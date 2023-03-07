#include "connexion.h"
connection::connection()
{
}
bool connection::createconnection()
{
 db=QSqlDatabase::addDatabase("QODBC");
 bool test=false;
 db.setDatabaseName("test");
 db.setUserName("saif");
 db.setPassword("saif");
 if(db.open()) test=true;
 return test;
}
void connection::closeConnection(){db.close();}
