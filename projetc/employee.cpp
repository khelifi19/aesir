#include"employee.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
Employee::Employee()
{
    id_employe=0; nom=""; cin=0000000;
    sexe=" ";
}
Employee::Employee(int id_employe,QString nom,int cin,QString sexe)
{
    this->id_employe=id_employe;
    this->nom=nom;
    this->cin=cin;
    this->sexe=sexe;
}


int Employee::Getid_employe() { return id_employe; }
      void Employee::Setid_employe(int id_employe) { this->id_employe = id_employe; }
      QString Employee::Getnom() { return nom; }
      void Employee::Setnom(QString nom) { this->nom = nom; }
      int Employee::Getcin() { return cin; }
      void Employee::Setcin(int cin) { this->cin = cin; }

      QString Employee::get_sexe() { return sexe; }
      void Employee::Set_sexe(QString sexe) { this->sexe = sexe; }

      bool Employee::ajouter()
      {
          QSqlQuery query;
          QString res = QString::number(id_employe);
          query.prepare("insert into EMPLOYEE(id,nom,cin,sexe)""values(:id,:nom,:cin,:sexe)");
          query.bindValue(":id",res);
          query.bindValue(":nom",nom);
          query.bindValue(":cin",cin);
          query.bindValue(":sexe",sexe);
          return  query.exec();
      }
      bool Employee::supprimer(int id)
      {
        QSqlQuery query;
        //QString res = QString::number(id);
        query.prepare("Delete from EMPLOYEE Where id=: id");
        query.bindValue(0,id);
        if (!query.exec()) { // si la requête a échoué
               return false;
           }
           if (query.numRowsAffected() == 0) { // si aucun enregistrement n'a été supprimé
               return false;
           }
           return true;
      }

QSqlQueryModel* Employee::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

          model->setQuery("SELECT * FROM employee");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Cin"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Sexe"));

    return model;

}
bool Employee :: modifier(int id ,QString nom,int cin,QString sexe)
{
    QSqlQuery qry;
    qry.prepare("UPDATE EMPLOYEE set nom=(?),cin=(?),sexe=(?) where id=(?) ");
    qry.addBindValue(nom);
    qry.addBindValue(cin);
    qry.addBindValue(sexe);
    qry.addBindValue(id);

    return  qry.exec();
}

QSqlQueryModel * Employee::trie_id()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYEE order by id");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("SEXE"));

    return model;
}

QSqlQueryModel * Employee::trie_nom()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYEE order by nom");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("SEXE"));
    return model;
}

QSqlQueryModel * Employee::trie_cin()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYEE order by cin");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("SEXE"));
    return model;
}
bool Employee::existeId(int id)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM EMPLOYEE WHERE id = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next()) {
        return true; // L'ID existe dans bd
    }
    return false; // L'ID n'existe pas dans bd
}
