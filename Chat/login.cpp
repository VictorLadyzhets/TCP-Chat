#include "login.h"

Login::Login(QWidget *parent) : QWidget(parent)
{


        logLabel = new QLabel(this);

        logLabel->setText("Enter you Nickname");
        LogEdit = new QTextEdit(this);
        SignInButton = new QPushButton(this);
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(QLabel("<H1>Sign In<H1>"));
        layout->addWidget(logLabel);
        layout->addWidget(LogEdit);
        layout->addWidget(SignInButton);

}

