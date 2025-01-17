#include "interfejs.h"
#include "ui_interfejs.h"
#include "konekcija.h"
#include "dialog.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QObject>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QFileDialog>
#include <QDir>
#include <QListWidgetItem>
interfejs::interfejs(QWidget *parent, QString ime, QString lozinka, QString status) :
    QDialog(parent),
    ui(new Ui::interfejs)
{
    ui->setupUi(this);
    this->K_ime=ime;
    this->k_lozinka=lozinka;
    this->K_status=status;
    for (int i=0;i<5 ;i++ ) {
        ui->sort_obj->setItemData(i, QBrush(Qt::white), Qt::TextColorRole);
    }
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    qDebug()<<K_ime<<k_lozinka<<K_status;
    if(status!="head_admin"){ui->odjava->setContentsMargins(0,50,0,0);
        ui->prikaz_baze_Arh->hide();}
    else ui->prikaz_baze_Arh->show();

    //createConnection(Adr_baza);
    konekcija(Adr_baza);
    ui->liste->setCurrentWidget(ui->lista_1);
    ui->pregled_R->resizeColumnsToContents();
    on_prikaz_baze_clicked();
}

interfejs::~interfejs()
{
    delete ui;

}

bool interfejs::konekcija(QString s){

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(s);
    if (db.open()) {
        postaviPodatke();
        QFile satnica(Sat_baza);
        file = &satnica;
        readData();
        return true;
        } else{
        postaviPodatke();

    QMessageBox::critical(nullptr, QObject::tr("Baza ne može biti otvorena"),
                       QObject::tr("Konekcija sa bazom nije uspjela.\n"
                                  "Kliknite na Cancel za izlaz."), QMessageBox::Cancel);

     return false;}

}
void interfejs::postaviPodatke(){


      QString imeB="";
      int n=0;
        for(int i=Adr_baza.length();i>0;i--){
            if(Adr_baza[i]=='/'){ n=i+1; break;}
            }
            for(int i=n;i<Adr_baza.length();i++){
             imeB+= Adr_baza[i];
          }
            QString imeBs="";
            int ni=0;
              for(int i=Sat_baza.length();i>0;i--){
                  if(Sat_baza[i]=='/'){ ni=i+1; break;}
                  }
                  for(int i=ni;i<Sat_baza.length();i++){
                   imeBs+= Sat_baza[i];
                }

    QString s=K_ime+"       STATUS - "+K_status+"       Baza radnika: "+imeB+"       Satnica radnika: "+imeBs;
    ui->podatci->setText(s);
}
void interfejs::readData()
{
    if (!file->open(QIODevice::ReadOnly)){
        ui->error_label_3->setText("!!!!");return;
 }

    if (Data.setContent(file)) {
        ui->error_label_3->setText("!!!!");file->close();
        return;
    }
    if (Data.isNull()) {
        ui->error_label_3->setText("!!!!");file->close();
        return;
    }


    file->close();
}
void interfejs::border(int n){
    ui->prikaz_baze->setStyleSheet("QPushButton{border:0px solid;border-right: 0px solid;color:#fff;}QPushButton:hover{background-color: rgb(17, 51, 68);}");
    ui->dodaj_R->setStyleSheet("QPushButton{border:0px solid;border-right: 0px solid;color:#fff;}QPushButton:hover{background-color: rgb(17, 51, 68);}");
    ui->Izmjena_R->setStyleSheet("QPushButton{border:0px solid;border-right: 0px solid;color:#fff;}QPushButton:hover{background-color: rgb(17, 51, 68);}");
    ui->izbrisi_R->setStyleSheet("QPushButton{border:0px solid;border-right: 0px solid;color:#fff;}QPushButton:hover{background-color: rgb(17, 51, 68);}");
    ui->konekcija->setStyleSheet("QPushButton{border:0px solid;border-right: 0px solid;color:#fff;}QPushButton:hover{background-color: rgb(17, 51, 68);}");
    switch (n) {
    case 1:ui->prikaz_baze->setStyleSheet("QPushButton{	border:0px solid;border-right: 4px solid rgb(85, 170, 255);color:#fff;}QPushButton:hover{background-color: rgb(17, 51, 68);}");break;
    case 2:ui->dodaj_R->setStyleSheet("QPushButton{	border:0px solid;border-right: 4px solid rgb(85, 170, 255);color:#fff;}QPushButton:hover{background-color: rgb(17, 51, 68);}");break;
    case 3:ui->Izmjena_R->setStyleSheet("QPushButton{	border:0px solid;border-right: 4px solid rgb(85, 170, 255);color:#fff;}QPushButton:hover{background-color: rgb(17, 51, 68);}");break;
    case 4:ui->izbrisi_R->setStyleSheet("QPushButton{	border:0px solid;border-right: 4px solid rgb(85, 170, 255);color:#fff;}QPushButton:hover{background-color: rgb(17, 51, 68);}");break;
    case 5:ui->konekcija->setStyleSheet("QPushButton{	border:0px solid;border-right: 4px solid rgb(85, 170, 255);color:#fff;}QPushButton:hover{background-color: rgb(17, 51, 68);}");break;
    }
}

