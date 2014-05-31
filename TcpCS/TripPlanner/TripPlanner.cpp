#include "TripPlanner.h"
#include "ui_tripplanner.h"

TripPlanner::TripPlanner(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TripPlanner)
{
    ui->setupUi(this);

    searchButton = buttonBox->addButton(tr("&Search"), QDialogButtonBox::ActionRole);

    stopButton = buttonBox->addButton(tr("S&top"), QDialogButtonBox::ActionRole);

    stopButton->setEnabled(false);
    buttonBox->button(QDialogButtonBox::Close)->setText(tr("&Quit"));

    QDateTime dateTime = QDateTime::currentDateTime();
    dateEdite->setDate(dateTime.date());
    timeEdite->setTime(QTime(dateTime.time().hour(), 0));

    progressBar->hide();
    progressBar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);

    tableWidget->verticalHeader()->hide();
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(searchButton, SIGNAL(clicked()), this, SLOT(connectionCloseByServer()));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopSearch()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(sendRequest()));
    connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(connectionCloseByServer()));
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(updateTableWidget()));
    connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error()));
}

TripPlanner::~TripPlanner()
{
    delete ui;
}

void TripPlanner::connectToServer()
{
    // 连接服务器,此调用是异步的,总是立即返回
    tcpSocket.connectToHost("tripserver.zugbahn.de", 6178);

    tableWidget->setRowCount(0);
    searchButton->setEnabled(false);
    stopButton->setEnabled(true);
    statusLable->setText(tr("Connecting to server..."));
    progressBar->show();

    nextBlockSize = 0;
}

void TripPlanner::sendRequest()
{
    // 连接已被建立
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_3);
    out << quint16(0) << quint8('S') << fromComboBox->currentText()
           << toComboBox->currentText() << dateEdite->date()
              << timeEdite->time();
    if (departureRadioButton->isChecked()) {
        out << quint8('D');
    }
    else {
        out << quint8('A');
    }
    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));
    tcpSocket.write(block);

    statusLable->setText(tr("Sending request..."));
}

void TripPlanner::updateTableWidget()
{
    QDataStream in(&tcpSocket);
    in.setVersion(QDataStream::Qt_4_3);

    forever {
        int row = tableWidget->rowCount();

        if (nextBlockSize == 0) {
            if (tcpSocket.bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> nextBlockSize;
        }
        if (nextBlockSize == 0xFFFF) {
            closeConnection();
            statusLable->setText(tr("Found %1 trip(s)").arg(row));
            break;
        }
        if (tcpSocket.bytesAvailable() < nextBlockSize) {
            break;
        }

        QDate date;
        QTime departureTime;
        QTime arrivalTime;
        quint16 duration;
        quint8 changes;
        QString trainType;

        in >> date >> departureTime >> duration >> changes >> trainType;
        arrivalTime = departureTime.addSecs(duration * 60);
        tableWidget->setRowCount(row + 1);

        QStringList fields;
        fields << date.toString(Qt::LocalDate)
               << departureTime.toString(tr("hh:mm"))
               << arrivalTime.toString(tr("hh:mm"))
               << tr("%1 hr %2 min").arg(duration / 60).arg(duration % 60)
               << QString::number(changes)
               << trainType;

        for (int i = 0; i < fields.count(); ++i) {
            tableWidget->setItem(row, i, new QTableWidgetItem(fields[i]));
        }
        nextBlockSize = 0;
    }
}

void TripPlanner::closeConnection()
{
    tcpSocket.close();
    searchButton->setEnabled(true);
    stopButton->setEnabled(false);
    progressBar->hide();
}

void TripPlanner::stopSearch()
{
    statusLable->setText(tr("Search stopped"));
    closeConnection();
}

void TripPlanner::connectionCloseByServer()
{
    if (nextBlockSize != 0xFFFF) {
        statusLable->setText(tr("Error:Connection closed by server"));
    }
    closeConnection();
}

void TripPlanner::error()
{
    statusLable->setText(tcpSocket.errorString());
    closeConnection();
}
