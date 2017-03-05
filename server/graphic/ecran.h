#ifndef ECRAN_H
#define ECRAN_H

#include <QPoint>
#include <QPushButton>
#include <QtNetwork>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMap>
#include <QMultiMap>
#include "monde/joueur.h"
#include "infoMonde/lesressources.h"
#include <QMessageBox>
#include "elementsMonde/decors.h"
#include "monde/monde.h"
#include "monde/combat.h"
#include <QTimer>
#include "network/database.h"
#include "network/compte.h"
#define PORT 32001


class Ecran : public QWidget
{
    Q_OBJECT

public:

    Ecran();
    ~Ecran();
    void enleveJeu(Joueur *joueur);
    void enleveChoixPerso(Joueur *joueur);
    //void analyseReponsePnj(QString const& reponse, Personnage *perso);
    //void commenceCombat(QString leader, QString autre);
    //void finiCombat(QString leader);
    //void analyseCombat(QString debut,QString fin,Joueur *joueur);
    //QList<Joueur*>joueursPasEnCombat(Point const& p);


public slots:

    void nouvelleConnexion();
    void donneesRecues();
    void deconnexionClient();
    //void envoie(QString nom, QString message);

private:

    Donnees_editeur *m_donnees_editeur;

    QPushButton *m_boutonQuitter;
    QLabel *m_infoServeur;
    QVBoxLayout *m_layout;
    QTcpServer *m_socketserveur;
    QListWidget *m_infojoueurs;
    QMap<QTcpSocket *, Joueur *>m_joueurs;
    QMap<QString,Joueur *>m_joueursCo;
    Monde *m_monde;
    DataBase *m_db;
};

#endif // ECRAN_H
