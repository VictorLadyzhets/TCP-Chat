#include "server.h"
#include<QVBoxLayout>
#include<QTime>
#include<QLabel>
#include<QString>
#include<string>
#include<iterator>

using namespace std;
Server::Server(quint16 nport,QWidget *parent) : QWidget(parent)
{


    log = new QTextEdit();
    log->setReadOnly(true);
    blockSize=0;
    port = nport;
    server= new QTcpServer(this);
    if(!server->listen(QHostAddress::Any,port))
    {
        log->append("Cannot run the server!"+server->errorString());
        server->close();
        return;
    }
    log->append("Server runned!");
    connect(server,SIGNAL(newConnection()),SLOT(onNewConnection()));

    QVBoxLayout* pvbxLayout = new QVBoxLayout;
        pvbxLayout->addWidget(new QLabel("<H1>Server</H1>"));
        pvbxLayout->addWidget(log);
        setLayout(pvbxLayout);

}


void Server::onNewConnection()
{



    QTcpSocket* socket = server->nextPendingConnection();
    Clients.push_back(socket);
    ClientNames.insert(socket,"Guest");
    log->append("new connection");

    connect(socket,SIGNAL(disconnected()),SLOT(onDisconect()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    SendToClient(socket,"Now you are connected!:)");
    SendToClients("USR"+GetOnlineUsers());
}


void Server::onDisconect()
{
    QTcpSocket * sock = qobject_cast<QTcpSocket *>(sender());

    for(int i=1;i<Clients.size();i++)
        if(Clients[i]==sock)
            Clients.erase(Clients.begin()+i,Clients.begin()+i+1);
        ClientNames.erase(ClientNames.find(sock));

    log->append("user disconected");
    QString response = "USR"+ GetOnlineUsers();
    log->append(response);
    SendToClients(response);
}

void Server::onReadyRead()
{



    QTcpSocket* socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_2);
    QByteArray ba;
    for(;;)
    {
        if(!blockSize)
        {

            if(socket->bytesAvailable()<sizeof(quint16))
                break;

            in >> blockSize;


             ba = socket->readAll();

                    QString s(ba);
            QString sizeB= "";

            for(int i=0;i<1;i++)
                sizeB.append(s[i]);
            blockSize = sizeB.toInt();

        }

        if(socket->bytesAvailable() < blockSize)
        {
            break;
        }


        QByteArray baa = socket->readAll();

        QString str(ba+baa);
        log->append("FromClient"+str);
        str= (str[0]=='M' ? "S" : (str[0]=='U' ? "C" : "U")) + str;
        blockSize=0;

        QString response = MakeResponse(str,socket);

        log->append("response " + str);

        SendToClients(response);

    }

}



QString Server::MakeResponse(QString msg,QTcpSocket* socket)
{
    QString response;
    QString comand = "";
    for(int i=0;i<3;i++)
        comand = comand + msg[i];



    if(comand =="SMS")
    {

        response = "";
        for(int i=3;i<msg.length();i++)
            response = response + msg[i];
        return "SMS"+response;
    }
    if(comand=="USR")
    {
        response = GetOnlineUsers();
        return "USR"+response;
    }
    if(comand=="CUN")
    {
       // QMap<QTcpSocket*,QString>::Iterator i = ClientNames.find(socket);
        QString response("SMS");
        QString newName="";
        for(int i=3;i<msg.length();i++)
            newName= newName + msg[i];
        QString oldName= ClientNames[socket];
        response = response + " " + oldName + " changed nickname into " + newName;
        ClientNames[socket]=newName;
        //SendToClients("USR" + GetOnlineUsers());
        return response;

    }
    return "Default response";
}


QString Server::GetOnlineUsers()
{

  //QMapIterator<QTcpSocket,QString> i(ClientNames);
  /*QString response=i.value()+",";
  while(i.hasNext())
  {
      response = response + i.value()+ ",";
      i.next();
  }*/
    QString response="";
    foreach(QString str,ClientNames)
        response = response + str +",";
  return response;
}



void Server::SendToClient(QTcpSocket *socket, QString message)
{


    QByteArray arrBlock;
    QByteArray tmpBlock;
    tmpBlock = message.toUtf8();
    quint16 size = tmpBlock.size();
    arrBlock.append(quint16(size-sizeof(quint16)));
    arrBlock.append(tmpBlock);
    QString s(arrBlock);
    //for(int i=0;i<Clients.size();i++)
        socket->write(arrBlock);

}


void Server::SendToClients(QString message)
{


    QByteArray arrBlock;
    QByteArray tmpBlock;
    tmpBlock = message.toUtf8();
    quint16 size = tmpBlock.size();
    arrBlock.append(quint16(size-sizeof(quint16)));
    arrBlock.append(tmpBlock);
    QString s(arrBlock);
    for(int i=0;i<Clients.size();i++)
        Clients[i]->write(arrBlock);

}
