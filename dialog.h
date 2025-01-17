#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();


private slots:
    void on_submit_clicked();

    void on_pas_V_pressed();

    void on_pas_V_released();

    void on_exit_clicked();

    void on_minimiziraj_clicked();

private:
    Ui::Dialog *ui;
    QString K_ime,K_lozinka, status;


};
#endif // DIALOG_H
