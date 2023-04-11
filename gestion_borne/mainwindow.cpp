#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "borne.h"
#include<QMessageBox>
#include <QIntValidator>
#include <QDebug>

#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>
#include<QSystemTrayIcon>
#include <QRegExp>
#include "connection.h"
#include <QFileDialog>
#include <QPainter>
#include <QDate>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>
#include <QApplication>
#include <QIntValidator>
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QtDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
#include <QApplication>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QtCore>
#include <QSystemTrayIcon>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

   ui->le_id->setValidator(new QIntValidator(0, 999, this));//range of 0 to 999


   ui->tab_borne->setModel(B.afficher());
   ui->le_historique->setModel(B.afficher_historique0());
   trayIcon = new QSystemTrayIcon(this);
     trayIcon->setIcon(QIcon("C:/Users/mkaou/OneDrive/Bureau/icon/bell-2-64.png"));

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
       if (ui->le_statut->currentText() == "disponible")
           {
               // Show a notification in the system tray
           trayIcon->show();
               trayIcon->showMessage("plugGo",
                                     QString("Charging station available").arg(id),
                                     QSystemTrayIcon::Information,
                                     5000); // 5 seconds
           }

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
                /*QTime heure_debut = QTime::fromString(ui->timeEdit->text(), "HH:mm ap");
                if (heure_debut.isNull()) {
                    qDebug() << "Error: Invalid time format!";
                } else {
                    qDebug() << "heure_debut:" << heure_debut;
                }*/
                 int heure_debut=ui->le_heure_debut->text().toInt();
                int duree=ui->le_duree->text().toInt();

    Borne B(id,statut,type_prise,voltage,montant,heure_debut,duree);
    bool test=B.ajouter();
    if (test)
    {
        ui->tab_borne->setModel(B.afficher());
     QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("ajout effectuer \n""click cancel to exit"),QMessageBox::Cancel);
     ui->le_id->clear();
        ui->le_voltage->clear();
        ui->le_montant->clear();
        ui->le_heure_debut->clear();
        ui->le_duree->clear();
        B.ajouter_historique("ajout",id,statut);

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
     B.ajouter_historique("supression",ui->le_idSUP->text().toInt(),ui->le_statut->currentText());

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),QObject::tr("L'id n'existe pas.\n""click cancel to exit"),QMessageBox::Cancel);
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
                        ui->le_voltage_modif->setText(qry.value(3).toString());
                        ui->le_montant_modif->setText(qry.value(4).toString());
                       /* QTime time = QTime::fromString(qry.value(5).toString(), "hh:mm ap");
                        ui->timeEdit_2->setTime(time);*/
                         ui->le_heure_debut_modif->setText(qry.value(5).toString());

                        ui->le_duree_modif->setText(qry.value(6).toString());

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
       if (ui->le_statut_modif->currentText() == "disponible")
           {
               // Show a notification in the system tray
           trayIcon->show();
               trayIcon->showMessage("Charging station available",
                                     QString("Charging station is now available for use").arg(id),
                                     QSystemTrayIcon::Information,
                                     5000); // 5 seconds
           }

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
       //QTime heure_debut = QTime::fromString(ui->timeEdit_2->text(), "hh:mm ap");
       int heure_debut=ui->le_heure_debut_modif->text().toUInt();
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
                  B.ajouter_historique("modification",id,statut);



        }
    else
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("modification non effectué"),QMessageBox::Cancel);


}







void MainWindow::on_tri_voltage_clicked()
{
    ui->tab_tri->setModel(B.tri_voltage());
}

void MainWindow::on_trie_type_clicked()
{
    ui->tab_tri->setModel(B.tri_type());
}

void MainWindow::on_le_recherche_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM BORNE WHERE id  LIKE'"+arg1+"%' or statut  LIKE'"+arg1+"%' ");
     query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->tab_tri->setModel(model);
     }
     else {
         QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                         QObject::tr("NO MATCH FOUND !!\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
      ui->le_recherche->clear();}
}

