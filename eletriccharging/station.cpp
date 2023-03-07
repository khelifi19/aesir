#include "station.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include<QtDebug>
#include<QObject>
station::station(int id_station,int nb_employe,int nb_borne,QString nom_resp,QString localisation)
{
 this->id_station=id_station;
    this->nb_employe=nb_employe;
    this->nb_borne=nb_borne;
    this->nom_resp=nom_resp;
    this->localisation=localisation;
}
bool station::ajouter()
{
   QSqlQuery query;
   QString res = QString::number(id_station);
   query.prepare("insert into station(id_station,nb_emp,nb_borne,nom_resp,loca)""values(:id_station,:nb_emp,:nb_borne,:nom_resp,:loca)");
   query.bindValue(":id_station",res);
   query.bindValue(":nb_emp",nb_employe);
   query.bindValue(":nb_borne",nb_borne);
   query.bindValue(":nom_resp",nom_resp);
   query.bindValue(":loca",localisation);



     return  query.exec();
}
QSqlQueryModel* station::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT * FROM station");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_station"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("nb_emp"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("nb_borne"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("nom_resp"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("loca"));


    return model;

}
bool station::supprimer(int id)
{
  QSqlQuery query;
  query.prepare("Delete from station Where id_station=: id_station");
  query.bindValue(0,id);
  if (!query.exec()) { // si la requête a échoué
                 return false;
             }
             if (query.numRowsAffected() == 0) { // si aucun enregistrement n'a été supprimé
                 return false;
             }
             return true;
}
bool station :: modifier(int id_station,int nb_emp, int nb_borne , QString nom_resp ,QString loca)
{
    QSqlQuery qry;
    qry.prepare("UPDATE station set nb_emp=(?),nb_borne=(?),nom_resp=(?),loca=(?) where id_station=(?) ");

    qry.addBindValue(nb_emp);
    qry.addBindValue(nb_borne);
    qry.addBindValue(nom_resp);
    qry.addBindValue(loca);
    qry.addBindValue(id_station);

    return  qry.exec();
}
QSqlQueryModel * station::trie_nom()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM station order by nom_resp");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("id_station"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("nb_emp"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("nb_borne"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("nom_resp"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("loca"));
    return model;
}QSqlQueryModel * station::trie_id()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM station order by id_station");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("id_station"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("nb_emp"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("nb_borne"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("nom_resp"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("loca"));
    return model;
}
QSqlQueryModel * station::trie_nbemp()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM station order by nb_emp");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("id_station"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("nb_emp"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("nb_borne"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("nom_resp"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("loca"));
    return model;
}
bool station::existeId(int id)
{
    QSqlQuery query;
    query.prepare("SELECT id_station FROM station WHERE id_station = :id_station");
    query.bindValue(":id_station", id);
    if (query.exec() && query.next()) {
        return true; // L'ID existe dans bd
    }
    return false; // L'ID n'existe pas dans bd
}

