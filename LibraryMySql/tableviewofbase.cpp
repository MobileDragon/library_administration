#include "tableviewofbase.h"

TableViewOfBase::TableViewOfBase(QWidget *parent) : QTableView(parent)
{
    initialize();
}

TableViewOfBase::~TableViewOfBase()
{
    if(my_model!=0)
        my_model->clear();
    delete my_model;

}

void TableViewOfBase::initialize()
{
    this->setAlternatingRowColors(true);//tableView
    this->setSortingEnabled(true);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->verticalHeader()->hide();
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    my_model=0;
    headerOfReader<<"Id читателя"<<"Имя"<<"Фамилия"<<"Отчество";
    headerOfMostPopularity<<"ISBN"<<"Год издания"<<"Название"<<"Число оставшихся книг";
    headerOfLeastPopularity<<"ISBN"<<"Год издания"<<"Название"<<"Число дней в простое";
    headerOfBooks<<"ISBN"<<"Название"<<"Инвертарный номер"<<"Статус";
    //--
    madalHeader<<"ISBN"<<"Инвертарный номер"<<"Название";
    madalHeader2<<"ISBN"<<"Инвертарный номер"<<"Название"<<"Число оставшихся дней";

    //все читатели 0
    requests_Reader<<QString("select id_reader, name, surname, patronymic from readers")+
                     " where id_reader like %1 or name like %1 or surname like %1 or patronymic like %1";
    //должники 1
    requests_Reader<<QString("select DISTINCT id_reader, name, surname, patronymic")+
              " from readers LEFT JOIN books_of_reader USING(id_reader)"+
              " where ISNULL(date_of_return)"+
              " and (TO_DAYS(NOW()) - TO_DAYS(date_of_issue) > max_number_of_days)"+
              " and (id_reader like %1 or name like %1 or surname like %1 or patronymic like %1)";
    //без долгов 2
    requests_Reader<<QString("select DISTINCT id_reader, name, surname, patronymic")+
              " from readers LEFT JOIN books_of_reader USING(id_reader)"+
              " where id_reader not in("+
              " select distinct bor.id_reader from books_of_reader AS bor"+
              " where TO_DAYS(NOW()) - TO_DAYS(bor.date_of_issue) > bor.max_number_of_days"+
              " )"+
              " and (id_reader like %1 or name like %1 or surname like %1 or patronymic like %1)";
    //без книг 3
    requests_Reader<<QString("select DISTINCT id_reader, name, surname, patronymic")+
              " from readers LEFT JOIN books_of_reader USING(id_reader)"+
              " where id_reader not in("+
              " select distinct bor.id_reader from books_of_reader AS bor"+
              " where ISNULL(date_of_return)"+
              " )"+
              " and (id_reader like %1 or name like %1 or surname like %1 or patronymic like %1)";
    //наиболее популярные книги 0
    requests_Popularity<<QString("select b.isbn, b.year_of_publication, b.book_title, (")+
                                 " select count(cob.inventory_number) from copies_of_books AS cob"+
                                 " where (cob.isbn like b.isbn) and"+
                                 " cob.inventory_number not in("+
                                 " select bor.inventory_number from books_of_reader as bor"+
                                 " where ISNULL(bor.date_of_return)"+
                                 " )"+
                                 " ) as kol from book as b"+
                                 " where b.isbn in("+
                                 " select bor2.isbn from books_of_reader as bor2"+
                                 " where ISNULL(bor2.date_of_return)"+
                                 " )"+
                                 " and (b.isbn like %1 or b.year_of_publication like %1 or b.book_title like %1)";
    //наименее популярные книги 1
    requests_Popularity<<QString("select b.isbn, b.year_of_publication, b.book_title, (")+
                                 " select TO_DAYS(NOW()) - TO_DAYS(bor.date_of_return) as days"+
                                 " from books_of_reader as bor"+
                                 " where bor.isbn = b.isbn"+
                                 " ORDER BY bor.date_of_return DESC LIMIT 0,1"+
                                 " ) as kol ,("+
                                 " select TO_DAYS(NOW()) - TO_DAYS(cob.date_of_receiving) AS birth"+
                                 " from copies_of_books AS cob"+
                                 " where cob.isbn = b.isbn"+
                                 " ORDER BY cob.date_of_receiving LIMIT 0,1"+
                                 " )from book as b"+
                                 " where b.isbn not in("+
                                 " select bor2.isbn from books_of_reader as bor2"+
                                 " where ISNULL(bor2.date_of_return)"+
                                 " )"+
                                 " and (b.isbn like %1 or b.year_of_publication like %1 or b.book_title like %1)"+
                                 " and (b.written_off like 'f')";
    //статус экземпляров книг
    requests_Books<<QString("select isbn, book_title, inventory_number,")+
                            " (select bor.id_reader from books_of_reader as bor"+
                            " where ISNULL(bor.date_of_return)"+
                            " and copies_of_books.inventory_number = bor.inventory_number"+
                            " ) as reading,"+
                            " (select bor2.is_buy from books_of_reader as bor2"+
                            " where (copies_of_books.inventory_number = bor2.inventory_number)"+
                            " and (bor2.is_buy like 't' )"+
                            " ) as buy,"+
                            " written_off from copies_of_books LEFT JOIN book USING(isbn)"+
                            " where isbn like %1 or book_title like %1 or inventory_number like %1";
//--
    madalRequest = QString("select isbn, inventory_number, book_title from book RIGHT JOIN copies_of_books USING(isbn)")+
                            " where isbn not in("+
                            " select bor.isbn from books_of_reader as bor"+
                            " WHERE ( bor.id_reader = %1 ) and ISNULL(bor.date_of_return)"+
                            " )"+
                            " and (written_off like 'f')"+
                            " and (inventory_number not in ("+
                            " select bor2.inventory_number from books_of_reader as bor2"+
                            " where ISNULL(bor2.date_of_return) ))"+
                            " and (isbn like %2 or book_title like %2 or inventory_number like %2)";
    madalRequest2 = QString("select isbn, inventory_number, book_title, "
                            " ( max_number_of_days - (TO_DAYS(NOW()) - TO_DAYS(date_of_issue) ) ) as num"
                            " from books_of_reader LEFT JOIN book USING(isbn)")+
                            " where (id_reader = %1) and (ISNULL(date_of_return))"+
                            " and (isbn like %2 or book_title like %2 or inventory_number like %2)";
}

