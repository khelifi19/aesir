#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include<QIntValidator>
#include <QDate>
#include "client.h"
#include <cctype>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(0, 999999, this));
    ui->le_id_supp->setValidator(new QIntValidator(0, 999999, this));
    ui->le_id_modifier->setValidator(new QIntValidator(0, 999999, this));
  ui->le_num_modifier->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_num->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_date->setDate(QDate::currentDate());

    ui->tab_client->setModel(C.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->le_id->text().toInt();
    if (ui->le_id->text().isEmpty()) { // Vérifie si id est vide
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ ID ne doit pas être vide."));
        return;
    }

   Client C1;
    if (C1.existeId(id)) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Cet ID existe déjà dans la base de données."));
        return;
    }
    QString nom=ui->le_nom->text();
    if (nom.isEmpty() || !nom.at(0).isUpper()) { // vérifie si nom est vide ou sa première lettre n'est pas en majuscule
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ nom doit être non vide et sa première lettre doit être en majuscule."));
        return;
    }
    QString prenom=ui->le_prenom->text();
    if (prenom.isEmpty() || !prenom.at(0).isUpper()) { // vérifie si prenom est vide ou sa première lettre n'est pas en majuscule
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ prenom doit être non vide et sa première lettre doit être en majuscule."));
        return;
    }
    QString adresse=ui->le_adresse->text();
    if (adresse.isEmpty() ) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ adresse doit être non vide "));
        return;}
    QString str_num = ui->le_num->text(); // récupérer la chaîne de caractères saisie
    bool ok;
    long num = str_num.toLong(&ok); // convertir en long et stocker dans la variable "num"

    if (!ok || str_num.length() != 8) { // vérifier si la conversion a échoué ou si la longueur n'est pas égale à 8
        // afficher un message d'erreur
        QMessageBox::warning(this, "Erreur", "Le numéro doit contenir 8 chiffres !");
        return;}


    QString charge=ui->le_charge->currentText();
    if (charge.isEmpty() ) { // vérifie si nom est vide ou sa première lettre n'est pas en majuscule
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ charge doit être non vide "));
        return;
    }


    QDate date=ui->le_date->date();
            Client C(id,nom,prenom,adresse,num,charge,date);
            bool test=C.ajouter();
            if (test)
            {
               ui->tab_client->setModel(C.afficher());
                QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Ajout effectué\n""Click Cancel to exit."),QMessageBox::Cancel);

                ui->le_id->clear();
                ui->le_nom->clear();
                ui->le_prenom->clear();
                  ui->le_adresse->clear();
                    ui->le_num->clear();
                    ui->le_charge->clear();
                    ui->le_date->clear();


            }
            else
                QMessageBox::critical(nullptr,QObject::tr("Not OK"),QObject::tr("Ajout non effectué.\n""click cancel to exit."),QMessageBox::Cancel);
         }




void MainWindow::on_pb_supprimer_clicked()
{
    Client C1; C1.setid(ui->le_id_supp->text().toInt());
    bool test= C1.supprimer(C1.getid());
    QMessageBox msgBox;
    if (test){

        msgBox.setText("suppression avec succes. ");
        ui->tab_client->setModel(C.afficher());
        ui->le_id_supp->clear();
        ui->tab_client->setModel(C.afficher());
        ui->le_id_modifier->clear();
        ui->le_nom_modifier->clear();
        ui->le_prenom_modifier->clear();
          ui->le_adresse_modifier->clear();
            ui->le_num_modifier->clear();
            ui->le_charge_modifier->clear();
            ui->le_date_modifier->clear();
    }

            else
            msgBox.setText("L'id n'existe pas. ");
    msgBox.exec();
}
void MainWindow::on_tab_client_activated(const QModelIndex &index)
{
    QString val=ui->tab_client->model()->data(index).toString();
    QSqlQuery a;
   a.prepare("SELECT * FROM CLIENT WHERE id='"+val+"' ");
    if (a.exec())
    { while (a.next())
        {
            //update
            //id
            ui->le_id_modifier->setText(a.value(0).toString());
            ui->le_nom_modifier->setText(a.value(1).toString());
            ui->le_prenom_modifier->setText(a.value(2).toString());
            ui->le_adresse_modifier->setText(a.value(3).toString());
            ui->le_num_modifier->setText(a.value(4).toString());
               ui->le_charge_modifier->setCurrentText(a.value(5).toString());
                   QString dateString = a.value(6).toString();
                   QDate date = QDate::fromString(dateString, "yyyy/dd/MM");
                   ui->le_date_modifier->setDate(date);



            //delete
            //id
            ui->le_id_supp->setText(a.value(0).toString()); //pour supprimer


        }
    }
}


void MainWindow::on_pb_modifier_clicked()
{
    int id=ui->le_id_modifier->text().toInt();
    if (ui->le_id->text().isEmpty()) { // Vérifie si id est vide
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ ID ne doit pas être vide."));
        return;
    }
    QString nom=ui->le_nom_modifier->text();
    if (nom.isEmpty() || !nom.at(0).isUpper()) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ nom doit être non vide et sa première lettre doit être en majuscule."));
        return;}
    QString prenom=ui->le_prenom_modifier->text();
    if (prenom.isEmpty() || !prenom.at(0).isUpper()) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ prenom doit être non vide et sa première lettre doit être en majuscule."));
        return;}
    QString adresse=ui->le_adresse_modifier->text();
    if (adresse.isEmpty() ) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ adresse doit être non vide "));
        return;}

   QString str_num = ui->le_num->text(); // récupérer la chaîne de caractères saisie
   bool ok;
   long num = str_num.toLong(&ok); // convertir en long et stocker dans la variable "num"

   if (!ok || str_num.length() != 8) { // vérifier si la conversion a échoué ou si la longueur n'est pas égale à 8
       // afficher un message d'erreur
       QMessageBox::warning(this, "Erreur", "Le numéro doit contenir 8 chiffres !");
       return;}

    QString charge=ui->le_charge_modifier->currentText();
    if (charge.isEmpty() ) { // vérifie si nom est vide ou sa première lettre n'est pas en majuscule
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ charge doit être non vide "));
        return;
    }


    QDate date=ui->le_date_modifier->date();
            Client C(id,nom,prenom,adresse,num,charge,date);
    bool test=C.modifier(id ,nom,prenom,adresse,num,charge,date);
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("modifié \n"
                                             "click to cancel"), QMessageBox::Cancel);
ui->tab_client->setModel(C.afficher());
ui->le_id_modifier->clear();
ui->le_nom_modifier->clear();
ui->le_prenom_modifier->clear();
  ui->le_adresse_modifier->clear();
    ui->le_num_modifier->clear();
    ui->le_charge_modifier->clear();
    ui->le_date_modifier->clear();

    }
else
    QMessageBox::critical(nullptr,QObject::tr("not ok"),
                          QObject::tr("modification non effectué"),QMessageBox::Cancel);
}



void MainWindow::on_tri_id_clicked()
{

        ui->tab_tri->setModel(C.trie_id());


}


void MainWindow::on_tri_nom_clicked()
{
    ui->tab_tri->setModel(C.trie_nom());
}

void MainWindow::on_tri_date_clicked()
{
    ui->tab_tri->setModel(C.trie_date());
}
