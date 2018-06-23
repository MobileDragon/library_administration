#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QVector>
#include <QComboBox>
#include <QPushButton>
#include <QTableView>
#include <QStandardItem>
#include <QLineEdit>
#include <QDebug>
#include <QMessageBox>

#include "bd.h"
#include "tableviewofbase.h"
#include "form_writeoff_books.h"
#include "form_login.h"
#include "form_book_issue.h"
#include "form_book_return.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void displayRequest();

private slots:

private:
    Ui::MainWindow *ui;
    //QVector<QVBoxLayout*> tabLayouts;//виджеты для трех вкладок tabWidget
    //QVector<QWidget*> gerbage;//прочий мусор который нужно удалить по заекрытию окна

    //tab1
    QWidget *tab1;
    QVBoxLayout* tabLayout1;//главный группировщик для вкладки №1
    QComboBox *comboReaderGroup1;//выпадающий список интересующих читателей
    QLineEdit* lineSearch1;//строка для поиска по таблице
    TableViewOfBase *tableOfReaders1;//список читателей
    QComboBox *comboAction1;//выпадающий список действий с читателем
    QPushButton *buttonAgree1;//создание модального окна для выполнения действия

    QString selectedReaderId;//id выбранного читателя из таблицы
    //tab2
    QWidget *tab2;
    QVBoxLayout* tabLayout2;//главный группировщик для вкладки №2
    QComboBox *comboBookPopularity2;//выпадающий список для поиска популярных, или не популярных книг
    QLineEdit* lineSearch2;//строка для поиска по таблице
    TableViewOfBase *tableOfBooks2;//список книг
    QPushButton *buttonWriteOff2;//отметить выбранный ISBN из таблицы, как списанный

    QString selectedBookISBN;//ISBN выбранной книги
    //tab3//список книг
    QWidget *tab3;
    QVBoxLayout* tabLayout3;//главный группировщик для вкладки №3
    QLineEdit* lineSearch3;//строка для поиска по таблице
    TableViewOfBase *tableOfBooks3;//список книг


    void initialize();
    void buid();//постройка интерфейса пользователя
    void createTab1();//создание таблиц
    void createTab2();
    void createTab3();

    void updatetableOfReaders(int numRequest, QString search);//обновление сведений
    void updateTableOfPopularity(int numRequest, QString search);
    void updateTableOfBooks(QString search);

    void activateTab_1(bool flag);//активировать элемены управления
    void activateTab_2(bool flag);//активировать элемены управления

    bool isCanIssue();//проверить - можно ли выдвть книгу

private slots:
    void Reader_IndexChanged(int index);//при изменении выпадающего списка
    void Action_IndexChanged(int index);
    void BookPopularity_IndexChanged(int index);

    void edited_Search_1(QString s);//при редактировании строки поиска
    void edited_Search_2(QString s);
    void edited_Search_3(QString s);
    //
    void slotClikTable_1(const QModelIndex &index);//при выборе строки из таблици
    void slotClikTable_2(const QModelIndex &index);

    //кнопки
    void buttononAgree1_Released();
    void buttonWriteOff2_Released();

    //закрытие диалогового окна
    void formLoginDestroy(int result);
    void book_IssueDestroy(int result);
    void book_ReturnDestroy(int result);
    void verificationDestroy(int result);

};

#endif // MAINWINDOW_H
