#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"server.h"
#include<QTextEdit>
#include<QTextBrowser>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     Server* GetServer();
public slots:
    void onNewMessage(QString from,QString msg);
    void onUsersUpade(QList<QString> users);
private slots:
    void on_SendButton_clicked();

    void on_RefreshUsersButton_clicked();

    void on_ChangeNickButton_clicked();

private:
    Ui::MainWindow *ui;
    Server *server;

};

#endif // MAINWINDOW_H
