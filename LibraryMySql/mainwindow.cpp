#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialize();
    displayRequest();//сделать авторизацию

}

MainWindow::~MainWindow()
{
    delete comboReaderGroup1;
    delete lineSearch1;

    delete tableOfReaders1;
    delete comboAction1;
    delete buttonAgree1;

    delete comboBookPopularity2;
    delete lineSearch2;
    delete tableOfBooks2;
    delete buttonWriteOff2;

    delete lineSearch3;
    delete tableOfBooks3;

    delete tabLayout1;
    delete tabLayout2;
    delete tabLayout3;
    delete tab1;
    delete tab2;
    delete tab3;

    delete ui;
}

void MainWindow::displayRequest()
{
    Form_Login *formLogin = new Form_Login(this);//авторизация
    connect(formLogin, SIGNAL(finished(int)) ,this,SLOT(formLoginDestroy(int) ));
    //this->setVisible(false);
    formLogin->show();


/*
    bool t = BD::getInstance()->createConnect("root","123");
    qDebug()<<t;
    //BD::getInstance()->make("insert into worker(name,dept) values('Ritu23', 'Accounting')");

    QSqlQuery *query = BD::getInstance()->make("select * from book");
    if(query == NULL)
        return;
    while(query->next())
    {
        QString type = query->value(1).toString();
        qDebug()<<type;
    }*/
}

void MainWindow::initialize()
{
    comboReaderGroup1=0;
    lineSearch1=0;

    tableOfReaders1=0;
    comboAction1=0;
    buttonAgree1=0;

    comboBookPopularity2=0;
    lineSearch2=0;
    tableOfBooks2=0;
    buttonWriteOff2=0;

    lineSearch3=0;
    tableOfBooks3=0;

    tabLayout1=0;
    tabLayout2=0;
    tabLayout3=0;
    tab1=0;
    tab2=0;
    tab3=0;
}

void MainWindow::buid()
{
    ui->tabWidget->clear();//удалить все вкладки
    createTab1();
    createTab2();
    createTab3();

    ui->tabWidget->addTab(tab1,"Читатели");
    ui->tabWidget->addTab(tab2,"Популярность книг");
    ui->tabWidget->addTab(tab3,"Список книг");
    ui->tabWidget->setCurrentWidget(tab1);

}

void MainWindow::createTab1()
{
    //tab1
    tab1 = new QWidget();
    tabLayout1 = new QVBoxLayout();
    comboReaderGroup1 = new QComboBox();
    comboReaderGroup1->addItem("Все читатели");
    comboReaderGroup1->addItem("Должники");
    comboReaderGroup1->addItem("Без задолжностей");
    comboReaderGroup1->addItem("Читатели без книг");
    connect(comboReaderGroup1, SIGNAL(currentIndexChanged(int)), this, SLOT(Reader_IndexChanged(int)) );

    lineSearch1 = new QLineEdit();
    lineSearch1->setPlaceholderText("поиск по таблице");
    connect(lineSearch1, SIGNAL(textEdited(QString)), this, SLOT(edited_Search_1(QString)) );
    tableOfReaders1 = new TableViewOfBase();
    connect(tableOfReaders1, SIGNAL(clicked(QModelIndex)), SLOT(slotClikTable_1(const QModelIndex)) );

    comboAction1 = new QComboBox();
    comboAction1->addItem("Выдать книгу");
    comboAction1->addItem("Принять книгу");
    comboAction1->addItem("Возместить утрату");
    comboAction1->addItem("Сведения о взятых книгах");
    connect(comboAction1, SIGNAL(currentIndexChanged(int)), this, SLOT(Action_IndexChanged(int)) );


    buttonAgree1 = new QPushButton("Продолжить");
    connect(buttonAgree1, SIGNAL(released()), SLOT(buttononAgree1_Released()) );

    tabLayout1->addWidget(comboReaderGroup1);
    tabLayout1->addWidget(lineSearch1);
    tabLayout1->addWidget(tableOfReaders1);
    tabLayout1->addWidget(comboAction1);
    tabLayout1->addWidget(buttonAgree1);
    tabLayout1->setAlignment(buttonAgree1,Qt::AlignRight);
    tab1->setLayout(tabLayout1);

    activateTab_1(false);

    updatetableOfReaders(comboReaderGroup1->currentIndex(),lineSearch1->text());
}

