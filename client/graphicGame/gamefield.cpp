#include "gamefield.h"
#include "affichejoueur.h"
#include <QGraphicsSceneMouseEvent>
#include "network/reseau.h"
#include <QDebug>
#define ARROW_DISPLAY_DIST 40

GameField::GameField(const QSize &size, Character *pers, QTcpSocket *sock, Data *donnees_editeur) : GameScene(size,0,donnees_editeur)
{
    QElapsedTimer elapsed;
    elapsed.start();
    qDebug() << "time : " << elapsed.elapsed();
    m_displayGrid = false;
    m_sort_a_utiliser = 0;
    m_combat = 0;
    m_nomMetier = "";
    m_combatOuPas = HorsCombat;
    m_socket = sock;
    m_character = pers;
    qDebug() << "time : " << elapsed.elapsed();
    charge(pers->getPosX(), pers->getPosY(), pers->getPosZ());
    qDebug() << "time : " << elapsed.elapsed();
    EntityInfo inf;
    inf.classe = pers->getClasse();
    inf.nom = pers->getNom();
    inf.posmap = pers->getPosMap();
    inf.monster = false;
    m_fleche = addPixmap(QPixmap());
    m_fleche->setZValue(4+NBR_CASES_H);
    m_posFleche = QPoint(-1,-1);
    addEntity(inf);
    qDebug() << "time : " << elapsed.elapsed();
    resize(size);
    qDebug() << "time : " << elapsed.elapsed();
}

GameField::~GameField()
{
    for(QMap<QString, AfficheJoueur*>::iterator i = m_persos.begin(); i != m_persos.end(); i++)
    {
        delete i.value();
    }
}

void GameField::resize(QSize const& newSize)
{
    GameScene::resize(newSize);
    for(QMap<QString,AfficheJoueur*>::iterator i = m_persos.begin(); i != m_persos.end(); i++)
    {
        i.value()->resize(m_lcase, m_hcase);
    }
}

void GameField::cliqueGauche(int x, int y)
{
    if(m_subWinOpened)
        return;
    if(m_combatOuPas == HorsCombat)
    {
        QPoint p = fleche();
        QQueue<Dir> chem;
        if(p.x() != -1)//gere la fleche et le changement de map
        {
            chem = m_dataMap->calculchemin(getJoueur(m_character->getNom())->posALaFin(), p);
            if(!chem.isEmpty())
                envoyerM(m_socket, "dep/"+m_character->getNom()+'*'+QString::number(p.x())+QString::number(p.y()));
            if(!chem.isEmpty() || p == getJoueur(m_character->getNom())->posALaFin())
            {
                m_maparrx = m_dataMap->x();
                m_maparry = m_dataMap->y();
                m_maparrz = m_dataMap->z();
                m_cooarrx = p.x();
                m_cooarry = p.y();

                if(direction_fleche() == O)
                {
                    m_maparry--;
                    m_cooarry += NBR_CASES_H-CASESCACHEESY*2-1;
                }
                else if(direction_fleche() == B)
                {
                    m_maparry++;
                    m_cooarry -= NBR_CASES_H-CASESCACHEESY*2-1;
                }
                else if(direction_fleche() == G)
                {
                    m_maparrx--;
                    m_cooarrx = NBR_CASES_L-CASESCACHEESX-1;
                }
                else
                {
                    m_maparrx++;
                    m_cooarrx = CASESCACHEESX;
                }
                deplace(m_character->getNom(), chem, Actions_personnage::ChangeDeMap);
            }
            else
            {
                deplace(m_character->getNom(), chem);
            }
            return;
        }
        p = m_dataMap->ccase(x, y,getlmap(),gethmap(),getlcase(),gethcase(),true);
        if(p.x() != -1)//gere le deplacement sans changer de map
        {
            chem = m_dataMap->calculchemin(getJoueur(m_character->getNom())->posALaFin(), p);
            if(!chem.isEmpty())
            {
                deplace(m_character->getNom(), chem);
                envoyerM(m_socket, "dep/"+m_character->getNom()+'*'+QString::number(p.x()) +'*'+QString::number(p.y()));
            }
        }
    }
    else if(m_combatOuPas == EnPlacement)
    {
        QPoint p = m_dataMap->ccase(x, y,getlmap(),gethmap(),getlcase(),gethcase(),true);
        if(m_dataMap->estCaseDeDepart(p.x(),p.y(),m_character->equipe()))
        {
            if(!contientJoueur(p))
            {
                envoyerM(m_socket, "combat/changePosDep/"+QString::number(p.x())+"*"+QString::number(p.y()));
            }
        }
    }
    else if(m_combatOuPas == EnCombat && m_character->monTour() && getJoueur(m_character->getNom())->isImobile())
    {
        if(!m_sort_a_utiliser)
        {
            QPoint arrivee = m_dataMap->ccase(x, y,getlmap(),gethmap(),getlcase(),gethcase(),true);
            QQueue<Dir> chem = m_dataMap->calculcheminCombat(getJoueur(m_character->getNom())->posALaFin(), arrivee, m_character->getPCCombat());
            if(!chem.isEmpty())
            {
                m_character->use_pc(chem.size());
                emit changePC(m_character->getPCCombat());
                envoyerM(m_socket, "combat/dep/"+QString::number(arrivee.x())+"*"+QString::number(arrivee.y()));
            }
        }
        else
        {
            QPoint p = posCaseVisee();
            stopUtiliseSort();
            if(p.x() != -1)
            {
                m_character->use_pc(m_sort_a_utiliser->points_combat());
                emit changePC(m_character->getPCCombat());
                envoyerM(m_socket,"combat/attaque/"+m_sort_a_utiliser->nom()+"/"+QString::number(p.x())+"/"+QString::number(p.y()));
            }
            m_sort_a_utiliser = 0;
        }
    }
}

