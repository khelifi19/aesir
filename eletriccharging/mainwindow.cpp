#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "station.h"
#include <QMessageBox>
#include<QIntValidator>

#include <QGeoCoordinate>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>
#include<QSystemTrayIcon>
#include <QRegExp>
#include "connexion.h"
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
      QString localisation=ui->le_loca_2->currentText();
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
    QString loca=ui->le_loca_3->currentText();
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

            ui->le_nom_modif->setText(qry.value(3).toString());

            //delete
            //id
            ui->le_id_supp->setText(qry.value(0).toString()); //pour supprimer


        }
    }
}
//recherche
void MainWindow::on_le_recherhe_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM station WHERE id_station LIKE'"+arg1+"%' or nom_resp  LIKE'"+arg1+"%' or loca LIKE'"+arg1+"%'");
     query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->tab_tri->setModel(model);
     }
     else {
         QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                         QObject::tr("NO MATCH FOUND !!\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
      ui->le_recherhe->clear();}
}
//pdf
void MainWindow::on_le_pdf_clicked()
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
                               painter.drawText(3000,1400,"Liste des stations");
                               painter.setPen(Qt::black);
                               painter.setFont(QFont("Time New Roman", 15));
                               painter.drawRect(100,100,9400,2500); // dimension taa rectangle li fih liste
                               painter.drawRect(100,3000,9400,500);
                               painter.setFont(QFont("Time New Roman", 9));
                               painter.drawText(300,3300,"ID");
                               painter.drawText(2000,3300,"nb_emp");
                               painter.drawText(4000,3300,"nb_borne");
                               painter.drawText(5600,3300,"nom_responsable");
                               painter.drawText(7200,3300,"localisation");

                               painter.drawRect(100,3000,9400,10700);
                               //QTextDocument previewDoc;
                               QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
                               //QTextCursor cursor(&previewDoc);
                               QSqlQuery query;
                               query.prepare("select * from station");
                               query.exec();
                               while (query.next())
                               {
                                   painter.drawText(300,i,query.value(0).toString());
                                   painter.drawText(2000,i,query.value(1).toString());
                                   painter.drawText(4000,i,query.value(2).toString());
                                   painter.drawText(5600,i,query.value(3).toString());
                                   painter.drawText(7000,i,query.value(4).toString());
                                   painter.drawText(8000,i,query.value(5).toString());
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
// stat
void MainWindow::on_le_stat_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                                    model->setQuery("select * from station where loca = 'Tunis' ");
                                    float e=model->rowCount();
                                    model->setQuery("select * from station where loca = 'Sfax' ");
                                    float ee=model->rowCount();
                                    model->setQuery("select * from station where loca = 'Gafsa' ");
                                    float eee=model->rowCount();
                                    model->setQuery("select * from station where loca = 'Gabes' ");
                                    float eeee=model->rowCount();
                                    float total=e+ee+eee+eeee;
                                    QString a=QString("Tunis"+QString::number((e*100)/total,'f',2)+"%" );
                                    QString b=QString("Sfax"+QString::number((ee*100)/total,'f',2)+"%" );
                                     QString c=QString("Gafsa"+QString::number((eee*100)/total,'f',2)+"%" );
                                      QString d=QString("Gabes"+QString::number((eeee*100)/total,'f',2)+"%" );
                                    QPieSeries *series = new QPieSeries();
                                    series->append(a,e);
                                    series->append(b,ee);
                                    series->append(c,eee);
                                    series->append(d,eeee);
                            if (e!=0)
                            {QPieSlice *slice = series->slices().at(0);
                             slice->setLabelVisible();
                             slice->setPen(QPen());}
                            if ( ee!=0)
                            {
                                     // Add label, explode and define brush for 2nd slice
                                     QPieSlice *slice1 = series->slices().at(1);
                                     //slice1->setExploded();
                                     slice1->setLabelVisible();
                            }
                            if ( eee!=0)
                            {
                                     // Add label, explode and define brush for 2nd slice
                                     QPieSlice *slice2 = series->slices().at(2);
                                     //slice1->setExploded();
                                     slice2->setLabelVisible();
                            }
                            if ( eeee!=0)
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
                                    chart->setTitle("Pourcentage des localisations : nombre total : "+ QString::number(total));
                                    chart->legend()->hide();
                                    // Used to display the chart
                                    QChartView *chartView = new QChartView(chart);
                                    chartView->setRenderHint(QPainter::Antialiasing);
                                    chartView->resize(1000,500);
                                    chartView->show();
}

void MainWindow::on_le_map_clicked()
{

}
