#include"connection.h"
Connection::Connection(){}
bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;

db.setDatabaseName("test");
db.setUserName("yassin");//inserer nom de l'utilisateur
db.setPassword("yassin");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}

void Connection::closeconnection(){
    db.close();
}
