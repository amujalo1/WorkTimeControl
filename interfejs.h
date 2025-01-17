#ifndef INTERFEJS_H
#define INTERFEJS_H

#include <QDialog>
#include <QPropertyAnimation>
#include "konekcija.h"
#include <QtCore>
#include <QtGui>
namespace Ui {
class interfejs;
}

class interfejs : public QDialog
{
    Q_OBJECT

public:
    explicit interfejs(QWidget *parent = nullptr, QString ime="",QString lozinka="",QString status="");
    ~interfejs();
    void dodaj();
    void izmjeni(const int &id);
    void border(int n);
    bool konekcija(QString s);




private slots:


    void on_toggle_btn_clicked();

    void on_prikaz_baze_clicked();

    void on_dodaj_R_clicked();

    void on_Izmjena_R_clicked();

    void on_izmjena_clicked();

    void on_izbrisi_R_clicked();

    void on_odjava_R_clicked();

    void on_konekcija_clicked();

    void on_prikaz_baze_Arh_clicked();

    void on_dodaj_db_clicked();

    void on_dodaj_db_adresa_clicked();

    void on_dodaj_xml_adresa_clicked();

    void on_sortitraj_R_clicked();

    void on_satnica_R_clicked();



    void on_dodaj_xml_clicked();

    void on_izlaz_clicked();

    void on_minimiziraj_clicked();

private:
    void readData();
    void postaviPodatke();
    Ui::interfejs *ui;
    QString K_ime, k_lozinka,  K_status, Adr_baza="E:/Qt/Personal_01/radnici.db", Kr_baza="E:/Qt/radovi/korisnici(1).db", Sat_baza="E:/Qt/radovi/M_Rad/satnica.xml";
    QPropertyAnimation *animation;
    QDomDocument Data;
    QFile *file;
    QStandardItemModel *unos;
    int ids;
    bool p=false;


};

#endif // INTERFEJS_H
