#include "form_login.h"

Form_Login::Form_Login(QWidget *parent) :
    QDialog(parent)
{
    initialize();
}

Form_Login::~Form_Login()
{
    delete login;
    delete password;
    delete agree;
    delete mainLayout;

}

void Form_Login::initialize()
{
    result=-1;
    this->setWindowTitle("Авторизация");

    mainLayout = new QVBoxLayout();
    login = new QLineEdit();
    login->setPlaceholderText("Логин");
    password = new QLineEdit();
    password->setPlaceholderText("Пароль");
    password->setEchoMode(QLineEdit::Password);
    agree = new QPushButton("Войти");
    connect(agree, SIGNAL(released()) ,this,SLOT(agreeReleased() ));

    mainLayout->addWidget(login);
    mainLayout->addWidget(password);
    mainLayout->addWidget(agree);
    mainLayout->setAlignment(agree,Qt::AlignCenter);

    this->setLayout(mainLayout);
}

bool Form_Login::makeLogin()
{
    return (BD::getInstance()->createConnect(login->text(),password->text() ) );
}


void Form_Login::closeEvent(QCloseEvent *e)
{
    this->finished(result);
    e->accept();
}

void Form_Login::agreeReleased()
{
    if(makeLogin())//если авторизация прошла успешно
    {
        result=0;
        this->close();
    }
}
