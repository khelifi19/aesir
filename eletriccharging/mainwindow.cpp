#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "station.h"
#include <QMessageBox>
#include<QIntValidator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(0, 999999, this));
    ui->le_emp->setValidator(new QIntValidator(0, 999999, this));
    ui->le_borne->setValidator(new QIntValidator(0, 999999, this));
    ui->le_id_supp->setValidator(new QIntValidator(0, 999999, this));
    ui->le_id_modif->setValidator(new QIntValidator(0, 999999, this));
    ui->le_emp_modif->setValidator(new QIntValidator(0, 999999, this));
    ui->le_borne_modif->setValidator(new QIntValidator(0, 999999, this));
    ui->tab_stat->setModel(s.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int id_station=ui->le_id->text().toInt();
    if (ui->le_id->text().isEmpty()) { // Vérifie si id est vide
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ ID ne doit pas être vide."));
        return;
    }
    station s1;
    if (s1.existeId(id_station)) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Cet ID existe déjà dans la base de données."));
        return;
    }
     int nb_emp=ui->le_emp->text().toInt();
      int nb_borne=ui->le_borne->text().toInt();
      QString nom_resp=ui->le_nom->text();
      if (nom_resp.isEmpty() || !nom_resp.at(0).isUpper()) { // vérifie si nom est vide ou sa première lettre n'est pas en majuscule
          QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ nom doit être non vide et sa première lettre doit être en majuscule."));
          return;
      }
      QString localisation=ui->le_loca->text();
      station S(id_station,nb_emp,nb_borne,nom_resp,localisation);
      bool test=S.ajouter();
      if (test)
      {
          ui->tab_stat->setModel(s.afficher());
          QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Ajout effectué\n""Click Cancel to exit."),QMessageBox::Cancel);
      ui->le_id->clear();
      ui->le_emp->clear();
      ui->le_borne->clear();
      ui->le_nom->clear();
      ui->le_loca->clear();

      }
      else
          QMessageBox::critical(nullptr,QObject::tr("Not OK"),QObject::tr("Ajot non effectué.\n""click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pb_supp_clicked()
{
    station S1;
    S1.setid(ui->le_id_supp->text().toInt());
    bool test= S1.supprimer(S1.getid());
    QMessageBox msgBox;
    if (test){
         ui->tab_stat->setModel(s.afficher());
        msgBox.setText("suppression avec succes. ");
        ui->le_id_supp->clear();
    }

            else
            msgBox.setText("id n'existe pas. ");
    msgBox.exec();
}

void MainWindow::on_pb_modifier_clicked()
{
    int id =ui->le_id_modif->text().toUInt();
    int nb_emp=ui->le_emp_modif->text().toUInt();
     int nb_borne=ui->le_borne_modif->text().toUInt();
    QString nom_resp =ui->le_nom_modif->text();
    if (nom_resp.isEmpty() || !nom_resp.at(0).isUpper()) { // vérifie si nom est vide ou sa première lettre n'est pas en majuscule
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ nom doit être non vide et sa première lettre doit être en majuscule."));
        return;
    }
    QString loca=ui->le_loca_modif->text();
    bool test=s.modifier(id,nb_emp,nb_borne,nom_resp,loca);

    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("modifié \n"
                                             "click to cancel"), QMessageBox::Cancel);
        ui->le_id_modif->clear();
        ui->le_emp_modif->clear();
        ui->le_borne_modif->clear();
        ui->le_nom_modif->clear();
        ui->le_loca_modif->clear();
ui->tab_stat->setModel(s.afficher());

    }
else
    QMessageBox::critical(nullptr,QObject::tr("not ok"),
                          QObject::tr("modification non effectué"),QMessageBox::Cancel);
}


void MainWindow::on_le_id_tri_clicked()
{
    ui->tab_tri->setModel(s.trie_id());
}

void MainWindow::on_le_nom_tri_clicked()
{
    ui->tab_tri->setModel(s.trie_nom());
}

void MainWindow::on_le_emp_tri_clicked()
{
    ui->tab_tri->setModel(s.trie_nbemp());
}

void MainWindow::on_tab_stat_activated(const QModelIndex &index)
{
    QString val=ui->tab_stat->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM station WHERE id_station='"+val+"' OR nb_emp='"+val+"' OR nb_borne='"+val+"' OR nom_resp='"+val+"' OR loca='"+val+"' ");
    if (qry.exec())
    { while (qry.next())
        {
            //update
            //id
            ui->le_id_modif->setText(qry.value(0).toString());
            ui->le_emp_modif->setText(qry.value(1).toString());
            ui->le_borne_modif->setText(qry.value(2).toString());
            ui->le_loca_modif->setText(qry.value(3).toString());
            ui->le_nom_modif->setText(qry.value(4).toString());

            //delete
            //id
            ui->le_id_supp->setText(qry.value(0).toString()); //pour supprimer


        }
    }
}