void GameField::setMonTour(bool monTour)
{
    effaceChemin();
    m_character->nouveau_tour();
    m_character->setTour(monTour);
    m_sort_a_utiliser = 0;
    emit changePC(m_character->getPCCombat());
}

void GameField::veut_utiliserSort(Spell *sort)
{
    effaceChemin();
    m_sort_a_utiliser = sort;
    utiliseSort(sort);
}

void GameField::phasePlacement(Combat *combat,int equipe)
{
    m_character->setEquipe(equipe);
    m_combatOuPas = EnPlacement;
    affiche_casesCombat();
    setMonTour(false);
}

void GameField::phaseCombat()
{
    m_combatOuPas = EnCombat;
    masque_casesCombat();
    marche_pas();
}

void GameField::phaseFinCombat()
{
    if(m_combatOuPas == EnPlacement)
        masque_casesCombat();
    m_combatOuPas = HorsCombat;
    m_combat = 0;
    effaceChemin();
    //cachePortee();
}

void GameField::deplaceCombat(const QString &qui, const QPoint &ou)
{
    QPoint dep = getJoueur(qui)->posALaFin();
    deplace(qui, m_dataMap->calculcheminCombat(dep,ou, 1000));
    m_dataMap->setCasePleineCombat(dep.x(), dep.y(), 0);
    m_dataMap->setCasePleineCombat(ou.x(), ou.y(), 2);
}

void GameField::changeDeMap(int mapx, int mapy, int mapz, int coox,int cooy)
{
    charge(mapx,mapy, mapz);
    changePlayerMap(coox, cooy);
    QString mess = "cdm/"+QString::number(mapx)+"/"+QString::number(mapy)+"/"+QString::number(mapz)+"/"+QString::number(coox)+"/"+QString::number(cooy);
    envoyerM(m_socket, mess);
    m_posFleche = QPoint(-1,-1);
    m_fleche->setVisible(false);
}

AfficheJoueur *GameField::getJoueur(QString const& nom)
{
    if(m_persos.contains(nom))
        return m_persos[nom];
    else
    {
        qDebug() << "perso doesn't exist : " << nom;
        return 0;
    }
}

