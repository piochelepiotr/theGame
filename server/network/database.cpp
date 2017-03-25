#include "database.h"
#include "network/compte.h"

DataBase::DataBase(Data *donneesEditeur) : QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))//::addDatabase("QSQLITE")
{
    m_donnees_editeur = donneesEditeur;
    setHostName("localhost");
    setUserName("piotr");
    setPassword("lralvalueatlr");
    setDatabaseName("../data/db.sqlite3");
    if(open())
    {
        qDebug() << "ouverture de la base a réussi !";
    }
    else
    {
        qDebug() << "L'ouverture de la base a échoué";
        exit(1);
    }
}

DataBase::~DataBase()
{
    close();
}

Compte *DataBase::tryConnection(QString pseudo, QString mdp,QString &message)
{
    QSqlQuery query;
    if(query.exec("SELECT * FROM home_compte WHERE pseudo = '"+pseudo+"' AND mdp = '"+mdp+"'"))
    {
        if(query.next())
        {
            message = pseudo+"/"+query.value(4).toString();
            qDebug() << "connexion de "+pseudo;
            qDebug() << "avec comme données pour la creation du nouveau compte : " << message << "     et pseudo = " << pseudo;
            return new Compte(pseudo+"/"+query.value(4).toString(),pseudo,m_donnees_editeur);
        }
        else
        {
            return 0;
        }
    }
    else
    {
        qDebug() << "dans tryConnection on arrive pas à faire une requette";
        exit(1);
    }
}

void DataBase::savePlayer(QString const& pseudo, QString const& text)
{
    QSqlQuery query;
    if(!query.exec("UPDATE `home_compte` SET `persos` = \""+text+"\" WHERE `pseudo` = '"+pseudo+"'"))
    {
        qDebug() << "dans savePlayer on arrive pas à faire une requette";
        exit(1);
    }
}


