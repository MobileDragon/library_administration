#include "form_payment_penalty.h"

Form_Payment_Penalty::Form_Payment_Penalty(const QString &bookInventory, QWidget *parent) :
    QDialog(parent)
{
    initialize(bookInventory);
}

Form_Payment_Penalty::~Form_Payment_Penalty()
{
    delete lineAccount;
    delete buttonLayout;
    delete agree;
    delete cancel;
    delete plaintText;
    delete mainLayout;
}

void Form_Payment_Penalty::initialize(QString bookInventory)
{
    this->setWindowTitle("Оплата штрафа");
    result=-1;
    accountChanged=false;
    this->bookInventory = bookInventory;
    requestForSelect=QString("select ( (TO_DAYS(NOW()) - TO_DAYS(date_of_issue) ) - max_number_of_days ) as num"
            " from books_of_reader where (inventory_number = %1) and ISNULL(date_of_return)").arg(this->bookInventory);
    requestForUpdate=QString("insert into money values( %1, %2, null)");

    mainLayout = new QVBoxLayout();

    generateAsk();
    plaintText = new QPlainTextEdit(verification);
    plaintText->setReadOnly(true);

    lineAccount = new QLineEdit();
    lineAccount->setPlaceholderText("оплата за штраф");
    connect(lineAccount, SIGNAL(textEdited(QString)), this, SLOT(editedAccount(QString)) );

    agree = new QPushButton("Оплатить");
    agree->setEnabled(false);
    connect(agree, SIGNAL(released()) ,this,SLOT(agreeReleased() ));

    mainLayout->addWidget(plaintText );
    mainLayout->addWidget(lineAccount);
    mainLayout->addWidget(agree);
    mainLayout->setAlignment(agree,Qt::AlignRight);

    this->setLayout(mainLayout);
}

void Form_Payment_Penalty::generateAsk()
{
    QSqlQuery *query = BD::getInstance()->make(requestForSelect);
    if(query == NULL)
    {
        verification = "-1";
        return;
    }
    query->next();
    //название ISBN количество год
    verification=QString("Сдача книги просрочена на %1 дней").arg(query->value(0).toString() ).arg(query->value(0).toString() ).arg(query->value(2).toString() ).arg(query->value(3).toString() );



    QString type = query->value(1).toString();
    qDebug()<<type;
}

void Form_Payment_Penalty::make_WriteOff()
{
    BD::getInstance()->insert(requestForUpdate.arg(this->bookInventory).arg(this->penaltyAccount));
    qDebug()<<"___________________________";
}


void Form_Payment_Penalty::closeEvent(QCloseEvent *e)
{
    this->finished(result);
    e->accept();
}

void Form_Payment_Penalty::agreeReleased()
{
    make_WriteOff();
    result=0;
    this->close();
}


void Form_Payment_Penalty::editedAccount(QString)
{
    if(accountChanged)
        return;
    agree->setEnabled(true);
    bool ok;
    int f=lineAccount->text().toInt(&ok);
    if(f > 1 && ok)
    {
        penaltyAccount = f;
    }
    else
    {
        penaltyAccount=0;
        accountChanged=true;
        lineAccount->setText("0");
        accountChanged=false;
    }
}
