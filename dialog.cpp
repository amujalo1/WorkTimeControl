#include "dialog.h"
#include "ui_dialog.h"
#include "konekcija.h"
#include "interfejs.h"
#include <QFileDialog>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //createConnection("E:/Qt/radovi/korisnici(1).db");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("E:/Qt/radovi/korisnici(1).db");
    vr:db.open();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM korisnici");
    if(!db.isOpen() || !qry.exec()){
        QMessageBox msgBox;
        msgBox.setStyleSheet("QMessageBox {background-color: rgb(14, 42, 54);}QMessageBox QLabel {color: #fff;}");
        msgBox.setText("pogresan unos baze!");
        msgBox.exec();
            QString baza_db=QFileDialog::getOpenFileName(this,"lokacija baze radnika",QDir::homePath(),"*.db");
            db.setDatabaseName(baza_db);
            goto vr;
    }



    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);


}

Dialog::~Dialog()
{
    delete ui;
}



void Dialog::on_submit_clicked()
{
qDebug()<<ui->K_ime->text()<<endl;
qDebug()<<ui->Lozinka->text()<<endl;
    QSqlQuery qry;
    qry.prepare("SELECT * FROM korisnici WHERE korisnicko_ime='"+ui->K_ime->text()+"' AND lozinka='"+ui->Lozinka->text()+"';");
qDebug()<<qry.exec()<<endl;

    if(qry.next()){

        this->K_ime=ui->K_ime->text();
        this->K_lozinka=ui->Lozinka->text();
        status=qry.value(3).toString();
        close();
        qry.clear();
        interfejs i(0,K_ime,K_lozinka,status);
        i.setModal(true);
        i.exec();
    }
    else{ ui->label->setText("POGREŠAN UNOS!!"); ui->Lozinka->setText("");}
}

void Dialog::on_pas_V_pressed()
{
    ui->Lozinka->setEchoMode(QLineEdit::Normal);
}

void Dialog::on_pas_V_released()
{
    ui->Lozinka->setEchoMode(QLineEdit::Password);
}

void Dialog::on_exit_clicked()
{
    close();
}

void Dialog::on_minimiziraj_clicked()
{
    setWindowState(Qt::WindowMinimized);
}
