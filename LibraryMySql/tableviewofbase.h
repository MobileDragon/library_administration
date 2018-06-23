#ifndef TABLEVIEWOFBASE_H
#define TABLEVIEWOFBASE_H

#include <QTableView>
#include <QStandardItem>
#include <QVector>
#include <QDebug>
#include <QHeaderView>
#include "bd.h"

class TableViewOfBase : public QTableView
{
    Q_OBJECT

public:
    explicit TableViewOfBase(QWidget *parent = 0);
    ~TableViewOfBase();

    void updateData(int typeRequest, int numRequest, const QString &search);
    void updateBooksForReader(const QString &search, QString idReader);//книги для читателя
    void updateBooksFromReader(const QString &search, QString idReader);//книги у читателя
private:
    QStandardItemModel *my_model;

    QStringList headerOfReader;
    QStringList headerOfMostPopularity;
    QStringList headerOfLeastPopularity;
    QStringList headerOfBooks;
    QStringList madalHeader;
    QStringList madalHeader2;

    QVector<QString> requests_Reader;
    QVector<QString> requests_Popularity;
    QVector<QString> requests_Books;
    QString madalRequest;
    QString madalRequest2;

    //void update();
    void initialize();


    void updateReader(int numRequest, const QString &search);
    void updateMostPopularity(int numRequest, const QString &search);
    void updateBooks(int numRequest, const QString &search);


};

#endif // TABLEVIEWOFBASE_H