void GameField::utileClique(QPoint const& pos)
{
    if(m_subWinOpened)
        return;
    if(m_combatOuPas == HorsCombat)
    {
        qDebug() << "clique utile !";
        Object *obj = m_dataMap->objet(pos.x(),pos.y(),2);
        if(obj->categorie() == "pnj")
        {
            qDebug() << "pnj";
            emit pnjclique(obj->numero(),pos);
        }
        else if(obj->categorie() == "forge")
        {
            JobModel *metier = m_donnees_editeur->metiers->forge_to_metier(obj);
            if(metier)
            {
                if(!m_character->arme())
                {
                    emit pourChat(QObject::trUtf8("Vous n'avez pas l'arme appropriée pour exercer ce métier : ")+metier->arme());
                }
                else if(m_character->arme()->getEquipement()->getRessource()->categorie() == metier->arme())
                {
                    m_nomMetier = metier->nom();//pour les recettes
                    QPoint p;
                    QQueue<Dir> chemin = m_dataMap->calculcheminJusquaLObjet(getJoueur(m_character->getNom())->posALaFin() , pos, &p);
                    if(!chemin.isEmpty())
                    {
                        deplace(m_character->getNom(), chemin, Actions_personnage::Recettes);
                        envoyerM(m_socket, "dep/"+m_character->getNom()+'*'+QString::number(p.x()) +'*'+QString::number(p.y()));
                    }
                    else if(p.x())
                    {
                        emit faitRecette(m_nomMetier);
                    }
                }
                else
                {
                    emit pourChat(QObject::trUtf8("Vous n'avez pas l'arme appropriée pour exercer ce métier : ")+metier->arme());
                }
            }
        }
        else if(m_donnees_editeur->metiers->est_un_objet_coupable(obj->numero()))
        {
            m_pos_ressource = pos;
            qDebug() << obj->numero();
            JobModel *metier = m_donnees_editeur->metiers->objet_coupable_to_metier(obj);
            if(metier)
            {
                if(!m_character->arme())
                {
                    emit pourChat(QObject::trUtf8("Vous ne pouvez pas pas récolter cette ressource"));
                }
                else if(m_character->arme()->getEquipement()->getRessource()->categorie() == metier->arme() && m_character->getMetier(metier->nom()) != 0 && metier->objet_coupable(obj->numero())->lvl() <= m_character->getMetier(metier->nom())->getLvl())
                {
                    QPoint p;
                    QQueue<Dir> chemin = m_dataMap->calculcheminJusquaLObjet(getJoueur(m_character->getNom())->posALaFin() , pos, &p);
                    if(!chemin.isEmpty())
                    {
                        deplace(m_character->getNom(), chemin, Actions_personnage::Recolter);
                        m_orientation = orientation_vers_objet(p, pos);
                        envoyerM(m_socket, "dep/"+m_character->getNom()+'*'+QString::number(p.x()) +'*'+QString::number(p.y()));
                        m_nomMetier = metier->nom();//pour la recolte
                    }
                    else if(p.x() != 0)
                    {
                        m_orientation = orientation_vers_objet(p, pos);
                        qDebug() << "nom metier";
                        m_nomMetier = metier->nom();
                        qDebug() << "=metier nom";
                        doit_recolter();
                    }
                }
                else
                {
                    emit pourChat(QObject::trUtf8("Vous ne pouvez pas pas récolter cette ressource"));
                }
            }
        }
    }
}

void GameField::changeMap()
{
    changeDeMap(m_maparrx, m_maparry, m_maparrz, m_cooarrx, m_cooarry);
}

void GameField::fait_recettes()
{
    emit faitRecette(m_nomMetier);
}

void GameField::doit_recolter()
{
    int orientation = m_orientation;
    recolte(m_character->getNom(), m_character->getMetier(m_nomMetier)->getMetierBase()->verbe(), m_orientation, m_character->getMetier(m_nomMetier)->nbrCoups(), Actions_personnage::ARecolter);
    envoyerM(m_socket, "cut/"+m_character->getNom()+'*'+m_character->getMetier(m_nomMetier)->getMetierBase()->verbe()+'*'+QString::number(orientation)+'*'+QString::number(m_character->getMetier(m_nomMetier)->nbrCoups()));
}

