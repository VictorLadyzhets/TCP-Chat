#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QWidget>

class Login : public QWidget
{
    Q_OBJECT
public:
    explicit Login(QWidget *parent = 0);

signals:

public slots:


private:
    //Server * server;
    QLabel *logLabel;
    QLabel* passLabel;
    QTextEdit* LogEdit;
    QTextEdit *passEdit;
    QPushButton *SignInButton;


};

#endif // LOGIN_H