void MainWindow::on_pdf_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    qDebug()<<dir;
    QPdfWriter pdf(dir+"/PdfList.pdf");
                           QPainter painter(&pdf);
                          int i = 4000;

                                painter.drawPixmap(QRect(100,100,2500,2500),QPixmap("C:/logo.jpg"));
                               // painter.drawText(900,650,"Smart Charging Station");
                               painter.setPen(Qt::blue);
                               painter.setFont(QFont("Time New Roman", 25));
                               painter.drawText(3000,1400,"Liste des bornes");
                               painter.setPen(Qt::black);
                               painter.setFont(QFont("Time New Roman", 15));
                               painter.drawRect(100,100,9400,2500); // dimension taa rectangle li fih liste
                               painter.drawRect(100,3000,9400,500);
                               painter.setFont(QFont("Time New Roman", 9));
                               painter.drawText(300,3300,"ID");
                               painter.drawText(2000,3300,"statut");
                               painter.drawText(4000,3300,"type");
                               painter.drawText(5600,3300,"voltage");
                               painter.drawText(7000,3300,"montant");
                               painter.drawText(8000,3300,"heure debut");
                               painter.drawText(9000,3300,"duree");





                               painter.drawRect(100,3000,9400,10700);
                               //QTextDocument previewDoc;
                               QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
                               //QTextCursor cursor(&previewDoc);
                               QSqlQuery query;
                               query.prepare("select * from Borne");
                               query.exec();
                               while (query.next())
                               {
                                   painter.drawText(300,i,query.value(0).toString());
                                   painter.drawText(2000,i,query.value(1).toString());
                                   painter.drawText(4000,i,query.value(2).toString());
                                   painter.drawText(5600,i,query.value(3).toString());
                                   painter.drawText(7000,i,query.value(4).toString());
                                   painter.drawText(8000,i,query.value(5).toString());
                                   painter.drawText(9000,i,query.value(6).toString());
                                  i = i +500;
                               }
                               int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                   QMessageBox::Yes|QMessageBox::No);
                                   if (reponse == QMessageBox::Yes)
                                   {
                                       QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                       painter.end();
                                   }
                                   else
                                   {
                                        painter.end();
                                   }
}

void MainWindow::on_statistique_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                                    model->setQuery("select * from BORNE where statut = 'disponible' ");
                                    float d=model->rowCount();
                                    model->setQuery("select * from Borne where statut = 'occupee' ");
                                    float o=model->rowCount();
                                    model->setQuery("select * from Borne where statut = 'maintenance' ");
                                    float m=model->rowCount();
                                    model->setQuery("select * from Borne where statut = 'En panne' ");
                                    float p=model->rowCount();
                                    float total=d+o+m+p;
                                    QString a=QString("disponible"+QString::number((d*100)/total,'f',2)+"%" );
                                    QString b=QString("occupee"+QString::number((o*100)/total,'f',2)+"%" );
                                    QString c=QString("maintenance"+QString::number((m*100)/total,'f',2)+"%" );
                                    QString f=QString("panne"+QString::number((p*100)/total,'f',2)+"%" );
                                    QPieSeries *series = new QPieSeries();
                                    series->append(a,d);
                                    series->append(b,o);
                                    series->append(c,m);
                                    series->append(f,p);
                            if (d!=0)
                            {QPieSlice *slice = series->slices().at(0);
                             slice->setLabelVisible();
                             slice->setPen(QPen());}
                            if ( o!=0)
                            {
                                     // Add label, explode and define brush for 2nd slice
                                     QPieSlice *slice1 = series->slices().at(1);
                                     //slice1->setExploded();
                                     slice1->setLabelVisible();
                            }
                            if ( m!=0)
                            {
                                     // Add label, explode and define brush for 2nd slice
                                     QPieSlice *slice2 = series->slices().at(2);
                                     //slice1->setExploded();
                                     slice2->setLabelVisible();
                            }
                            if ( p!=0)
                            {
                                     // Add label, explode and define brush for 2nd slice
                                     QPieSlice *slice3 = series->slices().at(3);
                                     //slice1->setExploded();
                                     slice3->setLabelVisible();
                            }
                                    // Create the chart widget
                                    QChart *chart = new QChart();
                                    // Add data to chart with title and hide legend
                                    chart->addSeries(series);
                                    chart->setTitle("Pourcentage des status : nombre total : "+ QString::number(total));
                                    chart->legend()->hide();
                                    // Used to display the chart
                                    QChartView *chartView = new QChartView(chart);
                                    chartView->setRenderHint(QPainter::Antialiasing);
                                    chartView->resize(1000,500);
                                    chartView->show();
}



void MainWindow::on_pushButton_clicked()
{
    Borne b;
    QString type=ui->type_historique->currentText();
    ui->le_historique->setModel(b.afficher_historique(type));
}

void MainWindow::on_le_supp_clicked()
{

    QSqlQuery query;

             query.prepare("DELETE from HISTORIQUE");

        query.exec();
}