void GameField::ressourceRecoltee(QPoint pos)
{
    caseEgale(pos.x(), pos.y(), m_donnees_editeur->metiers->getSoucheParObjet(m_dataMap->objet(pos.x(),pos.y(),2)->numero()), 2);
}

void GameField::ressource_repousse(int posx, int posy)
{
    caseEgale(posx, posy, m_donnees_editeur->metiers->getObjetParSouche(m_dataMap->objet(posx,posy,2)->numero()), 2);
}

void GameField::a_coupe()
{
    qint16 numobj = m_dataMap->objet(m_pos_ressource.x(),m_pos_ressource.y(),2)->numero();
    Job *metier = m_character->getMetier(m_nomMetier);
    int xp = xpCoupeRessource(metier->getMetierBase()->objet_coupable(numobj)->lvl());
    int nombre_ressources = metier->nombre_ressources(numobj);
    metier->gagneXp(xp);
    QString ajoutees = m_character->gagneRessources(metier->getMetierBase()->objet_coupable(numobj)->getRessource(), nombre_ressources);
    ressourceRecoltee(m_pos_ressource);
    envoyerM(m_socket, "cop/"+QString::number(m_pos_ressource.x())+'*'+QString::number(m_pos_ressource.y())+'/'+metier->getNomMetier()+'/'+QString::number(xp)+'/'+ajoutees);
}

void GameField::infos_map(QString infos)
{
    QString unJoueur;
    EntityInfo perso;
    while(infos.at(0) != '/')
    {
        ressourceRecoltee(QPoint(infos.mid(0,2).toInt(), infos.mid(2,2).toInt()));
        infos = infos.mid(4);
    }
    infos = infos.mid(1);
    while(infos.size() > 0)
    {
        unJoueur = infos.section('/', 0,0);
        perso.nom = unJoueur.section('*', 0, 0);
        perso.classe = unJoueur.section('*', 1, 1);
        perso.posmap = QPoint(unJoueur.section('*', 2,2).toInt(), unJoueur.section('*', 3, 3).toInt());
        perso.monster = (bool) unJoueur.section('*',4,4).toInt();
        addEntity(perso);
        infos = infos.section('/', 1);
    }
}

