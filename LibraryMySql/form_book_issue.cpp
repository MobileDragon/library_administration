#include "form_book_issue.h"

Form_Book_Issue::Form_Book_Issue(QString id_reader, QWidget *parent) :
    QDialog(parent)
{
    initialize(id_reader);
}

Form_Book_Issue::~Form_Book_Issue()
{
    delete lineSearch;
    delete tableOfBooks;
    delete buttonIssue;
    delete lineDayLimit;
    delete mainLayout;
}

void Form_Book_Issue::build()
{
    this->setWindowTitle("Выдача книги");
    mainLayout = new QVBoxLayout();
    lineSearch = new QLineEdit();
    lineSearch->setPlaceholderText("поиск по таблице");
    connect(lineSearch, SIGNAL(textEdited(QString)), this, SLOT(edited_Search(QString)) );
    lineDayLimit = new QLineEdit();
    connect(lineDayLimit, SIGNAL(textEdited(QString)), this, SLOT(edited_DayLimit(QString)) );
    lineDayLimit->setText("2");

    tableOfBooks = new TableViewOfBase();
    connect(tableOfBooks, SIGNAL(clicked(QModelIndex)), SLOT(slotClikTable(const QModelIndex)) );

    buttonIssue = new QPushButton("Выдать книгу");
    buttonIssue->setEnabled(false);
    connect(buttonIssue, SIGNAL(released()) ,this,SLOT(agreeReleased() ));

    mainLayout->addWidget(lineSearch);
    mainLayout->addWidget(tableOfBooks);
    mainLayout->addWidget(lineDayLimit);
    mainLayout->addWidget(buttonIssue);
    mainLayout->setAlignment(buttonIssue,Qt::AlignRight);

    tableOfBooks->updateBooksForReader(lineSearch->text(), id_reader);


    this->setLayout(mainLayout);
}
void Form_Book_Issue::initialize(QString id_reader)
{
    result = -1;

    this->id_reader = id_reader;

    mainLayout = 0;
    lineSearch = 0;
    tableOfBooks = 0;
    buttonIssue = 0;
    lineDayLimit = 0;
    dayChanged=false;
    numDays=2;

    selectedBookISBN="";
    selectedBookInventory="";

    build();
}

bool Form_Book_Issue::book_Issue()
{
    QString request = QString("insert into books_of_reader values( %1,NOW(),null,'f', %2, %3, %4)");

    BD::getInstance()->insert(request.arg(id_reader).arg(numDays).arg(selectedBookISBN).arg(selectedBookInventory) );
    return true;
}

void Form_Book_Issue::closeEvent(QCloseEvent *e)
{
    this->finished(result);
    e->accept();
}

void Form_Book_Issue::agreeReleased()
{
    if(book_Issue())//если книга выбрана
    {
        result=0;
        this->close();
    }
}

void Form_Book_Issue::edited_Search(QString s)
{
    tableOfBooks->updateBooksForReader(s, id_reader);
    buttonIssue->setEnabled(false);
}

void Form_Book_Issue::edited_DayLimit(QString s)
{
    if(dayChanged)
        return;
    bool ok;
    int f=lineDayLimit->text().toInt(&ok);
    if(f > 1 && ok)
    {
        numDays = f;
    }
    else
    {
        numDays=2;
        dayChanged=true;
        lineDayLimit->setText("2");
        dayChanged=false;
    }
}

void Form_Book_Issue::slotClikTable(const QModelIndex &index)
{
    int row = index.row();

    TableViewOfBase* thisTable = ((TableViewOfBase*)sender());//
    selectedBookISBN = (thisTable->model()->data(thisTable->model()->index(row,0))).toString();
    selectedBookInventory = (thisTable->model()->data(thisTable->model()->index(row,1))).toString();
    //з
    qDebug()<<"buttonIssue->setEnabled(true)";
    buttonIssue->setEnabled(true);
}
