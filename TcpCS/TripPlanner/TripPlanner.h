#ifndef TRIPPLANNER_H
#define TRIPPLANNER_H

#include <QtGui>
#include <QDialog>
#include <QWidget>
#include <QDateTime>
#include <QDateEdit>
#include <QLabel>
#include <QTcpSocket>
#include <QDialogButtonBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QComboBox>
#include <QProgressBar>
#include <QTableWidget>
#include <QRadioButton>

namespace Ui {
class TripPlanner;
}

class TripPlanner : public QDialog, private Ui::TripPlanner
{
    Q_OBJECT
    
public:
    explicit TripPlanner(QWidget *parent = 0);
    ~TripPlanner();

private slots:
    void connectToServer();
    void sendRequest();
    void updateTableWidget();
    void stopSearch();
    void connectionCloseByServer();
    void error();
    
private:
    Ui::TripPlanner *ui;

    void closeConnection();

    QDialogButtonBox *buttonBox;
    QDateEdit *dateEdite;
    QTimeEdit *timeEdite;
    QProgressBar *progressBar;
    QTableWidget *tableWidget;
    QPushButton *searchButton;
    QPushButton *stopButton;
    QLabel *statusLable;
    QTcpSocket tcpSocket;
    quint16 nextBlockSize;
    QComboBox *fromComboBox;
    QComboBox *toComboBox;
    QRadioButton *departureRadioButton;
};

#endif // TRIPPLANNER_H
