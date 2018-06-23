#include "bd.h"

#include <QMessageBox>

BD::BD()
{

}
bool BD::inicialize()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("library");
    db.setUserName(user);
    db.setPassword(password);
    db.setConnectOptions();

    if (db.open())
    {
        qDebug() <<db.lastError();
        return true;
    }
    else
    {
        qDebug() << "Failed to connect to root mysql admin";
        return false;
    }
}

BD* BD::getInstance()
{

    static BD instance;
    return &instance;
}


bool BD::createConnect(QString user, QString password)
{
    this->user = user;
    this->password = password;
    if(db.isOpen())
        db.close();
    return (inicialize() );
}



QSqlQuery* BD::make(QString request)//выборка из базы//учитывает selectedE
{

    if(!db.isOpen())
    {
        qDebug() << "You do not have to log in database";
        return NULL;
    }
    qDebug() << "[>] reqvest";
    qDebug() <<request;

    delete(query);
    query = new QSqlQuery(db);
    if(!query->exec(request))
    {
        qDebug() << "[!] bad reqvest";
        qDebug() << query->lastError().text();
    }
    return query;
}

void BD::insert(QString request)
{
    if(!db.isOpen())
    {
        qDebug() << "You do not have to log in database";
        return;
    }
    qDebug() << "[>] reqvest";
    qDebug() <<request;

    delete(query);
    query = new QSqlQuery(db);
    if(!query->prepare(request))
    {
        qDebug() << "[!] bad reqvest";
        qDebug() << query->lastError().text();
    }
    query->exec(request);
    qDebug() << "[!] bad reqvest ";
    qDebug() << query->lastError().text();
}

