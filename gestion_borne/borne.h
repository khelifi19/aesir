#ifndef BORNE_H
#define BORNE_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class Borne
{
public:
    Borne();
    Borne(int , QString , QString , int , int , int  , int );
    int getid();
    QString getstatut();
    QString gettype_prise();
    int getvoltage();
    int getmontant();
    int  getheure_debut();
    int getduree();
    void setid(int);
    void setstatut(QString);
    void settype_prise(QString);
    void setvoltage(int);
    void setmontant(int);
    void setheure_debut(int );
    void setduree(int);
    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* tri_voltage();
    QSqlQueryModel* tri_type();
    bool supprimer(int);
     bool modifier(int,QString,QString,int,int,int ,int);
     bool existeId(int id);
     bool ajouter_historique(QString action,int id_borne,QString statut_borne);
     QSqlQueryModel *afficher_historique0();
     QSqlQueryModel *afficher_historique(QString type);
     bool supprimerh(int ID_BORNE);
private:
    int id , voltage , montant  , duree,heure_debut;
    QString  statut, type_prise;



};


#endif // BORNE_H