void GameField::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
    if(m_subWinOpened)
        return;
    int x = mouseEvent->scenePos().x(), y = mouseEvent->scenePos().y();
    if(phase() == HorsCombat)
    {
        /*for(QMap<QString,AfficheJoueur*>::iterator it = m_persos.begin();it != m_persos.end(); it++)
        {
            if(it.value()->isUnderMouse())
                it.value()->displayToolTip();
            else
                it.value()->hideToolTip();
        }*/
        m_fleche->setVisible(false);
        m_posFleche.setX(-1);
        m_posFleche.setY(-1);
        if(x < ARROW_DISPLAY_DIST)
        {
            m_posFleche = m_dataMap->case_gauche(m_dataMap->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true));
            if(m_posFleche.x() != -1)
            {
                m_directionChangeMap = G;
                m_fleche->setVisible(true);
                m_fleche->setPixmap(QPixmap("../data/interface/flecheg.png").scaled(QSize(50,75)));
                m_fleche->setPos(0, m_dataMap->cposy(m_posFleche.y(),m_hcase,true)-m_fleche->pixmap().height()/2);
            }
        }
        else if(x > m_lmap-ARROW_DISPLAY_DIST)
        {
            m_posFleche = m_dataMap->case_droite(m_dataMap->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true));
            if(m_posFleche.x() != -1)
            {
                m_directionChangeMap = D;
                m_fleche->setVisible(true);
                m_fleche->setPixmap(QPixmap("../data/interface/fleched.png").scaled(QSize(50,75)));
                m_fleche->setPos(m_lmap-m_fleche->pixmap().width(), m_dataMap->cposy(m_posFleche.y(),m_hcase,true)-m_fleche->pixmap().height()/2);
            }
        }
        else if(y < ARROW_DISPLAY_DIST)
        {
            m_posFleche = m_dataMap->case_haut(m_dataMap->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true));
            if(m_posFleche.x() != -1)
            {
                m_directionChangeMap = O;
                m_fleche->setVisible(true);
                m_fleche->setPixmap(QPixmap("../data/interface/flecheo.png").scaled(QSize(75,50)));
                m_fleche->setPos(m_dataMap->cposx(m_posFleche.x(), m_posFleche.y(),m_lcase,true)-m_fleche->pixmap().width()/2, 0);
            }
        }
        else if(y > m_hmap - ARROW_DISPLAY_DIST)
        {
            m_posFleche = m_dataMap->case_bas(m_dataMap->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true));
            if(m_posFleche.x() != -1)
            {
                m_directionChangeMap = B;
                m_fleche->setVisible(true);
                m_fleche->setPixmap(QPixmap("../data/interface/flecheb.png").scaled(QSize(75,50)));
                m_fleche->setPos(m_dataMap->cposx(m_posFleche.x(), m_posFleche.y(),m_lcase,true)-m_fleche->pixmap().width()/2, m_hmap-m_fleche->pixmap().height());
            }
        }
    }
    else if(phase() == EnPlacement)
    {
        /*for(QMap<QString,AfficheJoueur*>::iterator it = m_persos.begin();it != m_persos.end(); it++)
        {
            if(it.value()->isUnderMouse())
                it.value()->displayToolTip();
            else
                it.value()->hideToolTip();
        }*/
    }
    else if(phase() == EnCombat)
    {
        if(sort())
        {
            m_posCaseVisee = QPoint(-1,-1);
            /*for(QMap<QString,AfficheJoueur*>::iterator it = m_persos.begin();it != m_persos.end(); it++)
            {
                if(it.value()->isUnderMouse())
                {
                    it.value()->displayToolTip();
                    m_posCaseVisee = it.value()->posALaFin();
                }
                else
                    it.value()->hideToolTip();
            }*/
            if(m_posCaseVisee.x() == -1)
            {
                m_posCaseVisee = m_dataMap->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true);
            }
            if(caseExiste(m_posCaseVisee.x(),m_posCaseVisee.y()) && m_cases_ateignables[m_posCaseVisee.x()][m_posCaseVisee.y()])
            {
                m_imgCaseVisee->setVisible(true);
                m_imgCaseVisee->setPos(m_dataMap->cposx(m_posCaseVisee.x(),m_posCaseVisee.y(),m_lcase,true)-m_mlcase, m_dataMap->cposy(m_posCaseVisee.y(),m_hcase,true)-m_mhcase);
            }
            else
            {
                m_posCaseVisee = QPoint(-1,-1);
                m_imgCaseVisee->setVisible(false);
            }
        }
        else
        {
            for(QMap<QString,AfficheJoueur*>::iterator it = m_persos.begin();it != m_persos.end(); it++)
            {
                if(it.value()->isUnderMouse())
                    it.value()->displayToolTip();
                else
                    it.value()->hideToolTip();
            }
            if(monTour() && m_persos[m_character->getNom()]->isImobile())
            {
                QPoint arrivee = m_dataMap->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true);
                if(arrivee.x() != -1)
                {
                    if(arrivee != m_ancienne)
                    {
                        effaceChemin();
                        m_ancienne = arrivee;
                        QQueue<Dir> chem = m_dataMap->calculcheminCombat(getJoueur(m_character->getNom())->posALaFin(), arrivee, getPerso()->getPCCombat());
                        if(!chem.isEmpty())
                        {
                            afficheChemin(getJoueur(m_character->getNom())->posALaFin(), chem);
                        }
                    }
                }
                else if(m_ancienne.x() != -1)
                {
                    m_ancienne = arrivee;
                    effaceChemin();
                }
            }
        }
    }
}

void GameField::dragLeaveEvent(QGraphicsSceneDragDropEvent *)
{
    m_fleche->setVisible(false);
    m_posFleche.setX(-1);
    m_posFleche.setY(-1);
}

