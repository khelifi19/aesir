#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "borne.h"
#include<QMessageBox>
#include <QIntValidator>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

   ui->le_id->setValidator(new QIntValidator(0, 999, this));


   ui->tab_borne->setModel(B.afficher());
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
    Borne E1;
            if (E1.existeId(id)) {
                QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Cet ID existe déjà dans la base de données."));
                return;
            }


                //Add items to the QComboBox using the addItem method

       QString statut=ui->le_statut->currentText();


      QString type_prise;
  if (ui->mennekes->isChecked())
  { type_prise="mannekes";}
  else if (ui->type2->isChecked())
  { type_prise="type2";}
  else if (ui->ccs->isChecked())
  {type_prise="ccs";}
  else {type_prise="tesla";}

  qDebug() << "DATE DESTINATION " << statut;
     qDebug() <<"Destination"<<type_prise;



               int voltage=ui->le_voltage->text().toInt();
                int montant=ui->le_montant->text().toInt();
                int heure_debut=ui->le_heure_debut->text().toInt();
                int duree=ui->le_duree->text().toInt();

    Borne B(id,statut,type_prise,voltage,montant,heure_debut,duree);
    bool test=B.ajouter();
    if (test)
    {//ui->tab_borne->setModel(B.afficher());
     QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("ajout effectuer \n""click cancel to exit"),QMessageBox::Cancel);
     ui->le_id->clear();
        ui->le_voltage->clear();
        ui->le_montant->clear();
        ui->le_heure_debut->clear();
        ui->le_duree->clear();

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),QObject::tr("ajout non effectue\n""click cancel to exit"),QMessageBox::Cancel);

}
void MainWindow::on_pb_supprimer_clicked()
{
    Borne B;
    B.setid(ui->le_idSUP->text().toInt());
    bool test=B.supprimer(B.getid());
    if (test)
    {
        ui->tab_borne->setModel(B.afficher());
     QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("suppression effectuer \n""click cancel to exit"),QMessageBox::Cancel);
     ui->le_idSUP->clear();

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),QObject::tr("L'id existe deja.\n""click cancel to exit"),QMessageBox::Cancel);
}






void MainWindow::on_tab_borne_activated(const QModelIndex &index)
{

                QString val=ui->tab_borne->model()->data(index).toString();
                QSqlQuery qry;
                qry.prepare("SELECT * FROM BORNE WHERE id='"+val+"' OR statut='"+val+"' OR type_prise='"+val+"' OR voltage='"+val+"' OR montant='"+val+"' OR heure_debut='"+val+"' OR duree='"+val+"'");
                if (qry.exec())
                { while (qry.next())
                    {
                        //update
                        //id
                        ui->le_id_modif_2->setText(qry.value(0).toString());
                        ui->le_voltage_modif->setText(qry.value(1).toString());
                        ui->le_montant_modif->setText(qry.value(2).toString());
                        ui->le_heure_debut_modif->setText(qry.value(2).toString());
                        ui->le_duree_modif->setText(qry.value(2).toString());

                        //delete
                        //id
                        ui->le_idSUP->setText(qry.value(0).toString()); //pour supprimer


                    }
                }
}





void MainWindow::on_pb_modifier_2_clicked()
{
    int id =ui->le_id_modif_2->text().toUInt();
    if (ui->le_id_modif_2
            ->text().isEmpty()) { // Vérifie si id est vide
            QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ ID ne doit pas être vide."));
            return;
        }




       QString statut=ui->le_statut_modif->currentText();

     QString type_prise;
       if (ui->mennekes_modif->isChecked())
       { type_prise="mannekes";}
       else if (ui->type2_modif->isChecked())
       { type_prise="type2";}
       else if (ui->ccs_modi->isChecked())
       {type_prise="ccs";}
       else {type_prise="tesla";}
       int voltage =ui->le_voltage_modif->text().toUInt();
       int montant=ui->le_montant_modif->text().toUInt();
       int heure_debut =ui->le_heure_debut_modif->text().toUInt();
       int duree =ui->le_duree_modif->text().toUInt();

        bool test=B.modifier(id,statut,type_prise,voltage,montant,heure_debut,duree);
        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("ok"),
                                     QObject::tr("modifié \n"
                                                 "click to cancel"), QMessageBox::Cancel);

            ui->tab_borne->setModel(B.afficher());
            ui->le_id_modif_2->clear();
               ui->le_voltage_modif->clear();
               ui->le_montant_modif->clear();
               ui->le_heure_debut_modif->clear();
                  ui->le_duree_modif->clear();


        }
    else
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("modification non effectué"),QMessageBox::Cancel);


}


