#ifndef FORM_WRITEOFF_BOOKS_H
#define FORM_WRITEOFF_BOOKS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>

#include "bd.h"

class Form_WriteOff_Books : public QDialog
{
    Q_OBJECT
public:
    explicit Form_WriteOff_Books(const QString &bookSbn, QWidget *parent = 0);
    ~Form_WriteOff_Books();
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QString bookSbn;
    QString requestForSelect;//запрос для бызы
    QString requestForUpdate;//запрос для бызы

    QString verification;//вопрос для пользователя о подтверждении действий

    QPlainTextEdit *plaintText;
    QPushButton *agree;//да
    QPushButton *cancel;//нет
private:
    int result;

    void initialize(QString bookSbn);

    void generateAsk();//генерирует вопрос verification
    void make_WriteOff();//списать книги

private slots:
    void closeEvent(QCloseEvent *e);
    void agreeReleased();
    void cancelReleased();

};

#endif // FORM_WRITEOFF_BOOKS_H
