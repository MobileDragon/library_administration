#ifndef FORM_PAYMENT_PENALTY_H
#define FORM_PAYMENT_PENALTY_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QLineEdit>

#include "bd.h"

class Form_Payment_Penalty : public QDialog
{
    Q_OBJECT
public:
    explicit Form_Payment_Penalty(const QString &bookInventory, QWidget *parent = 0);
    ~Form_Payment_Penalty();

    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QString bookInventory;
    QString requestForSelect;//запрос для бызы
    QString requestForUpdate;//запрос для бызы

    QString verification;//вопрос для пользователя о подтверждении действий

    QPlainTextEdit *plaintText;
    QLineEdit *lineAccount;
    QPushButton *agree;//да
    QPushButton *cancel;//нет
private:
    int result;
    int penaltyAccount;
    bool accountChanged;

    void initialize(QString bookInventory);

    void generateAsk();//генерирует вопрос verification
    void make_WriteOff();//списать книги

private slots:
    void closeEvent(QCloseEvent *e);
    void agreeReleased();
    void editedAccount(QString);
};

#endif // FORM_PAYMENT_PENALTY_H
