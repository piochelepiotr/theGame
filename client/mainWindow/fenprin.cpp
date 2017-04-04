#include "mainWindow/fenprin.h"
#include "graphicGame/affichejoueur.h"
#include <QDateTime>
#include "graphicGame/windowactions.h"

#define NBR_IMAGES_SECONDE 15


FenPrin::FenPrin(QWidget *parent) : QMainWindow(parent)
{
    m_fight = 0;
    m_donneesediteur = new Data(0,0,0,0);
    m_reseau = new Reseau();
    m_threadReseau = new QThread;
    m_reseau->moveToThread(m_threadReseau);
    m_threadReseau->start();
    m_etat = Debut;
    connexion();
    m_compte = 0;

    m_boxannul = new QMessageBox(this);
    m_boxannul->setWindowTitle(trUtf8("En attente de la réponse..."));
    m_boxannul->setStandardButtons(QMessageBox::Cancel);
    m_boxquestion = new QMessageBox(this);
    m_boxquestion->setWindowTitle(trUtf8("Que-est-ce tu veux ?!??"));
    m_boxquestion->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);


    qRegisterMetaType <EntityInfo>("InfoPerVis");
    connect(m_reseau, SIGNAL(erreurReseau(QString)), this, SLOT(ecriterreurReseau(QString)));
    connect(m_reseau, SIGNAL(ecritdanschat(QString)), this, SLOT(ajouteLigneChat(QString)));
    connect(m_reseau, SIGNAL(connexionAcceptee(QString)), this, SLOT(connexionAcc(QString)));
    connect(m_reseau, SIGNAL(connexionRefusee()), this, SLOT(connexionRef()));
    connect(m_reseau, SIGNAL(qqdautre()), this, SLOT(qqAutre()));
    connect(m_reseau, SIGNAL(deplacement(QString, QPoint)), this, SLOT(deplacement(QString, QPoint)));

    connect(m_reseau, SIGNAL(onMeProposeDefi(QString)), this, SLOT(onMeProposeDefi(QString)));
    //connect(m_reseau, SIGNAL(accepteEchange()), m_boxannul, SLOT(reject()));
    connect(m_reseau, SIGNAL(ilAnnuleDemandeDefi()), m_boxquestion, SLOT(reject()));
    connect(m_reseau, SIGNAL(ilRefuseMonDefi()), this, SLOT(ilRefuseDefi()));
    connect(m_reseau, SIGNAL(commenceDefi(int)), this, SLOT(defiCommance(int)));

    m_reseau->start();

    this->installEventFilter(this);
    //showMaximized();
}

FenPrin::~FenPrin()
{
    delete m_donneesediteur;
    m_threadReseau->exit();
    m_threadReseau->wait();
    delete m_threadReseau;
    delete m_reseau;
    if(m_etat != Connexion && m_etat != Debut)
        delete m_compte;
    if(m_etat == Connexion)
        delete m_coui;
    else if(m_etat == ChoixPersos)
        delete m_choixui;
    else if(m_etat == Jeu)
    {
        delete m_jeuui;
    }
    else if(m_etat == CreerPerso)
        delete m_creerui;
}

void FenPrin::inscription()
{
    QDesktopServices::openUrl(QUrl("http://www.google.fr"));
}

void FenPrin::essaiconnexion()
{
    QString accountName = m_coui->bar_ndc->text();
    QString password = m_coui->bar_mdp->text();
    /*For the tests*/
    if(accountName.isEmpty())
    {
        accountName = "piochelepiotr";
        password = "jaioublier";
    }
    if(accountName.size() < 4 ||password.size()  < 4)
    {
        QMessageBox::critical(this, trUtf8("erreur lors de la connexion"), trUtf8("ERREUR : le pseudo et le mot de passe doivent contenir au minimum 4 caractères."));
    }
    else
    {
       m_reseau->envoyer("ess/"+accountName+'*'+password);
    }
}

void FenPrin::ecriterreurReseau(QString erreur)
{
    QMessageBox::critical(this, trUtf8("erreur de réseau"), erreur);
}

void FenPrin::ajouteLigneChat(QString const& message)
{
    m_layoutBarreOutil->getChat()->addItem(new QListWidgetItem(message));
}

