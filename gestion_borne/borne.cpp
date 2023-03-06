#include "borne.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
Borne::Borne()
{
id=0;
statut="";
type_prise="";
voltage=0;
montant=0;
heure_debut=0;
duree=0;
}
Borne::Borne(int id , QString statut , QString type_prise , int voltage , int montant , int heure_debut , int duree)
{
    this->id=id;
    this->statut=statut;
    this->type_prise=type_prise;
    this->voltage=voltage;
    this->montant=montant;
    this->heure_debut=heure_debut;
    this->duree=duree;
}
//get
int Borne::getid()
{return id;}
QString Borne::getstatut()
{return statut;}
QString Borne::gettype_prise()
{return type_prise;}
int Borne::getvoltage()
{return voltage;}
int Borne::getmontant()
{return montant;}
int Borne::getheure_debut()
{return heure_debut;}
int Borne::getduree()
{return duree;}

//set
void Borne::setid(int id)
{this->id=id;}
void Borne::setstatut(QString statut)
{this->statut=statut;}
void Borne::settype_prise(QString type_prise)
{this->type_prise=type_prise;}
void Borne::setvoltage(int voltage)
{this->voltage=voltage;}
void Borne::setmontant(int montant)
{this->montant=montant;}
void Borne::setheure_debut(int heure_debut)
{this->heure_debut=heure_debut;}
void Borne::setduree(int duree)
{this->duree=duree;}

bool Borne::ajouter()
{

     QString id_string = QString::number(id);
     QString voltage_string = QString::number(voltage);
     QString montant_string = QString::number(montant);
     QString heure_debut_string = QString::number(heure_debut);
     QString duree_string = QString::number(duree);
    QSqlQuery query;

          query.prepare("INSERT INTO borne (id, statut , type_prise , voltage , montant , heure_debut , duree)" "VALUES (:id, :statut , :type_prise , :voltage , :montant , :heure_debut , :duree)");
          query.bindValue(":id", id_string);
          query.bindValue(":statut", statut);
          query.bindValue(":type_prise", type_prise);
          query.bindValue(":voltage", voltage_string);
          query.bindValue(":montant", montant_string);
          query.bindValue(":heure_debut", heure_debut_string);
          query.bindValue(":duree", duree_string);

    return query.exec();

}
bool Borne::existeId(int id)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM BORNE WHERE id = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        return true; // L'ID existe dans bd
    }
    return false; // L'ID n'existe pas dans bd
}
QSqlQueryModel* Borne::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM borne");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("statut"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("type prise"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("voltage"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("montant"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("heure bebut"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("duree"));





    return model;
}
bool Borne::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("Delete from BORNE Where id=: id");
    query.bindValue(0,id);
    if (!query.exec()) { // si la requête a échoué
                   return false;
               }
               if (query.numRowsAffected() == 0) { // si aucun enregistrement n'a été supprimé
                   return false;
               }
               return true;
}


bool Borne :: modifier(int id ,QString statut,QString type_prise , int voltage,int montant,int heure_debut,int duree)
{
    QSqlQuery qry;
    qry.prepare("UPDATE BORNE set duree=(?),heure_debut=(?),montant=(?) ,voltage=(?),type_prise=(?),statut=(?) where id=(?) ");
      qry.addBindValue(duree);
       qry.addBindValue(heure_debut);
        qry.addBindValue(montant);
    qry.addBindValue(voltage);
    qry.addBindValue(type_prise);
    qry.addBindValue(statut);
    qry.addBindValue(id);

    return  qry.exec();
}



