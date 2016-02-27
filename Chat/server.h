#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include<QTcpSocket>
#include<QString>
#include<QDataStream>
#include"commandcodes.h"
#include<QMessageBox>
#include<QList>
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

    bool Connect();
    void Dissconect();
    bool SendMessage(QString msg);
    bool SendOnlyTo(QString msg, QString name);

    bool disconnect();

    void RefreshUsers();
    void ChangeUserName(QString newUserName);
signals:
    void newMessage(QString from,QString Msg);
    void UsersUpdate(QList<QString> newUsers);

public slots:
    void onConnected();
    void onError(QAbstractSocket::SocketError socketError);
    void onReadyRead();

private:
    void DataReaded(QString data);

    QTcpSocket *socket;

    QString server_adrress;
    int server_port;
    int block_size;

    QString thisUserName;
};

#endif // SERVER_H
