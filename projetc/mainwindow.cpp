#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"employee.h"
#include <QMessageBox>
#include<QIntValidator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(0, 999999, this));
    ui->le_id_supp->setValidator(new QIntValidator(0, 999999, this));
    ui->le_id_modifier->setValidator(new QIntValidator(0, 999999, this));
    ui->le_cin->setValidator(new QIntValidator(0, 99999999, this));
    ui->tab_employe->setModel(E.afficher());


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

    Employee E1;
    if (E1.existeId(id)) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Cet ID existe déjà dans la base de données."));
        return;
    }
    QString nom=ui->le_nom->text();
    if (nom.isEmpty() || !nom.at(0).isUpper()) { // vérifie si nom est vide ou sa première lettre n'est pas en majuscule
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ nom doit être non vide et sa première lettre doit être en majuscule."));
        return;
    }
    int cin=ui->le_cin->text().toInt();
    QString sexe=ui->le_sexe->currentText();
    Employee E(id,nom,cin,sexe);
    bool test=E.ajouter();
    if (test)
    {
        ui->tab_employe->setModel(E.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Ajout effectué\n""Click Cancel to exit."),QMessageBox::Cancel);
    ui->le_id->clear();
    ui->le_nom->clear();
    ui->le_cin->clear();


    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"),QObject::tr("Ajout non effectué.\n""click cancel to exit."),QMessageBox::Cancel);
 }


void MainWindow::on_pb_supprimer_clicked()
{
    Employee E1; E1.Setid_employe(ui->le_id_supp->text().toInt());
    bool test= E1.supprimer(E1.Getid_employe());
    QMessageBox msgBox;
    if (test){
         ui->tab_employe->setModel(E.afficher());
        msgBox.setText("suppression avec succes. ");
        ui->le_id_supp->clear();
    }

            else
            msgBox.setText("L'id n'existe pas. ");
    msgBox.exec();

}

void MainWindow::on_tab_employe_activated(const QModelIndex &index)
{
    QString val=ui->tab_employe->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM EMPLOYEE WHERE id='"+val+"' OR nom='"+val+"' OR cin='"+val+"'");
    if (qry.exec())
    { while (qry.next())
        {
            //update
            //id
            ui->le_id_modifier->setText(qry.value(0).toString());
            ui->le_nom_modifier->setText(qry.value(1).toString());
            ui->le_cin_modifier->setText(qry.value(2).toString());

            //delete
            //id
            ui->le_id_supp->setText(qry.value(0).toString()); //pour supprimer


        }
    }
}

void MainWindow::on_pb_modifier_clicked()
{
    int id =ui->le_id_modifier->text().toUInt();
    QString nom =ui->le_nom_modifier->text();
    if (nom.isEmpty() || !nom.at(0).isUpper()) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le champ nom doit être non vide et sa première lettre doit être en majuscule."));
        return;
    }
    int cin =ui->le_cin_modifier->text().toUInt();
    QString sexe=ui->le_sexe_modifier->currentText();
    bool test=E.modifier(id ,nom,cin,sexe);
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("modifié \n"
                                             "click to cancel"), QMessageBox::Cancel);

        ui->tab_employe->setModel(E.afficher());
    }
else
    QMessageBox::critical(nullptr,QObject::tr("not ok"),
                          QObject::tr("modification non effectué"),QMessageBox::Cancel);
}

void MainWindow::on_tri_id_clicked()
{
    ui->tab_tri->setModel(E.trie_id());

}

void MainWindow::on_tri_nom_clicked()
{
    ui->tab_tri->setModel(E.trie_nom());
}

void MainWindow::on_tri_cin_clicked()
{
    ui->tab_tri->setModel(E.trie_cin());
}