void MainWindow::createTab2()
{
    //tab2
    tab2 = new QWidget();
    tabLayout2 = new QVBoxLayout();
    comboBookPopularity2 = new QComboBox();
    comboBookPopularity2->addItem("Нииболее популярные");
    comboBookPopularity2->addItem("Не пользующиеся спросом");
    connect(comboBookPopularity2, SIGNAL(currentIndexChanged(int)), this, SLOT(BookPopularity_IndexChanged(int)) );


    lineSearch2 = new QLineEdit();
    lineSearch2->setPlaceholderText("поиск по таблице");
    connect(lineSearch2, SIGNAL(textEdited(QString)), this, SLOT(edited_Search_2(QString)) );
    tableOfBooks2 = new TableViewOfBase();
    connect(tableOfBooks2, SIGNAL(clicked(QModelIndex)), SLOT(slotClikTable_2(const QModelIndex)) );

    buttonWriteOff2 = new QPushButton("Списать книги");
    connect(buttonWriteOff2, SIGNAL(released()), SLOT(buttonWriteOff2_Released()) );

    tabLayout2->addWidget(comboBookPopularity2);
    tabLayout2->addWidget(lineSearch2);
    tabLayout2->addWidget(tableOfBooks2);
    tabLayout2->addWidget(buttonWriteOff2);
    tabLayout2->setAlignment(buttonWriteOff2,Qt::AlignCenter);
    tab2->setLayout(tabLayout2);

    activateTab_2(false);

    updateTableOfPopularity(comboBookPopularity2->currentIndex(),lineSearch1->text());
}

void MainWindow::createTab3()
{
    //tab3
    tab3 = new QWidget();
    tabLayout3 = new QVBoxLayout();
    lineSearch3 = new QLineEdit();
    lineSearch3->setPlaceholderText("поиск по таблице");
    connect(lineSearch3, SIGNAL(textEdited(QString)), this, SLOT(edited_Search_3(QString)) );
    tableOfBooks3 = new TableViewOfBase();
    tabLayout3->addWidget(lineSearch3);
    tabLayout3->addWidget(tableOfBooks3);
    tab3->setLayout(tabLayout3);

    updateTableOfBooks(lineSearch3->text());
}

void MainWindow::updatetableOfReaders(int numRequest, QString search)//
{
    tableOfReaders1->updateData(1,numRequest,search);

}

void MainWindow::updateTableOfPopularity(int numRequest, QString search)
{
    tableOfBooks2->updateData(2,numRequest,search);
}
void MainWindow::updateTableOfBooks(QString search)
{
    tableOfBooks3->updateData(3,0,search);
}


//--tab 1
void MainWindow::Reader_IndexChanged(int index)//combo
{
    qDebug() <<index;
    updatetableOfReaders(index,lineSearch1->text());
    activateTab_1(false);
}

void MainWindow::Action_IndexChanged(int index)//combo
{

}
//tab 2
void MainWindow::BookPopularity_IndexChanged(int index)//combo
{
    updateTableOfPopularity(index,lineSearch2->text());
    activateTab_2(false);
}
//--tab 1
void MainWindow::edited_Search_1(QString s)
{
    updatetableOfReaders(comboReaderGroup1->currentIndex(), s);
    activateTab_1(false);
}
//tab 2
void MainWindow::edited_Search_2(QString s)
{
    updateTableOfPopularity(comboBookPopularity2->currentIndex(), s);
    activateTab_2(false);
}
//tab 3
void MainWindow::edited_Search_3(QString s)
{
    updateTableOfBooks(s);
}

void MainWindow::activateTab_1(bool flag)//активировать элемены управления
{
    comboAction1->setEnabled(flag);
    buttonAgree1->setEnabled(flag);
    if(!flag)
        selectedReaderId="";
}

void MainWindow::activateTab_2(bool flag)//активировать элемены управления
{
    buttonWriteOff2->setEnabled(flag);
    if(!flag)
        selectedBookISBN="";
}

