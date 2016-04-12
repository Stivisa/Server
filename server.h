#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    ~Server();
signals:

public slots:
    void acceptConnection();
    void startRead();
private:
    QTcpServer server;
    QTcpSocket* client;
};

#endif // SERVER_H