void interfejs::on_toggle_btn_clicked()
{

    int width=ui->lijev_panel->width();
    int maxWidth=250;
    int standard=70;

    if(width==70){
     ui->lijev_panel->setMinimumWidth(maxWidth);
     ui->prikaz_baze->setText(" Baza radnika");
     ui->dodaj_R->setText(" Dodaj radnika");
     ui->Izmjena_R->setText(" Izmjeni radnika");
     ui->izbrisi_R->setText(" Izbrisi radnika");
     ui->konekcija->setText(" Konekcija baza");
     ui->sortitraj_R->setText(" Sortiraj");
     ui->satnica_R->setText(" Satnica radnika");
     ui->odjava_R->setText(" Odjavi se");
     ui->prikaz_baze_Arh->setText(" Baza korisnika");
    }
    else {
        maxWidth=standard;
        ui->lijev_panel->setMinimumWidth(maxWidth);
        ui->sortitraj_R->setText("");
        ui->satnica_R->setText("");
        ui->konekcija->setText("");
        ui->izbrisi_R->setText("");
        ui->Izmjena_R->setText("");
        ui->dodaj_R->setText("");
        ui->prikaz_baze->setText("");
        ui->odjava_R->setText("");
        ui->prikaz_baze_Arh->setText("");
    }

    //animacija
    animation= new QPropertyAnimation(ui->lijev_panel, "minimumWidth");
    animation->setDuration(400);
    animation->setStartValue(width);
    animation->setEndValue(maxWidth);
    animation->start();
}

void interfejs::on_prikaz_baze_clicked()
{
    border(1);
    ui->liste->setCurrentWidget(ui->lista_1);
    ui->error_label->clear();
    ui->error_label_2->clear();
    ui->error_label_3->clear();
    QSqlQuery qry;
    QSqlQueryModel *model=new QSqlQueryModel();
    if(p==true){qry.prepare("select *  from korisnici;");}
    else qry.prepare("select *  from radnici_inf;");
    qry.exec();

    model->setQuery(qry);
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Ime"));
    model->setHeaderData(2, Qt::Horizontal, tr("Prezime"));
    model->setHeaderData(3, Qt::Horizontal, tr("Struka"));
    model->setHeaderData(4, Qt::Horizontal, tr("Pozicija"));
    ui->pregled_R->setModel(model);
    ui->pregled_R->resizeColumnsToContents();
    ui->pregled_R->horizontalHeader()->stretchLastSection();
    ui->pregled_R->horizontalHeader()->setStyleSheet("border-left:2px solid rgb(85, 170, 255);border-radius: 7px;");
    ui->pregled_R->setColumnWidth(1,150);
    ui->pregled_R->setColumnWidth(2,150);
    ui->pregled_R->setColumnWidth(3,200);
    ui->pregled_R->horizontalHeader()->setVisible(true);
    ui->pregled_R->verticalHeader()->setVisible(false);
}//rgb(85, 170, 255)

void interfejs::on_dodaj_R_clicked()
{
    try {
        if(K_status=="korisnik"){
           throw "ERROR: Korisnici nemaju prioritet dodavanjem radnika!";
        }
    }  catch (const char *chr) {
        ui->error_label_3->setStyleSheet("QLabel {color : red; }");
        ui->error_label_3->setText(chr);
        return;
    }

    ui->liste->setCurrentWidget(ui->lista_2);
    border(2);
    connect(ui->dodaj, &QPushButton::released,this,&interfejs::dodaj);

}