void MainWindow::slotClikTable_1(const QModelIndex &index)//выбран читатель
{
    int row = index.row();

    TableViewOfBase* thisTable = ((TableViewOfBase*)sender());//
    selectedReaderId = (thisTable->model()->data(thisTable->model()->index(row,0))).toString();
    //запустить отображение вариантов действий, и кнопки продолжить
    activateTab_1(true);

}
void MainWindow::slotClikTable_2(const QModelIndex &index)
{
    int row = index.row();

    TableViewOfBase* thisTable = ((TableViewOfBase*)sender());//
    selectedBookISBN = (thisTable->model()->data(thisTable->model()->index(row,0))).toString();
    //запустить отображение кнопки "Списать" если это возможно
    if(comboBookPopularity2->currentIndex()==1)
    {
         activateTab_2(true);
    }
}

bool MainWindow::isCanIssue()
{//узнать количество книг у читателя
    QSqlQuery *query = BD::getInstance()->make( QString("select count(isbn) from books_of_reader"
                                               " WHERE (id_reader=\'%1\') and (ISNULL(date_of_return))").arg(selectedReaderId) );
    if(query == NULL)
        return true;
    query->next();
    if(query->value(0).toInt() < 5)
        return true;
    else
        return false;
}

void MainWindow::buttononAgree1_Released()
{
    Form_Book_Issue *book_Issue;
    Form_Book_Return *book_Return;
    Form_WriteOff_Books *verification;
    switch (comboAction1->currentIndex()) {
    case 0:
        if(!isCanIssue())
        {
            QMessageBox::warning(this, "Ошибка выдачи", "Читатель не может иметь более 5 книг на руках", QMessageBox::Ok);
            break;
        }

        book_Issue = new Form_Book_Issue(selectedReaderId,this);//isbn
        connect(book_Issue, SIGNAL(finished(int)) ,this,SLOT(book_IssueDestroy(int) ));
        book_Issue->show();

        break;
    case 1:

        book_Return = new Form_Book_Return(selectedReaderId,this);//isbn
        connect(book_Return, SIGNAL(finished(int)) ,this,SLOT(book_ReturnDestroy(int) ));
        book_Return->show();
        break;
    case 2:
        verification = new Form_WriteOff_Books(selectedBookISBN,this);//isbn
        connect(verification, SIGNAL(finished(int)) ,this,SLOT(verificationDestroy(int) ));
        verification->show();
        break;
    case 3:

        break;
    default:
        break;
    }


}

void MainWindow::buttonWriteOff2_Released()
{
    Form_WriteOff_Books *verification = new Form_WriteOff_Books(selectedBookISBN,this);//isbn
    connect(verification, SIGNAL(finished(int)) ,this,SLOT(verificationDestroy(int) ));
    verification->show();
}


void MainWindow::formLoginDestroy(int result)
{
    if(result==0)
    {
        buid();//размещение на форме всех элементов

        //this->setVisible(true);
    }
    else
        this->close();
}

void MainWindow::book_IssueDestroy(int result)
{
    if(result==0)//была выдана книга
    {
        updatetableOfReaders(comboReaderGroup1->currentIndex(), lineSearch1->text());
        activateTab_1(false);
        updateTableOfPopularity(comboBookPopularity2->currentIndex(), lineSearch2->text());//обновление тыблицы
        activateTab_2(false);
        updateTableOfBooks(lineSearch3->text() );
    }
}

void MainWindow::book_ReturnDestroy(int result)
{
    if(result==0)//была возвращена книга
    {
        updatetableOfReaders(comboReaderGroup1->currentIndex(), lineSearch1->text());
        activateTab_1(false);
        updateTableOfPopularity(comboBookPopularity2->currentIndex(), lineSearch2->text());//обновление тыблицы
        activateTab_2(false);
        updateTableOfBooks(lineSearch3->text() );
    }
}

void MainWindow::verificationDestroy(int result)
{
    if(result==0)//было выполнено списывание книг
    {
        updateTableOfPopularity(comboBookPopularity2->currentIndex(), lineSearch2->text());//обновление тыблицы
        activateTab_2(false);
        updateTableOfBooks(lineSearch3->text() );
    }
}
