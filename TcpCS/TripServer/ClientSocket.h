#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QDate>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

class ClientSocket:public QTcpSocket
{
    Q_OBJECT
public:
    ClientSocket(QObject *parent = 0);

private slots:
    void readClient();

private:
    void generateRandomTrip(const QString &from, const QString &to,
                            const QDate &date, const QTime &time);
    quint16 nextBlockSize;
};

#endif // CLIENTSOCKET_H
