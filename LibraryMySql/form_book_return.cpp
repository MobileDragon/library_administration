#include "form_book_return.h"

Form_Book_Return::Form_Book_Return(QString id_reader, QWidget *parent):
    QDialog(parent)
{
    initialize(id_reader);
}

Form_Book_Return::~Form_Book_Return()
{
    delete lineSearch;
    delete tableOfBooks;
    delete buttonIssue;
    delete lineDayLimit;
    delete mainLayout;
}

void Form_Book_Return::build()
{
    this->setWindowTitle("Возврат книги");
    mainLayout = new QVBoxLayout();
    lineSearch = new QLineEdit();
    lineSearch->setPlaceholderText("поиск по таблице");
    connect(lineSearch, SIGNAL(textEdited(QString)), this, SLOT(edited_Search(QString)) );

    tableOfBooks = new TableViewOfBase();
    connect(tableOfBooks, SIGNAL(clicked(QModelIndex)), SLOT(slotClikTable(const QModelIndex)) );

    buttonIssue = new QPushButton("Принять книгу");
    buttonIssue->setEnabled(false);
    connect(buttonIssue, SIGNAL(released()) ,this,SLOT(agreeReleased() ));

    mainLayout->addWidget(lineSearch);
    mainLayout->addWidget(tableOfBooks);
    mainLayout->addWidget(buttonIssue);
    mainLayout->setAlignment(buttonIssue,Qt::AlignRight);

    tableOfBooks->updateBooksFromReader(lineSearch->text(), id_reader);


    this->setLayout(mainLayout);
}
void Form_Book_Return::initialize(QString id_reader)
{
    result = -1;

    this->id_reader = id_reader;

    mainLayout = 0;
    lineSearch = 0;
    tableOfBooks = 0;
    buttonIssue = 0;
    lineDayLimit = 0;

    leftDays=0;
    selectedBookISBN="";
    selectedBookInventory="";

    build();
}

bool Form_Book_Return::book_Return()
{
    QString request = QString("UPDATE books_of_reader SET date_of_return = NOW()")+
                              " WHERE (id_reader = %1) and (inventory_number= %2 )";

    BD::getInstance()->insert(request.arg(id_reader).arg(selectedBookInventory) );
    return true;
}

void Form_Book_Return::closeEvent(QCloseEvent *e)
{
    this->finished(result);
    e->accept();
}

void Form_Book_Return::agreeReleased()
{
    if(leftDays>=0)//если сдача не просрочена
    {
        if(book_Return())//если книга выбрана
        {
            result=0;
            this->close();
        }
    }
    else//запуск формы для оплаты штрафа
    {
        //
        Form_Payment_Penalty *formPenalty = new Form_Payment_Penalty(selectedBookInventory,this);//авторизация
        connect(formPenalty, SIGNAL(finished(int)) ,this,SLOT(formPenaltyDestroy(int) ));
        //this->setVisible(false);
        formPenalty->show();

    }
}

void Form_Book_Return::edited_Search(QString s)
{
    tableOfBooks->updateBooksFromReader(s, id_reader);
    buttonIssue->setEnabled(false);
}


void Form_Book_Return::slotClikTable(const QModelIndex &index)
{
    int row = index.row();

    TableViewOfBase* thisTable = ((TableViewOfBase*)sender());//
    selectedBookISBN = (thisTable->model()->data(thisTable->model()->index(row,0))).toString();
    selectedBookInventory = (thisTable->model()->data(thisTable->model()->index(row,1))).toString();
    leftDays = (thisTable->model()->data(thisTable->model()->index(row,3))).toInt();
    //з
    qDebug()<<"buttonIssue->setEnabled(true)";
    buttonIssue->setEnabled(true);
}

void Form_Book_Return::formPenaltyDestroy(int result)
{
    if(result==0)
    {
        if(book_Return())//если книга выбрана
        {
            result=0;
            this->close();
        }
    }
}