void TableViewOfBase::updateData(int typeRequest, int numRequest, const QString &search)
{
    if(my_model!=0)
        my_model->clear();
    else
    {
        my_model = new QStandardItemModel();
    }

    switch (typeRequest) {//1,2,3
    case 1:
        updateReader(numRequest, search);
        break;
    case 2:
        updateMostPopularity(numRequest, search);
        break;
    case 3:
        updateBooks(numRequest, search);
        break;

    default:
        qDebug() <<"Не существующий вариант выборки";
        break;
    }
}

void TableViewOfBase::updateReader(int numRequest, const QString &search)
{
    if(numRequest < 0 || numRequest > 3)
        return;
    my_model->setHorizontalHeaderLabels(headerOfReader);

    QSqlQuery *query = BD::getInstance()->make(requests_Reader[numRequest].arg("\'"+search+"\%\'") );//выполнение выборки
    if(query == NULL)
        return;

    int numRow=0;
    while(query->next())
    {
        for(int numColumn = 0; numColumn < 4; numColumn++)
        {
            QStandardItem *item = new QStandardItem(query->value(numColumn).toString() );

            item->setEditable(false);
            item->setFont(QFont("Arial",10,6500));
            my_model->setItem(numRow, numColumn, item);
        }

        QString type = query->value(1).toString();
        qDebug()<<type;
        numRow++;
    }
    this->setModel(my_model);
    this->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    //this->horizontalHeader()->setSectionResizeMode(0,QHeaderView::);
}