void interfejs::on_Izmjena_R_clicked()
{
    if(ui->liste->currentWidget()!=ui->lista_1){
        ui->liste->setCurrentWidget(ui->lista_1);border(1);
        return;}
    try {
        if(K_status=="korisnik"){
           throw "ERROR: Korisnici nemaju prioritet izmjenom radnika!";
        }
    }  catch (const char *chr) {
        ui->error_label_3->setStyleSheet("QLabel {color : red; }");
        ui->error_label_3->setText(chr);return;
    }

    QModelIndex index = ui->pregled_R->currentIndex();
    QMessageBox msgBox;
    int id = ui->pregled_R->model()->data(index).toInt();

    try {       qDebug()<<id;
            if(id==0){
            throw "ERROR: Pogresan unos. Niste odabrali ID radnika!";
        }
    }  catch (const char *chr) {
        ui->error_label_3->setStyleSheet("QLabel {color : red; }");
        ui->error_label_3->setText(chr);return;
    }//DELETE FROM radnici_inf WHERE ID=:ID


    qDebug()<<id<<endl;
    izmjeni(id);
}

void interfejs::dodaj(){
    ui->error_label->clear();
    QString Ime,Prezime,Struka,Pozicija;
    Ime=ui->R_ime->text();
    Prezime=ui->R_prezime->text();
    Struka=ui->R_struka->text();
    Pozicija=ui->R_pozicija->text();
    QSqlQuery qry;
    try {
        if(ui->R_ime->text().isEmpty() || ui->R_prezime->text().isEmpty() || ui->R_pozicija->text().isEmpty())
        {
               throw QString("POGRESAN UNOS! Niste nista unijeli!");
           }
        if(p==true) {
            if(ui->R_pozicija->text()!=QString("korisnik") && ui->R_pozicija->text()!=QString("admin") && ui->R_pozicija->text()!=QString("head_admin"))
                    {
                           throw QString("POGRESAN UNOS statusa! Status moze samo biti jednak korisnik, admin ili head_admin!");
                       }
        }
    }  catch (QString s) {
        ui->error_label->setText(s);
        return;
    }
    if(p==true){qry.prepare("insert into korisnici values(NULL,'"+Ime+"','"+Prezime+"','"+Pozicija+"');");}
    else {qry.prepare("insert into radnici_inf values(NULL,'"+Ime+"','"+Prezime+"','"+Struka+"','"+Pozicija+"');");}
    qDebug()<<qry.exec()<<endl;
    ui->R_ime->setText("");
    ui->R_prezime->setText("");
    ui->R_struka->setText("");
    ui->R_pozicija->setText("");
    ui->error_label->clear();
    ui->error_label->setStyleSheet("QLabel {color : rgb(85, 170, 255); }");
    ui->error_label->setText("upit izvrsen :)");
    return;


}

void interfejs::izmjeni(const int &id){
    ui->liste->setCurrentWidget(ui->lista_3);
    border(3);
    ui->error_label_3->clear();
    QSqlQuery qry;
    if(p==true){qry.prepare("SELECT * FROM korisnici WHERE ID=:ID;");}
    else qry.prepare("SELECT * FROM radnici_inf WHERE ID=:ID;");
    qry.bindValue(":ID",id);
    if(qry.exec())
         {
           while(qry.next())
             {
               //ui->R_id_I->setText(qry.value(0).toString());
              ids=qry.value(0).toInt();
               ui->R_ime_I->setText(qry.value(1).toString());
               ui->R_prezime_I->setText(qry.value(2).toString());
               if(p==true){ui->R_pozicija_I->setText(qry.value(3).toString()); goto to;}

               ui->R_struka_I->setText(qry.value(3).toString());
               ui->R_pozicija_I->setText(qry.value(4).toString());
            }
             to:qry.first();
             ui->error_label_2->setStyleSheet("QLabel {color : rgb(85, 170, 255); }");
             ui->error_label_2->setText("Upit se može izvršiti :)");
    }
       else
            {
               ui->error_label_2->setStyleSheet("QLabel {color : red; }");
               ui->error_label_2->setText("Upit se ne može izvršiti!");
            }
}

