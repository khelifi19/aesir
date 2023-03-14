#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"employee.h"
#include <QMessageBox>
#include<QIntValidator>

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

//recherche

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM employee WHERE id  LIKE'"+arg1+"%' or nom  LIKE'"+arg1+"%' or sexe LIKE'"+arg1+"%'");
     query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->tab_tri->setModel(model);
     }
     else {
         QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                         QObject::tr("NO MATCH FOUND !!\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
      ui->lineEdit->clear();}
}

//pdf

void MainWindow::on_pushButton_clicked()
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
                               painter.drawText(3000,1400,"Liste des employees");
                               painter.setPen(Qt::black);
                               painter.setFont(QFont("Time New Roman", 15));
                               painter.drawRect(100,100,9400,2500); // dimension mtaa3 rectangle li fih liste
                               painter.drawRect(100,3000,9400,500);
                               painter.setFont(QFont("Time New Roman", 9));
                               painter.drawText(300,3300,"ID");
                               painter.drawText(2000,3300,"Nom");
                               painter.drawText(4000,3300,"Cin");
                               painter.drawText(5600,3300,"Sexe");

                               painter.drawRect(100,3000,9400,10700);
                               //QTextDocument previewDoc;
                               QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");
                               //QTextCursor cursor(&previewDoc);
                               QSqlQuery query;
                               query.prepare("select * from employee");
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

void MainWindow::on_pushButton_2_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                                    model->setQuery("select * from employee where SEXE = 'Homme' ");
                                    float e=model->rowCount();
                                    model->setQuery("select * from employee where SEXE = 'Femme' ");
                                    float ee=model->rowCount();
                                    float total=e+ee;
                                    QString a=QString("Homme"+QString::number((e*100)/total,'f',2)+"%" );
                                    QString b=QString("Femme"+QString::number((ee*100)/total,'f',2)+"%" );
                                    QPieSeries *series = new QPieSeries();
                                    series->append(a,e);
                                    series->append(b,ee);
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
                                    // Create the chart widget
                                    QChart *chart = new QChart();
                                    // Add data to chart with title and hide legend
                                    chart->addSeries(series);
                                    chart->setTitle("Pourcentage des homme et femme : nombre total : "+ QString::number(total));
                                    chart->legend()->hide();
                                    // Used to display the chart
                                    QChartView *chartView = new QChartView(chart);
                                    chartView->setRenderHint(QPainter::Antialiasing);
                                    chartView->resize(1000,500);
                                    chartView->show();
}


