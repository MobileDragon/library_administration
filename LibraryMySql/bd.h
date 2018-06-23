#ifndef BD_H
#define BD_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QFileDialog>

class BD
{
public:
    static BD* getInstance();

    bool createConnect(QString user, QString password);

    QSqlQuery *make(QString request);
    void insert(QString request);


protected:
    QString user;
    QString password;
    QSqlDatabase db;
    QSqlQuery *query;
    //когда список пустой-значит можно вибирать все
    //
    bool inicialize();//создание нового подключения без проверок предыдущего
private:
    BD();
    //~BDE();
    BD(BD const&) = delete;
    BD& operator= (BD const&) = delete;




};

#endif // BD_H
