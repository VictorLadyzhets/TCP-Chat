#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    server=  new Server(this);
     connect(server,SIGNAL(newMessage(QString,QString)),SLOT(onNewMessage(QString,QString)));
     connect(server,SIGNAL(UsersUpdate(QList<QString>)),SLOT(onUsersUpade(QList<QString>)));



}


MainWindow::~MainWindow()
{
    server->Dissconect();
    delete ui;
}

Server* MainWindow::GetServer()
{
    return server;
}

void MainWindow::onNewMessage(QString from, QString msg)
{


    QString text =  msg;
    ui->CharArea->append(text);
}

void MainWindow::on_SendButton_clicked()
{
    QString msg = ui->InputEditor->toPlainText();
    ui->InputEditor->clear();
   // server->Connect();
    server->SendMessage(msg);
    //server->Dissconect();
}


void MainWindow::onUsersUpade(QList<QString> users)
{
    ui->OnlineUsersArea->clear();
    for(int i=0;i<users.size();i++)
        ui->OnlineUsersArea->append(users[i]);
}

void MainWindow::on_RefreshUsersButton_clicked()
{
    server->RefreshUsers();
}

void MainWindow::on_ChangeNickButton_clicked()
{
    QString newNickName;
    newNickName = ui->NickEdit->toPlainText();
    server->ChangeUserName(newNickName);
}
