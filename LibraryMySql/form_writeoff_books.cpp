#include "form_writeoff_books.h"

Form_WriteOff_Books::Form_WriteOff_Books(const QString &bookSbn, QWidget *parent) :
    QDialog(parent)
{
    initialize(bookSbn);
}

Form_WriteOff_Books::~Form_WriteOff_Books()
{
    delete buttonLayout;
    delete agree;
    delete cancel;
    delete plaintText;
    delete mainLayout;
}

void Form_WriteOff_Books::initialize(QString bookSbn)
{
    this->setWindowTitle("Списывание книг");
    result=-1;
    this->bookSbn = bookSbn;
    requestForSelect=QString("select b.isbn, b.book_title,("
                             " select count(cob.inventory_number) from copies_of_books AS cob"
                             " where cob.isbn like \'%1\'"
                             " ) AS kol,"
                             " b.year_of_publication from book AS b"
                             " where b.isbn like \'%1\'").arg(this->bookSbn);
    requestForUpdate=QString("UPDATE book SET written_off=\'t\'"
                             " WHERE isbn=\'%1\'").arg(this->bookSbn);

    mainLayout = new QVBoxLayout();

    generateAsk();
    plaintText = new QPlainTextEdit(verification);
    plaintText->setReadOnly(true);

    agree = new QPushButton("Да");
    cancel = new QPushButton("Нет");
    connect(agree, SIGNAL(released()) ,this,SLOT(agreeReleased() ));
    connect(cancel, SIGNAL(released()) ,this,SLOT(cancelReleased() ));
    buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(agree);
    buttonLayout->addWidget(cancel);

    mainLayout->addWidget(plaintText );
    mainLayout->addLayout(buttonLayout);

    this->setLayout(mainLayout);
}

void Form_WriteOff_Books::generateAsk()
{
    QSqlQuery *query = BD::getInstance()->make(requestForSelect);
    if(query == NULL)
    {
        verification = "-1";
        return;
    }
    query->next();
    //название ISBN количество год
    verification=QString("Вы действительно хотите списать книгу \"%1\"\n"
            "с ISBN %2 в количестве %3 штук %4 года публикации?").arg(query->value(1).toString() ).arg(query->value(0).toString() ).arg(query->value(2).toString() ).arg(query->value(3).toString() );



    QString type = query->value(1).toString();
    qDebug()<<type;
}

void Form_WriteOff_Books::make_WriteOff()
{
    BD::getInstance()->insert(requestForUpdate);
    qDebug()<<"___________________________";
}


void Form_WriteOff_Books::closeEvent(QCloseEvent *e)
{
    this->finished(result);
    e->accept();
}

void Form_WriteOff_Books::agreeReleased()
{
    make_WriteOff();
    result=0;
    this->close();
}

void Form_WriteOff_Books::cancelReleased()
{
    result=-1;
    this->close();
}
