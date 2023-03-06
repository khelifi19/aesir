#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QDate>
#include<QSqlQueryModel>
class Client
{
public:
    Client();
    Client(int id,QString nom,QString prenom ,QString adresse,long num,QString charge ,QDate date);
    int getid();
    QString getnom();
     QString getprenom();
      QString getadresse();
      long getnum();
        QString getcharge();

        QDate getdate();

        void setid(int id);
        void setnom(QString nom);
        void setprenom(QString prenom );
        void setadresse(QString adresse );
        void setnum(long num);
        void setcharge(QString charge);

        void setdate(QDate date);
        bool ajouter();
        bool supprimer(int id);
         bool  modifier(int id ,QString nom,QString prenom, QString adresse,long num,QString charge,QDate date);

         QSqlQueryModel* afficher();
          bool existeId(int id);
          QSqlQueryModel * trie_id();
          QSqlQueryModel * trie_nom();
          QSqlQueryModel * trie_date();
private:

    int id;
    QString nom,prenom,adresse,charge;
long num;
    QDate date;
};

#endif // CLIENT_H
