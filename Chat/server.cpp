#include "server.h"
#include<QHostAddress>
#include<QTime>
#include<QDataStream>
#include<QByteArray>
Server::Server(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket;
    connect(socket,SIGNAL(connected()),SLOT(onConnected()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),SLOT(onError(QAbstractSocket::SocketError)));
    connect(socket,SIGNAL(readyRead()),SLOT(onReadyRead()));

       socket->connectToHost("127.0.0.1",10000);

     quint16  k= qrand()%20;
    thisUserName = "Guest";

    //SendNameToServer();
}





void Server::onReadyRead()
{

  QDataStream in(socket);QByteArray ba;
  if(block_size==0)
  {
      if(socket->bytesAvailable() < (int)sizeof(quint16))
          return;

      ba = socket->readAll();

              QString s(ba);
      QString sizeB= "";

      for(int i=0;i<2;i++)
          sizeB.append(s[i]);
      block_size = sizeB.toInt();
  }

  if(socket->bytesAvailable()<(int)sizeof(block_size))
  {

      return;
  }
  else
     {

      QByteArray baa = socket->readAll();
      QString readed(ba+baa);
      DataReaded(readed);
     }

}


void Server::onError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
        case QAbstractSocket::RemoteHostClosedError:
            emit newMessage("server:","RemoteHostClosedError");
            break;
        case QAbstractSocket::HostNotFoundError:
              emit newMessage("server:","ServerNotFound");
            break;
        case QAbstractSocket::ConnectionRefusedError:
            emit newMessage("server","ConnectionRefusedError");
            break;
        default:
            emit newMessage("server","Error");
     }



}


void Server::onConnected()
{
    emit newMessage("server","connected");
}


bool Server::SendMessage(QString message)
{


        QByteArray  arrBlock,tmpBlock;
        QTextStream out(&arrBlock);
        message = "SMS" +thisUserName +" : " + message;
         tmpBlock = message.toUtf8();
         quint16 size = tmpBlock.size();
         arrBlock.append(quint16(size-sizeof(quint16)));
         arrBlock.append(tmpBlock);

        socket->write(arrBlock);
        return true;
}


void Server::Dissconect()
{
    socket->disconnectFromHost();

}

bool Server::Connect()
{
    QHostAddress address;
    address = QHostAddress("127.0.0.1");
    socket->connectToHost(address,10000);

    return socket->isOpen();
}


void Server::RefreshUsers()
{
    QByteArray  arrBlock,tmpBlock;
    QString message = "USR";
     tmpBlock = message.toUtf8();
     quint16 size = tmpBlock.size();
     arrBlock.append(quint16(size-sizeof(quint16)));
     arrBlock.append(tmpBlock);
    socket->write(arrBlock);

}
void Server::DataReaded(QString data)
{
    QString comand="";
    for(int i=1;i<4;i++)
        comand= comand + data[i];
    if(comand=="SMS")
    {
        QString msg="";
        for(int i=4;i<data.length();i++)
            msg=msg+data[i];
        emit newMessage("server",msg);
        return;
    }

    if(comand=="USR")
    {
       QList<QString> users;
       QString tmp="";
       for(int i=4;i<data.length();i++)
       {
           if(data[i]!=',')
               tmp = tmp+data[i];
           else
           {
               users.push_back(tmp);
               tmp="";
           }
       }

       emit UsersUpdate(users);
    }

}


void Server::ChangeUserName(QString newUserName)
{
    thisUserName=newUserName;
    QByteArray  arrBlock,tmpBlock;
    QString message = "CUN" + newUserName;
     tmpBlock = message.toUtf8();
     quint16 size = tmpBlock.size();
     arrBlock.append(quint16(size-sizeof(quint16)));
     arrBlock.append(tmpBlock);
    socket->write(arrBlock);
}