void FenPrin::envoiAChat()// fonction à mettre dans la classe layoutbarre outil
{
    QString texte = m_layoutBarreOutil->getLineEditChat()->text();
    texte = texte.simplified();
    if(!texte.isEmpty())
    {
        analyseTexte(texte);
        m_reseau->envoyer("cha/"+texte);
        m_layoutBarreOutil->getLineEditChat()->clear();
    }

}

void FenPrin::analyseTexte(QString & texte)//fonction à mettre dans la classe barre outil
{
    texte.replace("%pos%", "["+QString::number(m_compte->getPerso(m_persoActuel)->getPosX())+";"+QString::number(m_compte->getPerso(m_persoActuel)->getPosY())+"]");
    texte.replace("%carac%", m_compte->getPerso(m_persoActuel)->caracteristiques());
    texte = m_compte->getPerso(m_persoActuel)->getNom() + " : "+texte;
}

void FenPrin::jeu()
{
    QSize size = this->size();
    delete m_choixui;
    m_choixui = 0;
    m_reseau->envoyer("jeu/"+QString::number(m_persoActuel));
    m_jeuui = new Ui::JeuMainWindow();
    m_jeuui->setupUi(this);

    this->setWindowTitle(m_compte->getPerso(m_persoActuel)->getNom());
    m_jeu = new GameField(QSize(size.width(),size.height()-HAUTEUR_BARRE_OUTIL), m_compte->getPerso(m_persoActuel), m_reseau->socket(), m_donneesediteur);
    m_jeuui->jeu2d->setScene(m_jeu);
    m_jeuui->jeu2d->setSceneRect(0,0,size.width(),size.height()-HAUTEUR_BARRE_OUTIL);

    m_layoutBarreOutil = new LayoutBarreOutil(this,m_compte->getPerso(m_persoActuel));
    m_jeuui->barreoutil->setLayout(m_layoutBarreOutil);
    m_jeuui->barreoutil->setFixedHeight(HAUTEUR_BARRE_OUTIL);

    connect(m_jeuui->menu_jeu_quitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(m_jeuui->menu_jeu_deco, SIGNAL(triggered()), this, SLOT(connexion()));
    connect(m_jeuui->menu_jeu_changerPerso, SIGNAL(triggered()), this, SLOT(choixPerso()));
    connect(m_reseau, SIGNAL(nouveauJoueur(EntityInfo)), m_jeu, SLOT(addEntity(EntityInfo)));
    connect(m_reseau, SIGNAL(decJoueur(QString)), m_jeu, SLOT(removeEntity(QString)));
    connect(m_reseau, SIGNAL(coupe(QString,QString,int,int)), m_jeu, SLOT(recolte(QString,QString,int,int)));
    connect(m_reseau, SIGNAL(resource_coupe(QPoint)), m_jeu, SLOT(resourceRecoltee(QPoint)));
    connect(m_reseau, SIGNAL(resource_repousse(int,int)), m_jeu, SLOT(resource_repousse(int,int)));
    connect(m_reseau, SIGNAL(infos_map(QString)), m_jeu, SLOT(infos_map(QString)));
    connect(m_jeu, SIGNAL(pnjclique(qint16, QPoint)), this, SLOT(dialoguePnj(qint16,QPoint)));
    connect(m_jeu, SIGNAL(faitRecette(QString)), this, SLOT(creerRecette(QString)));
    connect(m_jeu, SIGNAL(pourChat(QString)), this, SLOT(ajouteLigneChat(QString)));
    connect(m_jeu,SIGNAL(changePC(int)),m_layoutBarreOutil,SLOT(setPC(int)));
    connect(m_reseau, SIGNAL(passe_tour()), this, SLOT(tu_dois_passe_tour()));
    connect(m_reseau, SIGNAL(ton_tour()), this, SLOT(ton_tour()));
    connect(m_reseau,SIGNAL(gagneEquipement(QString)), this,SLOT(gagneEquipement(QString)));
    connect(m_reseau,SIGNAL(gagneArme(QString)), this,SLOT(gagneArme(QString)));
    connect(m_reseau,SIGNAL(gagneRessource(QString)), this,SLOT(gagneRessource(QString)));
    connect(m_reseau,SIGNAL(commenceFight()),this,SLOT(commenceFight()));
    connect(m_reseau,SIGNAL(changeVie(QString,int)),this,SLOT(changeVie(QString,int)));
    connect(m_reseau,SIGNAL(meurt(QString)),this,SLOT(meurt(QString)));
    connect(m_reseau,SIGNAL(changePos(QString,int,int)),m_jeu,SLOT(changePos(QString,int,int)));
    connect(m_reseau,SIGNAL(finFight(QString)),this,SLOT(finFight(QString)));

    QTimer *timer = new QTimer(m_jeu);
    connect(timer, SIGNAL(timeout()), m_jeu, SLOT(imagesuivante()));
    timer->start(1000/NBR_IMAGES_SECONDE);


    m_jeuui->jeu2d->setMouseTracking(true);

    m_jeu->installEventFilter(this);

    m_etat = Jeu;



    tu_dois_passe_tour();
    this->resize(size);
    //m_jeuui->jeu2d->setAttribute(Qt::WA_AlwaysShowToolTips);

    //part3 = QDateTime::currentMSecsSinceEpoch() - temps_actuel - part1 - part2;

    //QMessageBox::information(this, QString::number(part3), trUtf8("1 : ")+QString::number(part1)+trUtf8("; 2 : ")+QString::number(part2)+trUtf8("; 3 : ")+QString::number(part3));
}


void FenPrin::choixPerso()
{
    QSize size = this->size();
    if(m_etat == Connexion)
    {
        delete m_coui;
        m_coui = 0;
    }
    if(m_etat == CreerPerso)
    {
        delete m_creerui;
        m_creerui = 0;
    }
    else if(m_etat == Jeu)
    {
        delete m_jeuui;
        m_jeuui = 0;
        m_reseau->envoyer("cdp");
    }

    m_choixui = new Ui::ChoixMainWindow();
    m_choixui->setupUi(this);
    m_persoActuel = 0;

    if(m_compte->getNbrPerso())
    {
        m_choixui->image_persoactuel->setPixmap(QPixmap("../data/imagesdespersos/"+m_compte->getPerso(m_persoActuel)->getClasse()+'/'+m_compte->getPerso(m_persoActuel)->getClasse()+".png").scaled(QSize(this->size().width()*PLPERSOCHOIX, this->size().height()*PHPERSOCHOIX)));
        m_choixui->bout_jouer->setEnabled(true);
        m_choixui->bout_supprimer->setEnabled(true);
        m_choixui->nameperso->setText(m_compte->getPerso(m_persoActuel)->getNom());
    }

    connect(m_choixui->menu_jeu_quitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(m_choixui->menu_jeu_deco, SIGNAL(triggered()), this, SLOT(connexion()));
    connect(m_choixui->bout_jouer, SIGNAL(pressed()), this, SLOT(jeu()));
    connect(m_choixui->bout_creer, SIGNAL(pressed()), this, SLOT(persoPlus()));
    connect(m_choixui->bout_suiv, SIGNAL(pressed()), this, SLOT(persoSuivant()));
    connect(m_choixui->bout_pre, SIGNAL(pressed()), this, SLOT(persoPrecedent()));
    connect(m_choixui->bout_supprimer, SIGNAL(pressed()), this, SLOT(supprimmePerso()));

    m_etat = ChoixPersos;
    this->resize(size);
}


void FenPrin::connexion(bool choixDuServ)
{
    if(m_etat == ChoixPersos)
    {
        if(!choixDuServ)
            m_reseau->envoyer("dec");
        delete m_choixui;
        m_choixui = 0;
        delete m_compte;
        m_compte = 0;
    }
    else if(m_etat == CreerPerso)
    {
        if(!choixDuServ)
            m_reseau->envoyer("dec");
        delete m_creerui;
        m_creerui = 0;
        delete m_compte;
        m_compte = 0;
    }
    else if(m_etat == Jeu)
    {
        if(!choixDuServ)
            m_reseau->envoyer("dec");
        delete m_jeuui;
        m_jeuui = 0;
        delete m_compte;
        m_compte = 0;
    }


    m_coui = new Ui::CoMainWindow();
    m_coui->setupUi(this);

    connect(m_coui->bout_ins, SIGNAL(pressed()), this, SLOT(inscription()));
    connect(m_coui->bout_co, SIGNAL(pressed()), this, SLOT(essaiconnexion()));
    connect(m_coui->bar_ndc, SIGNAL(returnPressed()), this, SLOT(essaiconnexion()));
    connect(m_coui->bar_mdp, SIGNAL(returnPressed()), this, SLOT(essaiconnexion()));
    connect(m_coui->menu_jeu_quitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    m_etat = Connexion;
}

void FenPrin::creer()
{
    m_classeActuelle = "esudem";
    delete m_choixui;
    m_choixui = 0;
    m_creerui = new Ui::CreerMainWindow();
    m_creerui->setupUi(this);
    m_creerui->image_classe->setPixmap(QPixmap("../data/imagesdespersos/"+m_classeActuelle+'/'+m_classeActuelle+".png").scaled(QSize(this->size().width()*PLPERSOCREER, this->size().height()*PHPERSOCREER)));
    connect(m_creerui->bout_creer, SIGNAL(pressed()),this, SLOT(creerUnPerso()));
    connect(m_creerui->bout_annuler, SIGNAL(pressed()), this, SLOT(choixPerso()));
    connect(m_creerui->menu_jeu_quitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(m_creerui->menu_jeu_deco, SIGNAL(triggered()), this, SLOT(connexion()));
    connect(m_creerui->bout_suiv, SIGNAL(pressed()), this, SLOT(classeSuivante()));
    connect(m_creerui->bout_pre, SIGNAL(pressed()), this, SLOT(classePrecedente()));
    m_etat = CreerPerso;
}

void FenPrin::caracteristiques()
{
    Caracteristiques cara(this, m_compte->getPerso(m_persoActuel), m_reseau, m_donneesediteur);
}

bool FenPrin::eventFilter(QObject *obj, QEvent *event)
{
    if(m_etat == CreerPerso && m_creerui != 0)
    {
        if (obj == this)
        {
                 if(event->type() == QEvent::Resize)
                 {
                     m_creerui->image_classe->setPixmap(QPixmap("../data/imagesdespersos/"+m_classeActuelle+'/'+m_classeActuelle+".png").scaled(QSize(this->size().width()*PLPERSOCREER, this->size().height()*PHPERSOCREER)));
                     return true;
                 }
                 else
                 {
                     return QMainWindow::eventFilter(obj, event);
                 }
        }
        else
        {
            return QMainWindow::eventFilter(obj, event);
        }
    }
    else if(m_etat == ChoixPersos && m_choixui != 0)
    {
        if(obj == this)
        {
            if (event->type() == QEvent::Resize)
            {
                if(m_compte->getNbrPerso())
                    m_choixui->image_persoactuel->setPixmap(QPixmap("../data/imagesdespersos/"+m_compte->getPerso(m_persoActuel)->getClasse()+'/'+m_compte->getPerso(m_persoActuel)->getClasse()+".png").scaled(QSize(this->size().width()*PLPERSOCHOIX, this->size().height()*PHPERSOCHOIX)));
                return true;
            }
            else
            {
                return QMainWindow::eventFilter(obj, event);
            }
        }
        else
        {
            return QMainWindow::eventFilter(obj, event);
        }
    }
    else if(m_etat == Jeu && m_jeuui != 0)
    {
        if(obj == this && event->type() == QEvent::Resize)
        {
            qDebug() << "au travail !";
            //QMainWindow::eventFilter(obj,event);
            int width2 = this->width();
            int height2 = this->height()-HAUTEUR_BARRE_OUTIL;
            /*if(width2 > (int)(((double)height2)*screenFormat))
            {
                width2 = (int)(((double)height2)*screenFormat);
            }
            else
            {
                height2 = (int)(((double)width2)/screenFormat);
            }*/
            m_jeu->resize(QSize(width2,height2));
            m_jeuui->jeu2d->setSceneRect(0,0,width2,height2);
            return true;
        }
        else if(obj == m_jeu && event->type() == QEvent::GraphicsSceneMousePress)
        {
            QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                m_jeu->cliqueGauche(mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
            }
            else if(m_jeu->phase() == HorsFight)
            {
                QString name = m_jeu->contientJoueur();
                if(name != m_compte->getPerso(m_persoActuel)->getNom() && !name.isEmpty())
                {
                    if(m_jeu->getJoueur(name)->getEntityModel()->isMonster())
                    {
                        WindowActions * windowAction = new WindowActions(m_jeu,m_jeu->getJoueur(name)->getEntityModel()->getClass(),name);
                        connect(windowAction, SIGNAL(attackMonster(QString)),this,SLOT(attackMonster(QString)));
                    }
                }
            }
            else if(m_jeu->monTour())
            {
                QString name = m_jeu->contientJoueur();
                if(!name.isEmpty())
                {

                }
            }
            return QMainWindow::eventFilter(obj, event);
        }
        /*else if(obj == m_jeu && event->type() == QEvent::GraphicsSceneMove)
        {
            //QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
            //QPoint p = m_jeu->ccase(mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
            //m_bout_passer_tour->setText("x:"+QString::number(p.x())+";y:"+QString::number(p.y()));
            //m_jeu->souris_bouge(mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
        }*/
        else
        {
            return QMainWindow::eventFilter(obj, event);
        }
    }
    else
    {
        return QMainWindow::eventFilter(obj, event);
    }
}

void FenPrin::classeSuivante()
{
    m_classeActuelle = m_donneesediteur->resources->classeSuivante(m_classeActuelle);
    m_creerui->image_classe->setPixmap(QPixmap("../data/imagesdespersos/"+m_classeActuelle+'/'+m_classeActuelle+".png").scaled(QSize(this->size().width()*PLPERSOCREER, this->size().height()*PHPERSOCREER)));
}

void FenPrin::classePrecedente()
{
    m_classeActuelle = m_donneesediteur->resources->classeSuivante(m_classeActuelle);
    m_creerui->image_classe->setPixmap(QPixmap("../data/imagesdespersos/"+m_classeActuelle+'/'+m_classeActuelle+".png").scaled(QSize(this->size().width()*PLPERSOCREER, this->size().height()*PHPERSOCREER)));
}

void FenPrin::persoSuivant()
{
    if(m_compte->getNbrPerso())
    {
        m_persoActuel++;
        if(m_persoActuel >= m_compte->getNbrPerso())
            m_persoActuel = 0;
        m_choixui->image_persoactuel->setPixmap(QPixmap("../data/imagesdespersos/"+m_compte->getPerso(m_persoActuel)->getClasse()+'/'+m_compte->getPerso(m_persoActuel)->getClasse()+".png").scaled(QSize(this->size().width()*PLPERSOCHOIX, this->size().height()*PHPERSOCHOIX)));
        m_choixui->nameperso->setText(m_compte->getPerso(m_persoActuel)->getNom());
    }
}

void FenPrin::persoPrecedent()
{
    if(m_compte->getNbrPerso())
    {
        m_persoActuel--;
        if(m_persoActuel < 0)
            m_persoActuel = m_compte->getNbrPerso()-1;
        m_choixui->image_persoactuel->setPixmap(QPixmap("../data/imagesdespersos/"+m_compte->getPerso(m_persoActuel)->getClasse()+'/'+m_compte->getPerso(m_persoActuel)->getClasse()+".png").scaled(QSize(this->size().width()*PLPERSOCHOIX, this->size().height()*PHPERSOCHOIX)));
        m_choixui->nameperso->setText(m_compte->getPerso(m_persoActuel)->getNom());
    }
}


void FenPrin::supprimmePerso()
{
    if(QMessageBox::question(this, "Suppression d'un personnage", "Voulez vous vraiment supprimer ce personnage ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        m_reseau->envoyer("spr/"+QString::number(m_persoActuel));
        m_compte->supprimme(m_persoActuel);
        m_persoActuel = 0;
        if(m_compte->getNbrPerso())
        {
            m_choixui->image_persoactuel->setPixmap(QPixmap("../data/imagesdespersos/"+m_compte->getPerso(m_persoActuel)->getClasse()+'/'+m_compte->getPerso(m_persoActuel)->getClasse()+".png").scaled(QSize(this->size().width()*PLPERSOCHOIX, this->size().height()*PHPERSOCHOIX)));
            m_choixui->nameperso->setText(m_compte->getPerso(m_persoActuel)->getNom());
        }
        else
        {
            m_choixui->image_persoactuel->setText("Vous n'avez aucun personnage.");
            m_choixui->nameperso->setText("name inconnu");
            m_choixui->bout_jouer->setEnabled(false);
            m_choixui->bout_supprimer->setEnabled(false);
        }
    }

}



void FenPrin::creerUnPerso()
{
    QString texte="PERSO/";
    Character *perso = new Character(m_creerui->bar_name->text(), m_classeActuelle, m_donneesediteur);
    m_compte->ajouteUnPerso(perso);
    texte += perso->toString();

    m_reseau->envoyer("new/"+texte);
    choixPerso();
}

void FenPrin::persoPlus()
{
    if(m_compte->getNbrPerso() <= 2)
    {
        creer();
    }
}



void FenPrin::defiCommance(int equipe)
{
    m_jeu->phasePlacement(m_fight,equipe);
    m_boxannul->close();
    //m_bar_vie->setMaximum(m_jeu->getPerso()->getTotalVie());
    m_compte->getPerso(m_persoActuel)->setPret(false);
    m_layoutBarreOutil->phasePlacement();
}

void FenPrin::annuleDemandeDefi()
{
    if(m_fight != 0 && m_fight->leader() == m_compte->getPerso(m_persoActuel)->getNom() && m_jeu->phase() == HorsFight)
    {
        m_reseau->envoyer("fight/annuleDemandeDefi/");
        delete m_fight;
    }
}

void FenPrin::onMeProposeDefi(QString qui)
{
    m_fight = new Fight(qui, m_compte->getPerso(m_persoActuel));
    m_boxquestion->setText(trUtf8("Souhaitez-vous faire un défi avec ") + qui +" ?");
    int rep = m_boxquestion->exec();
    if(rep == QMessageBox::Ok)
    {
        m_reseau->envoyer("fight/accepteDemandeDefi");
    }
    else if(rep == QMessageBox::Cancel)
    {
        m_reseau->envoyer("fight/refuseDemandeDefi");
    }
}

void FenPrin::ilRefuseDefi()
{
    delete m_fight;
    m_fight = 0;
    m_boxannul->close();
}


void FenPrin::echangeCommance()
{
    //qApp->quit();
    //m_nameDeLautre.clear();
}

void FenPrin::accepteEchange()
{
    //m_reseau->envoyer("eac/"+m_nameDeLautre);
}

void FenPrin::refuseEchange()
{
    //m_reseau->envoyer("ere/"+m_nameDeLautre);
}

void FenPrin::annuleDemandeEchange()
{
    /*m_reseau->envoyer("ean/"+m_nameDeLautre);
    m_nameDeLautre.clear();
    m_cestmoiquiestdemande = false;*/
}

void FenPrin::onMeProposeEchange(QString qui)
{
    /*m_nameDeLautre = qui;
    m_boxquestion->setText(trUtf8("Souhaitez-vous faire un échange avec ") + m_nameDeLautre +" ?");
    int rep = m_boxquestion->exec();
    if(rep == QMessageBox::Ok)
    {
        m_reseau->envoyer("eda/"+m_nameDeLautre);
    }
    else if(rep == QMessageBox::Cancel)
    {
        m_reseau->envoyer("edr/"+m_nameDeLautre);
    }*/
    /*connect(m_boxquestion, SIGNAL(accepted()), this, SLOT(echangeAcc()));
    connect(m_boxquestion, SIGNAL(rejected()), this, SLOT(echangeRef()));*/
}

void FenPrin::annuleEchangeEnCour()
{
    /*m_boxquestion->done(-4);
    m_nameDeLautre.clear();
    m_reseau->envoyer("eca/"+m_nameDeLautre);*/
}



void FenPrin::connexionAcc(QString donnees)
{
    m_compte = new Compte(donnees,"", m_donneesediteur);
    choixPerso();
}


void FenPrin::connexionRef()
{
    QMessageBox::critical(this, trUtf8("erreur lors de la connexion"), trUtf8("ERREUR : identifiants incorects."));
}

void FenPrin::qqAutre()
{
    connexion(true);
    QMessageBox::critical(this, trUtf8("erreur"), trUtf8("ERREUR : quelqun c'est connecté à votre place."));
}

void FenPrin::deplacement(QString qui, QPoint ou)
{
    if(m_jeu->phase() == HorsFight)
    {
        m_jeu->deplace(qui, m_jeu->dataMap()->calculchemin(m_jeu->getJoueur(qui)->posALaFin(),ou));
    }
    else if(m_jeu->phase() == EnPlacement)
    {
        m_jeu->changePos(qui,ou.x(),ou.y());
    }
    else if(m_jeu->phase() == EnFight)
    {
        m_jeu->deplaceFight(qui,ou);
    }
}

void FenPrin::dialoguePnj(qint16 num, QPoint pos)
{
    QString reponse;
    NPC *pers = m_jeu->donneesediteur()->touslespnj->getpnj(num);
    Dialoguepnj boite(this, pers, &reponse);
    analyseReponsePnj(reponse);
    m_jeu->updateObjet(pos);
}

void FenPrin::analyseReponsePnj(QString const& reponse)
{
    if(reponse.isEmpty())
    {
        return;
    }
    else if(reponse.section('_', 0, 0) == "metier")
    {
        m_compte->getPerso(m_persoActuel)->learnJob(reponse.section('_', 1,1));
        m_reseau->envoyer("pnj/"+reponse);
    }
    else
    {
        m_reseau->envoyer("pnj/"+reponse);
    }
}

void FenPrin::creerRecette(QString metier)
{
    FaireRecettes box(this, metier, m_donneesediteur, m_compte->getPerso(m_persoActuel), m_reseau);
    //QMessageBox::information(this, "creation", "metier : "+metier);
}

void FenPrin::commenceFight()
{
    m_jeu->phaseFight();
    tu_dois_passe_tour();
    m_layoutBarreOutil->phaseFight();
}

void FenPrin::je_passe_tour()
{
    if(m_jeu->phase() == EnPlacement)
    {
        if(m_compte->getPerso(m_persoActuel)->pret())
        {
            m_reseau->envoyer("fight/pasPret");
            m_compte->getPerso(m_persoActuel)->setPret(false);
        }
        else
        {
            m_reseau->envoyer("fight/pret");
            m_compte->getPerso(m_persoActuel)->setPret(true);
        }
        m_layoutBarreOutil->setPret(m_compte->getPerso(m_persoActuel)->pret());
    }
    else if(m_jeu->phase() == EnFight && m_jeu->monTour())
    {
        m_reseau->envoyer("fight/passeTour");
    }
}

void FenPrin::tu_dois_passe_tour()
{
    m_jeu->setMonTour(false);
    m_layoutBarreOutil->setMonTour(false);
}

void FenPrin::ton_tour()
{
    QMessageBox::information(this, trUtf8("haha"), trUtf8("a ton tour"));
    m_jeu->setMonTour(true);
    m_layoutBarreOutil->setMonTour(true);
}

void FenPrin::utiliseSpell(QString name)// à passer dans layoutBarreOutil
{
    if(m_jeu->phase() == EnFight && m_jeu->monTour())
    {
        if(m_jeu->getPerso()->peutUtiliserSpell(name))
        {
            m_jeu->veut_utiliserSpell(m_jeu->getPerso()->getSpell(name));
        }
    }
}

void FenPrin::gagneEquipement(QString donnees)
{
    m_compte->getPerso(m_persoActuel)->ajouterEquipement(new Outfit(donnees,m_donneesediteur->resources));
}

void FenPrin::gagneArme(QString donnees)
{
    m_compte->getPerso(m_persoActuel)->ajouterArme(new Weapon(donnees,m_donneesediteur->resources));
}

void FenPrin::gagneRessource(QString donnees)
{
    m_compte->getPerso(m_persoActuel)->ajouterRessource(m_donneesediteur->resources->getRessource(donnees));
}

void FenPrin::meurt(QString const& name)
{
    if(name == m_compte->getPerso(m_persoActuel)->getNom())
    {
        if(m_jeu->monTour())
            tu_dois_passe_tour();
    }
    m_jeu->meurt(name);
}

void FenPrin::finFight(QString const& texte)
{
    m_jeu->phaseFinFight();
    WindowEndFight boite(texte,this,m_compte->getPerso(m_persoActuel));
}

void FenPrin::changeVie(QString const& name, int vie)
{
    m_jeu->setVie(name,vie);
    if(name == m_compte->getPerso(m_persoActuel)->getNom())
    {
        m_layoutBarreOutil->setVie(vie);
    }
}

void FenPrin::attackMonster(QString const& name)
{
    m_reseau->envoyer("fight/attackMonster/"+name);
    qDebug() << "veut fighttre " << name;
    //m_reseau->envoyer("fight/jeDemandeDefi/"+name);
    //m_boxannul->setText(trUtf8("Demande de defi à ")+name+(" en cours..."));
    //m_boxannul->open(this, SLOT(annuleDemandeDefi()));
    //m_fight = new Fight(m_compte->getPerso(m_persoActuel)->getNom(), m_compte->getPerso(m_persoActuel));
}




