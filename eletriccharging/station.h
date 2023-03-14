#ifndef STATION_H
#define STATION_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QtQuick>
#include <QtPositioning>
#include <QGeoServiceProvider>
#include <QGeoCoordinate>
#include <QQuickView>
#include <QQuickItem>
#include <QList>
class station
{
    int id_station,nb_employe,nb_borne;
    QString nom_resp,localisation;

public:
    station(){}
    station(int id_station,int nb_employe,int nb_borne,QString nom_resp,QString localisation );
    QString getnom(){return nom_resp;}
    QString getloc(){return localisation;}
    int getid(){return id_station;}
    int getemp(){return nb_employe;}
    int getborne(){return nb_borne;}

    void setnom(QString n){nom_resp=n;}
    void setloc(QString l){localisation=l;}
    void setid(int id){id_station=id;}
    void setemp(int e){nb_employe=e;}
    void setborne(int b){nb_borne=b;}

    bool ajouter();
    bool supprimer(int id);
    bool modifier(int,int,int,QString,QString);
    bool existeId(int id);
    QSqlQueryModel* afficher();
    QSqlQueryModel * trie_id();
    QSqlQueryModel * trie_nom();
    QSqlQueryModel * trie_nbemp();





};

#endif // STATION_H