void interfejs::on_izmjena_clicked()
{
    QString Ime,Prezime,Struka,Pozicija;

    Ime=ui->R_ime_I->text();
    Prezime=ui->R_prezime_I->text();
    Struka=ui->R_struka_I->text();
    Pozicija=ui->R_pozicija_I->text();

    try {
        if(ui->R_ime_I->text().isEmpty() || ui->R_prezime_I->text().isEmpty() || ui->R_pozicija_I->text().isEmpty())
        {
               throw QString("POGRESAN UNOS! Niste nista unijeli!");
           }
        if(p==true) {
            if(ui->R_pozicija_I->text()!=QString("korisnik") && ui->R_pozicija_I->text()!=QString("admin") && ui->R_pozicija_I->text()!=QString("head_admin"))
                    {
                           throw QString("POGRESAN UNOS! Status moze samo biti jednak korisnik, admin ili head_admin!");
                       }
        }
    }  catch (QString s) {
        ui->error_label_2->setStyleSheet("QLabel {color : red; }");
        ui->error_label_2->setText(s);
        return;
    }

    QSqlQuery qry;
    if(p==true){qry.prepare("UPDATE korisnici SET korisnicko_ime=:IME, lozinka=:PRE, status=:POZ WHERE ID=:ID;");}
    else qry.prepare("UPDATE radnici_inf SET ime=:IME, prezime=:PRE, struka=:STR, pozicija=:POZ WHERE ID=:ID;");
    qry.bindValue(":ID",ids);
    qry.bindValue(":IME",Ime);
    qry.bindValue(":PRE",Prezime);
    qry.bindValue(":STR",Struka);
    qry.bindValue(":POZ",Pozicija);
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox {background-color: rgb(14, 42, 54);}QMessageBox QLabel {color: #fff;}");
    msgBox.setText("Izmjena radnika.");
    msgBox.setInformativeText("Da li ste sigurni da želite izmjeniti radnika?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
        if(ret==QMessageBox::Yes)
                {
                if(qry.exec())
                    {
                        QMessageBox::information(this,"", "Slog izmjenjen!");
                        return;
                    }
               else
                  {
                    QMessageBox::information(this,"", "Upit se ne može izvršiti!");
                }
                }
        ui->error_label_2->clear();
        ui->error_label_2->setStyleSheet("QLabel {color : rgb(85, 170, 255); }");
        ui->error_label_2->setText("upit izvrsen :)");
}

void interfejs::on_izbrisi_R_clicked()
{
    if(ui->liste->currentWidget()!=ui->lista_1){
        ui->liste->setCurrentWidget(ui->lista_1);
        return;}
    try {
        if(K_status=="korisnik"){
           throw "ERROR: Korisnici nemaju prioritet brisanjem radnika!";
        }
    }  catch (const char *chr) {
        ui->error_label_3->setStyleSheet("QLabel {color : red; }");
        ui->error_label_3->setText(chr);
        return;
    }
    ui->error_label_3->clear();
    QString s;
    QModelIndex index = ui->pregled_R->currentIndex();
    QMessageBox msgBox;
    int id = ui->pregled_R->model()->data(index).toInt();
    s=ui->pregled_R->model()->data(index).toString();

    try {       qDebug()<<id;
            if(id==0){
            throw "ERROR: Pogresan unos. Niste odabrali ID radnika!";
        }
    }  catch (const char *chr) {
        ui->error_label_3->setStyleSheet("QLabel {color : red; }");
        ui->error_label_3->setText(chr);return;
    }

    QSqlQuery qry;
    if(p==true){qry.prepare("DELETE FROM korisnici WHERE ID=:ID;");}
    else qry.prepare("DELETE FROM radnici_inf WHERE ID=:ID;");
    qry.bindValue(":ID",id);
    msgBox.setStyleSheet("QMessageBox {background-color: rgb(14, 42, 54);}QMessageBox QLabel {color: #fff;}");
    msgBox.setText("Brisanje radnika.");
    msgBox.setInformativeText("Da li ste sigurni da želite obrisati radnika?");
    border(4);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
        if(ret==QMessageBox::Yes)
                {
                    QMessageBox::information(this,"", "Slog obrisan!");
                    qry.exec();
                    on_prikaz_baze_clicked();
                 }
        on_prikaz_baze_clicked();
}

void interfejs::on_odjava_R_clicked()
{
    QMessageBox msgBox;
    msgBox.setStyleSheet("QMessageBox {background-color: rgb(14, 42, 54);}QMessageBox QLabel {color: #fff;}");
    msgBox.setText("logout->"+K_ime+"");
    msgBox.setInformativeText("Da li ste sigurni da želite se odjaviti?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
        if(ret==QMessageBox::Yes)
                {
            close();
            Dialog i;
            i.setModal(true);
            i.exec();
                 }
    else return;
}

void interfejs::on_konekcija_clicked()
{
    if(p==true) {return;}
        ui->error_label_3->clear();
        ui->liste->setCurrentWidget(ui->konekcija_baza);
        border(5);
        //connect(ui->dodaj_db_adresa, &QPushButton::pressed,this,&interfejs::dodaj_db);
        //connect(ui->dodaj_xml_adresa, &QPushButton::pressed,this,&interfejs::dodaj_xml);
}

void interfejs::on_prikaz_baze_Arh_clicked()
{
    if(p==false){
        ui->prikaz_baze_Arh->setStyleSheet("color: rgb(255, 255, 255);border:0px solid;background-color:rgb(175, 215, 255);");
        p=true;
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
        on_prikaz_baze_clicked();
        ui->R_struka->hide();ui->R_struka_I->hide();
        ui->R_ime->setPlaceholderText("korisnicko ime");ui->R_ime_I->setPlaceholderText("korisnicko ime");
        ui->R_prezime->setPlaceholderText("lozinka");ui->R_prezime_I->setPlaceholderText("lozinka");
        ui->R_pozicija->setPlaceholderText("status");ui->R_pozicija_I->setPlaceholderText("status");
        ui->sort_obj->clear();
        ui->sort_obj->addItem("ID");
        ui->sort_obj->addItem("korisnicko_ime");
        ui->sort_obj->addItem("lozinka");
        ui->sort_obj->addItem("status");
        for (int i=0;i<5 ;i++ ) {
            ui->sort_obj->setItemData(i, QBrush(Qt::white), Qt::TextColorRole);
        }
    }
    else {
        ui->prikaz_baze_Arh->setStyleSheet("color: rgb(255, 255, 255);border:0px solid;background-color:rgb(14, 42, 54);");
        p=false;
        ui->R_struka->show();ui->R_struka_I->show();
        konekcija(Adr_baza);
        on_prikaz_baze_clicked();
        ui->R_ime->setPlaceholderText("ime");ui->R_ime_I->setPlaceholderText("ime");
        ui->R_prezime->setPlaceholderText("prezime");ui->R_prezime_I->setPlaceholderText("prezime");
        ui->R_pozicija->setPlaceholderText("pozicija");ui->R_pozicija_I->setPlaceholderText("pozicija");
        ui->sort_obj->clear();
        ui->sort_obj->addItem("ID");
        ui->sort_obj->addItem("ime");
        ui->sort_obj->addItem("prezime");
        ui->sort_obj->addItem("struka");
        ui->sort_obj->addItem("pozicija");
        for (int i=0;i<5 ;i++ ) {
            ui->sort_obj->setItemData(i, QBrush(Qt::white), Qt::TextColorRole);
        }

    }

}

void interfejs::on_dodaj_db_clicked()
{
    Adr_baza=ui->baza_Radnika->text();
    if(konekcija(Adr_baza)==true){
        QMessageBox::information(nullptr, QObject::tr("Baza radnika je povezana"),
                                        QObject::tr("Konekcija sa bazom je uspjela.\n"
                                                   ), QMessageBox::Ok);
    }

}
void interfejs::on_dodaj_xml_clicked()
{
    Sat_baza=ui->Baza_Satnice->text();
    postaviPodatke();
    QFile satnica(Sat_baza);
    file = &satnica;
    readData();


}
void interfejs::on_dodaj_db_adresa_clicked()
{
    QString baza_db=QFileDialog::getOpenFileName(this,"lokacija baze radnika",QDir::homePath(),"*.db");
    ui->baza_Radnika->setText(baza_db);
}

void interfejs::on_dodaj_xml_adresa_clicked()
{
    QString baza_xml=QFileDialog::getOpenFileName(this,"lokacija baze korisnika",QDir::homePath(),"*.xml");
    ui->Baza_Satnice->setText(baza_xml);
}

void interfejs::on_sortitraj_R_clicked()
{
    QString at, sort;
    at= ui->sort_obj->currentText();
    sort= ui->naziv_sort->text();

    QSqlQuery qry;
    QSqlQueryModel *model=new QSqlQueryModel();
    if(p==true){qry.prepare("select * from korisnici where "+at+" like '"+sort+"%' order by 'BEST MATCH';"); }
    else qry.prepare("select *  from radnici_inf where "+at+" like '"+sort+"%' order by 'BEST MATCH';");
    qry.exec();

    model->setQuery(qry);
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Ime"));
    model->setHeaderData(2, Qt::Horizontal, tr("Prezime"));
    model->setHeaderData(3, Qt::Horizontal, tr("Struka"));
    model->setHeaderData(4, Qt::Horizontal, tr("Pozicija"));
    ui->pregled_R->setModel(model);

}
//for (int i=0;i<ukEl;i++) {
  //  qDebug()<<ui->pregled_R->model()->data(ui->pregled_R->model()->index(i,0)).toInt();
//}
void interfejs::on_satnica_R_clicked()
    {
        if(p==true){return;}
        if(ui->liste->currentWidget()!=ui->lista_1){
            ui->liste->setCurrentWidget(ui->lista_1);border(1);
            return;}


        QModelIndex index = ui->pregled_R->currentIndex();
        int indexRow = ui->pregled_R->currentIndex().row();
        qDebug()<<"indexRow";
        qDebug()<<indexRow;
        QMessageBox msgBox;
        int id = ui->pregled_R->model()->data(index).toInt();

        try {
                if(id==0){
                throw "ERROR: Pogresan unos. Niste odabrali ID radnika!";
            }
        }  catch (const char *chr) {
            ui->error_label_3->setStyleSheet("QLabel {color : red; }");
            ui->error_label_3->setText(chr);return;
        }
        ui->error_label->clear();
        ui->error_label_2->clear();
        ui->error_label_3->clear();
        QSqlQuery qry;
        QSqlQueryModel *model=new QSqlQueryModel();
        qry.prepare("select ID,Ime,Prezime from radnici_inf;");
        qry.exec();

        model->setQuery(qry);
        int ukEl=model->rowCount();
        model->clear();


        QDomNodeList radnici = Data.elementsByTagName("radnik");
        for (int i = 0; i < radnici.count(); ++i) {
            QDomNode radnik = radnici.item(i);
            QDomNodeList tracks = radnik.childNodes();
            QDomNode track;

            int a;
            int b;
            int c;

            for (int i = 0; i < tracks.count(); ++i) {

                track = tracks.item(i);
                b = track.toElement().attribute("n").toInt();
                a= track.toElement().text().toInt();

                c=a*b;

                qDebug()<<radnik.toElement().attribute("ID");
                QString stanje="\n";
                if(b<136) stanje="\nnedovoljan broj sati!\n";
                for (int i=0;i<ukEl;i++) {
                    if(radnik.toElement().attribute("ID").toInt()==id){
                        QMessageBox msg;
                        msg.setStyleSheet("QMessageBox {background-color: rgb(14, 42, 54);}QMessageBox QLabel {color: #fff;}");
                        msg.setText("satnica radnika?");
                        QString si="ID: "+radnik.toElement().attribute("ID")+"\nIme: "+ui->pregled_R->model()->data(ui->pregled_R->model()->index(indexRow,1)).toString()+"\nPrezime: "+ui->pregled_R->model()->data(ui->pregled_R->model()->index(indexRow,2)).toString()+"\nPozicija: "+ui->pregled_R->model()->data(ui->pregled_R->model()->index(indexRow,4)).toString()+"\nUkupnpo sati rada: "+QString::number(b) + "h\nSatnica po satu: "+ QString::number(a)+"km\n"+"Ukupna plata radnika: "+QString::number(c)+"km\n"+stanje;
                        msg.setInformativeText(si);
                        msg.exec();
                        return;
                    }
                }

            }}}



void interfejs::on_izlaz_clicked()
{
    close();
}

void interfejs::on_minimiziraj_clicked()
{
    setWindowState(Qt::WindowMinimized);
}
