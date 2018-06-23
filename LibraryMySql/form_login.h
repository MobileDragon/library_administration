#ifndef FORM_LOGIN_H
#define FORM_LOGIN_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QCloseEvent>

#include "bd.h"

class Form_Login : public QDialog
{
    Q_OBJECT
public:
    explicit Form_Login(QWidget *parent = 0);
    ~Form_Login();

private:
    int result;

    QVBoxLayout *mainLayout;
    QLineEdit *login;
    QLineEdit *password;
    QPushButton *agree;//продолжить


    void initialize();
    bool makeLogin();//авторизация на сервере

private slots:
    void closeEvent(QCloseEvent *e);
    void agreeReleased();
};

#endif // FORM_LOGIN_H
