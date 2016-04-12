#include "server.h"
#include <QDebug>
#include <iostream>
#include <QString>
#include <QByteArray>
using namespace std;

Server::Server(QObject* parent): QObject(parent)
{
  connect(&server, SIGNAL(newConnection()),
    this, SLOT(acceptConnection()));

  if(!server.listen(QHostAddress::Any, 1234)){

      qDebug() << "Server is off!";
  }
  else{
      qDebug() << "Server is on!";
  }
}

Server::~Server()
{
  server.close();
}

void Server::acceptConnection()
{
  client = server.nextPendingConnection();

  if(client->state() == QTcpSocket::ConnectedState)
      {
          printf("New connection established.\n");
          client->write("Welcome client :)\n");

          qDebug()<<client->peerAddress();
      }


  /*od onog sa youtube da ispise Dobrodosli klijent u soket
   * i da se to ispise kod klijenta prvo*/
  connect(client, SIGNAL(readyRead()),
    this, SLOT(startRead()));
}

void Server::startRead()
{
    while(client->canReadLine())
            {
                QByteArray ba = client->readLine();

                if(strcmp(ba.constData(), "exit\n") == 0)
                {
                    qDebug() << "KRAJ!";
                    client->close();
                    break;
                    //socket->disconnectFromHost();
                    //break;
                }
                printf(">> %s", ba.constData());
            }

}

