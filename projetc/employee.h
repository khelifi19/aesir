#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
class Employee{
public:
    Employee();
    Employee(int,QString,int,QString);
    int Getid_employe();
          void Setid_employe(int val);
          QString Getnom();
          void Setnom(QString val);
          int Getcin();
          void Setcin(int val);
          void Set_sexe(QString val) ;
          QString get_sexe();

          bool ajouter();
          bool supprimer(int id);
           bool modifier(int,QString,int,QString);
           bool existeId(int id);
          QSqlQueryModel* afficher();
          QSqlQueryModel * trie_id();
          QSqlQueryModel * trie_nom();
          QSqlQueryModel * trie_cin();
private:
          int id_employe,cin;
          QString nom;
          QString sexe;


};

#endif // EMPLOYEE_H
