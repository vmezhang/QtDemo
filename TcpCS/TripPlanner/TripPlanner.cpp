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