void GameField::deplace(QString const& nom, const QQueue<Dir> &chem, Actions_personnage::DerniereAction action)
{
    if(phase() == EnCombat && monTour())
        effaceChemin();
    m_persos[nom]->nouveauchemin(chem, action);
}

void GameField::utiliseSort(Spell *sort)
{
    m_dataMap->calculPortee(m_cases_ateignables, m_persos[m_character->getNom()]->posALaFin().x(), m_persos[m_character->getNom()]->posALaFin().y(),sort->portee_min(), sort->portee_max());
    affichePortee();
}

void GameField::marche_pas()
{
    for(QMap<QString,AfficheJoueur*>::iterator it = m_persos.begin(); it != m_persos.end(); it++)
    {
        QPoint p = it.value()->posALaFin();
        m_dataMap->setCasePleineCombat(p.x(),p.y(),2);
    }
}

void GameField::recolte(const QString &nom, QString const& verbe, Dir orientation, int nombre_coups, Actions_personnage::DerniereAction derniere_action)
{
    m_persos[nom]->recolte(verbe, nombre_coups, orientation, derniere_action);
}

void GameField::recolte(const QString &nom, QString const& verbe, int orientation, int nombre_coups, Actions_personnage::DerniereAction derniere_action)
{
    recolte(nom, verbe, (Dir)orientation, nombre_coups, derniere_action);
}

void GameField::setVie(QString const& nom, int vie)
{
    m_persos[nom]->changeToolTip(nom+" ("+QString::number(vie)+")");
}

void GameField::meurt(QString const& nom)
{
    m_persos[nom]->setPos(-100,-100);
}

void GameField::imagesuivante()
{
    for(QMap<QString, AfficheJoueur*>::iterator i = m_persos.begin(); i != m_persos.end(); i++)
    {
       i.value()->suivante();
    }
}

void GameField::changePlayerMap(int largX, int largY)
{
    m_persos[m_character->getNom()]->changePos(largX, largY);
    QStringList asuprr;
    for(QMap<QString,AfficheJoueur*>::iterator i = m_persos.begin(); i != m_persos.end(); i++)
    {
        if(i.key() != m_character->getNom())
        {
            asuprr.append(i.key());
        }
    }
    while(!asuprr.isEmpty())
    {
        removeEntity(asuprr.first());
        asuprr.pop_front();
    }
}

void GameField::ajouteChemin(QString const& nom, QQueue<Dir> const& chemin)
{
    m_persos[nom]->nouveauchemin(chemin);
}

QString GameField::contientJoueur()
{
    for(QMap<QString, AfficheJoueur*>::iterator i = m_persos.begin(); i != m_persos.end(); i++)
    {
        if(i.value()->isUnderMouse())
        {
            return i.key();
        }
    }
    return "";
}

bool GameField::contientJoueur(QPoint const& pos)
{
    for(QMap<QString,AfficheJoueur*>::iterator it = m_persos.begin(); it != m_persos.end();it++)
    {
        if(it.value()->posALaFin() == pos)
            return true;
    }
    return false;
}

void GameField::addEntity(EntityInfo perso)
{
    qDebug() << "adding entity " << perso.nom << " monster ? " << perso.monster;
    m_persos[perso.nom] = new AfficheJoueur(m_donnees_editeur->ressources->getCreature(perso.classe) ,perso.nom, QSize(m_lcase, m_hcase), perso.posmap, this,m_lmap);
    /*if(perso.nom == m_personnage->getNom())
        connect(m_persos[perso.nom], SIGNAL(estSurTranspo(QPoint)), this, SLOT(VaChangerDeMap(QPoint)));*/
}

void GameField::removeEntity(QString const& nom)
{
    delete m_persos[nom];
    m_persos.remove(nom);
}

void GameField::changePos(QString const& qui, int x, int y)
{
    m_persos[qui]->changePos(x,y);
}

void GameField::faitRecettes()
{
    emit faitRecette(m_nomMetier);
}
