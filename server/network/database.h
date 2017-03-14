#ifndef DATEBASE_H
#define DATEBASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include "QDebug"
#include "scenery/data.h"

class Compte;


/*
 *
 * Cette classe permet l'accès aux données des comptes stockés dans la base de donnée
 */


class DataBase : public QSqlDatabase
{
public:
    DataBase(Donnees_editeur *donneesEditeur);
    ~DataBase();
    Compte *tryConnection(QString pseudo, QString mdp, QString &message);//returns null pointer if the input data isn't correct
    //otherwise returns the account
    void savePlayer(QString const& pseudo, QString const& text);
private:
    Donnees_editeur *m_donnees_editeur;
};

#endif // DATEBASE_H
