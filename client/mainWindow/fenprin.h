#ifndef FENPRIN_H
#define FENPRIN_H


#include <QDataStream>
#include <QDesktopServices>
#include <QListWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QTcpSocket>
#include <QUrl>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QDockWidget>
#include <QTabWidget>
#include <QThread>
#include <QString>
#include <QStatusBar>
#include <QProgressBar>

#include "scenery/constants.h"
#include "network/compte.h"
#include "graphicGame/gamefield.h"
#include "additionalWindows/echange.h"
#include "network/reseau.h"
#include "additionalWindows/caracteristiques.h"
#include "inventory/resources.h"
#include "entities/npc.h"
#include "additionalWindows/dialoguepnj.h"
#include "additionalWindows/fairerecettes.h"
#include "fights/fight.h"
#include "additionalWindows/windowendfight.h"
#include "graphicGame/layoutbarreoutil.h"
#include "additionalWindows/interjoueur.h"

#include "mainWindow/laychoosechar.h"
#include "mainWindow/laycreatecharac.h"
#include "mainWindow/laygame.h"
#include "mainWindow/layhome.h"

class FenPrin : public QMainWindow
{
    enum Etat{Debut, Connexion,ChoixPersos,CreerPerso, Jeu, Cara};

    Q_OBJECT
public:
    explicit FenPrin(QWidget *parent = 0);
    ~FenPrin();
    void analyseTexte(QString & texte);
    void analyseReponsePnj(QString const& reponse);
    GameField *getJeu() const { return m_jeu; }

public slots:

    void inscription();
    void essaiconnexion();
    void ecriterreurReseau(QString erreur);

    void connexionAcc(QString donnees);
    void connexionRef();
    void qqAutre();
    void deplacement(QString qui, QPoint ou);

    void choixPerso();
    void jeu();
    void connexion(bool choixDuServ = false);
    void creer();
    void caracteristiques();
    void creerRecette(QString metier);

    void classeSuivante();
    void classePrecedente();
    void persoSuivant();
    void persoPrecedent();


    void creerUnPerso();
    void persoPlus();
    void supprimmePerso();

    void envoiAChat();
    void ajouteLigneChat(QString const& message);

    void echangeCommance();
    void onMeProposeEchange(QString qui);
    void annuleDemandeEchange();
    void accepteEchange();
    void refuseEchange();
    void annuleEchangeEnCour();

    void defiCommance(int equipe);
    void onMeProposeDefi(QString qui);
    void annuleDemandeDefi();
    void ilRefuseDefi();

    void dialoguePnj(qint16 num,QPoint pos);

    ///fights

    void je_passe_tour();
    void utiliseSpell(QString name);
    void meurt(QString const& name);
    void finFight(const QString &texte);

    void attackMonster(QString const& name);

private:

    Data *m_donneesediteur;
    Reseau *m_reseau;
    QThread *m_threadReseau;
    QTcpSocket *m_socket;
    quint16 m_tailleMessage;
    Compte *m_compte;
    Etat m_etat;
    int m_persoActuel;
    QString m_classeActuelle;


    LayChooseChar *m_layChooseChar;
    LayCreateCharac *m_layCreateCharac;
    LayGame *m_layGame;
    LayHome *m_layHome;



    LayoutBarreOutil *m_layoutBarreOutil;

    ////interjoueur

    //BoxEchange m_boxchange;
    QMessageBox *m_boxannul;
    QMessageBox *m_boxquestion;

    GameField *m_jeu;


protected:

    bool eventFilter(QObject *obj, QEvent *event);

};

#endif // FENPRIN_H
