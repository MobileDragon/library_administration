#ifndef FORM_BOOK_RETURN_H
#define FORM_BOOK_RETURN_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QCloseEvent>

#include "bd.h"
#include "tableviewofbase.h"
#include "form_payment_penalty.h"

class Form_Book_Return : public QDialog
{
    Q_OBJECT
public:
    explicit Form_Book_Return(QString id_reader, QWidget *parent = 0);
    ~Form_Book_Return();

private:
    int result;

    QString id_reader;

    QVBoxLayout* mainLayout;//главный группировщик для вкладки №2
    QLineEdit* lineSearch;//строка для поиска по таблице
    TableViewOfBase *tableOfBooks;//список книг
    QLineEdit* lineDayLimit;//строка для указания срока выдачи
    QPushButton *buttonIssue;//отметить выбранный инвертарный из таблицы

    int leftDays;
    QString selectedBookISBN;//ISBN выбранной книги
    QString selectedBookInventory;//номер экземпляра выбранной книги

    void build();
    void initialize(QString id_reader);

    bool book_Return();//выдать книгу





private slots:
    void closeEvent(QCloseEvent *e);
    void agreeReleased();
    void slotClikTable(const QModelIndex &index);
    void edited_Search(QString);
    void formPenaltyDestroy(int result);
};

#endif // FORM_BOOK_RETURN_H
