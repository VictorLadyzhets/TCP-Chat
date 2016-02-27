#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QWidget>
#include<QTcpSocket>
#include<QTextEdit>
#include<QTcpServer>
#include"commands.h"
#include<QList>
#include<QMap>
class Server : public QWidget
{
    Q_OBJECT
public:
    explicit Server(quint16 nport,QWidget *parent = 0);

signals:

public slots:
    virtual void onNewConnection();
    void onReadyRead();
    void onDisconect();
private:
    QTcpServer *server;
    QTextEdit *log;
    quint16 blockSize;
    quint16 port;

    void SendMessage(QTcpSocket * socket,QString message);
    void SendToClient(QTcpSocket * socket,QString message);
    void SendToClients(QString message);
    void RefreshUser(QTcpSocket *socket);
    QString MakeResponse(QString msg, QTcpSocket *socket);
    QString GetOnlineUsers();
    QList<QTcpSocket*> Clients;
    QMap<QTcpSocket*,QString> ClientNames;

};

#endif // SERVER_H
