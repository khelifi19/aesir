#include "client.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
Client::Client()
{
    id=0; nom=" "; prenom=" "; adresse=" "; num=00000000; charge=" ";

}
Client::Client(int id,QString nom,QString prenom ,QString adresse,long num,QString charge,QDate date)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->adresse=adresse;
    this->num=num;
    this->charge=charge;

    this->date=date;
}
int Client::getid()
{
    return id;

}
QString Client::getnom()
{return nom;}
 QString Client:: getprenom()
 { return prenom;}
  QString Client:: getadresse()
  {return adresse;}
   long Client:: getnum()
   {return num;}
    QString Client:: getcharge()
    {return charge;}

    QDate Client:: getdate()
    {return date;}

    void Client::setid(int id)
    {this->id =id;}
    void Client:: setnom(QString nom)
    {this->nom=nom;}
    void Client::setprenom(QString prenom)
    {this->prenom=prenom;}
    void Client:: setadresse(QString adresse)
    {this->adresse=adresse;}
    void Client:: setnum(long num)
    {this->num=num;}
    void Client::setcharge(QString charge)
    {this->charge=charge;}

    void Client:: setdate(QDate date)
    {this->date=date;}

    bool Client::ajouter()
    {

 QString id_string = QString::number(id);
QString num_string = QString::number(num);

        QSqlQuery query;
             query.prepare("INSERT INTO CLIENT(id, nom, prenom,adresse,num,charge,dateCharge) "
                           "VALUES (:id, :nom, :prenom, :adresse, :num, :charge, :dateCharge)");
             query.bindValue(":id", id_string);
             query.bindValue(":nom", nom);
             query.bindValue(":prenom", prenom);
              query.bindValue(":adresse", adresse);
               query.bindValue(":num", num_string);
                query.bindValue(":charge", charge);
                 query.bindValue(":dateCharge", date);




        return  query.exec();
    }

    bool Client::supprimer(int id)
    {
      QSqlQuery query;
      //QString res = QString::number(id);
      query.prepare("Delete from CLIENT Where id=: id");
      query.bindValue(0,id);
      if (!query.exec()) { // si la requête a échoué
             return false;
         }
         if (query.numRowsAffected() == 0) { // si aucun enregistrement n'a été supprimé
             return false;
         }
         return true;
    }

    QSqlQueryModel* Client::afficher()
    {
        QSqlQueryModel* model=new QSqlQueryModel();

              model->setQuery("SELECT * FROM CLIENT");
              model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
              model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
              model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
              model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
               model->setHeaderData(4, Qt::Horizontal, QObject::tr("num"));
                model->setHeaderData(5, Qt::Horizontal, QObject::tr("charge"));
                 model->setHeaderData(6, Qt::Horizontal, QObject::tr("dateCharge"));

        return model;

    }

    bool Client ::  modifier(int id ,QString nom,QString prenom, QString adresse,long num,QString charge,QDate date)
    {
        QVariant var=QVariant(QString::number(num));;

        QSqlQuery qry;
        qry.prepare("UPDATE CLIENT set nom=(?),prenom=(?),adresse=(?),num=(?),charge=(?),dateCharge=(?) where id=(?) ");

        qry.addBindValue(nom);
        qry.addBindValue(prenom);
        qry.addBindValue(adresse);
         qry.addBindValue(var);
          qry.addBindValue(charge);
           qry.addBindValue(date);
          qry.addBindValue(id);

        return  qry.exec();
    }
    bool Client::existeId(int id)
    {
        QSqlQuery query;
        query.prepare("SELECT id FROM CLIENT WHERE id = :id");
        query.bindValue(":id", id);
        if (query.exec() && query.next()) {
            return true; // L'ID existe dans bd
        }
        return false; // L'ID n'existe pas dans bd
    }
    QSqlQueryModel * Client::trie_id()
    {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM CLIENT order by id");
        model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal,QObject::tr("ADRESSE"));
         model->setHeaderData(4, Qt::Horizontal,QObject::tr("NUM"));
          model->setHeaderData(5, Qt::Horizontal,QObject::tr("CHARGE"));
           model->setHeaderData(6, Qt::Horizontal,QObject::tr("DATE"));


        return model;
    }

    QSqlQueryModel * Client::trie_nom()
    {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM CLIENT order by nom");
        model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal,QObject::tr("ADRESSE"));
         model->setHeaderData(4, Qt::Horizontal,QObject::tr("NUM"));
          model->setHeaderData(5, Qt::Horizontal,QObject::tr("CHARGE"));
           model->setHeaderData(6, Qt::Horizontal,QObject::tr("DATE"));


        return model;
    }

    QSqlQueryModel * Client::trie_date()
    {
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM CLIENT order by dateCharge");
        model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal,QObject::tr("ADRESSE"));
         model->setHeaderData(4, Qt::Horizontal,QObject::tr("NUM"));
          model->setHeaderData(5, Qt::Horizontal,QObject::tr("CHARGE"));
           model->setHeaderData(6, Qt::Horizontal,QObject::tr("DATE"));


        return model;
    }