void TableViewOfBase::updateMostPopularity(int numRequest, const QString &search)
{
    switch (numRequest) {
    case 0:
        my_model->setHorizontalHeaderLabels(headerOfMostPopularity);
        break;
    case 1:
        my_model->setHorizontalHeaderLabels(headerOfLeastPopularity);
        break;
    default:
        return;
    }

    QSqlQuery *query = BD::getInstance()->make(requests_Popularity[numRequest].arg("\'"+search+"\%\'") );//выполнение выборки
    if(query == NULL)
        return;

    int numRow=0;
    while(query->next())
    {
        for(int numColumn = 0; numColumn < 4; numColumn++)
        {
            QStandardItem *item;
            if(numRequest == 1 && numColumn == 3
                    && query->value(numColumn).isNull())
            {
                item = new QStandardItem(query->value(4).toString() );
            }
            else
                item = new QStandardItem(query->value(numColumn).toString() );

            item->setEditable(false);
            item->setFont(QFont("Arial",10,6500));
            my_model->setItem(numRow, numColumn, item);
        }

        QString type = query->value(1).toString();
        qDebug()<<type;
        numRow++;
    }

    this->setModel(my_model);
    this->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    this->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    this->horizontalHeader()->setSectionResizeMode(3,QHeaderView::ResizeToContents);
}


void TableViewOfBase::updateBooks(int numRequest, const QString &search)
{
    if(numRequest != 0)
        return;
    my_model->setHorizontalHeaderLabels(headerOfBooks);

    QSqlQuery *query = BD::getInstance()->make(requests_Books[numRequest].arg("\'"+search+"\%\'")  );//выполнение выборки
    if(query == NULL)
        return;

    int numRow=0;
    while(query->next())
    {
        for(int numColumn = 0; numColumn < 4; numColumn++)
        {
            QStandardItem *item;
            if(numColumn == 3)
            {
                if(query->value(3).toInt() != 0)
                {
                    item = new QStandardItem("На руках" );


                }
                else
                {
                    if(query->value(4).toString() == "t")
                        item = new QStandardItem("Куплена" );
                    else
                    {
                        if(query->value(5).toString() == "t")
                            item = new QStandardItem("Списана" );
                        else
                            item = new QStandardItem("В библиотеке" );
                    }

                }
            }
            else
                item = new QStandardItem(query->value(numColumn).toString() );


            item->setEditable(false);
            item->setFont(QFont("Arial",10,6500));
            my_model->setItem(numRow, numColumn, item);
        }

        QString type = query->value(1).toString();
        qDebug()<<type;
        numRow++;
    }

    this->setModel(my_model);
    this->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    this->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
    this->horizontalHeader()->setSectionResizeMode(3,QHeaderView::ResizeToContents);
}

void TableViewOfBase::updateBooksForReader(const QString &search, QString idReader)
{
    if(my_model!=0)
        my_model->clear();
    else
    {
        my_model = new QStandardItemModel();
    }
    my_model->setHorizontalHeaderLabels(madalHeader);

    QSqlQuery *query = BD::getInstance()->make(madalRequest.arg("\'"+idReader+"\'").arg("\'"+search+"\%\'")  );//выполнение выборки
    if(query == NULL)
        return;

    int numRow=0;
    while(query->next())
    {
        for(int numColumn = 0; numColumn < 3; numColumn++)
        {
            QStandardItem *item = new QStandardItem(query->value(numColumn).toString() );


            item->setEditable(false);
            item->setFont(QFont("Arial",10,6500));
            my_model->setItem(numRow, numColumn, item);
        }

        QString type = query->value(1).toString();
        qDebug()<<type;
        numRow++;
    }

    this->setModel(my_model);
    this->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    this->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
}
//--
void TableViewOfBase::updateBooksFromReader(const QString &search, QString idReader)
{
    if(my_model!=0)
        my_model->clear();
    else
    {
        my_model = new QStandardItemModel();
    }
    my_model->setHorizontalHeaderLabels(madalHeader2);

    QSqlQuery *query = BD::getInstance()->make(madalRequest2.arg("\'"+idReader+"\'").arg("\'"+search+"\%\'")  );//выполнение выборки
    if(query == NULL)
        return;

    int numRow=0;
    while(query->next())
    {
        for(int numColumn = 0; numColumn < 4; numColumn++)
        {
            QStandardItem *item = new QStandardItem(query->value(numColumn).toString() );


            item->setEditable(false);
            item->setFont(QFont("Arial",10,6500));
            my_model->setItem(numRow, numColumn, item);
        }

        QString type = query->value(1).toString();
        qDebug()<<type;
        numRow++;
    }

    this->setModel(my_model);
    this->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    this->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    this->horizontalHeader()->setSectionResizeMode(3,QHeaderView::ResizeToContents);

}
