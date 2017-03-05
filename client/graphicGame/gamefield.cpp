#include "gamefield.h"

GameField::GameField(const QSize &size, Personnage *pers, QTcpSocket *sock, Donnees_editeur *donnees_editeur) : GameScene(size,0,donnees_editeur)
{
    m_sort_a_utiliser = 0;
    m_combat = 0;
    m_nomMetier = "";
    m_combatOuPas = HorsCombat;
    m_donnees_editeur = donneesediteur;
    m_socket = sock;
    m_personnage = pers;
    m_graphique = new GameField(size, pers->getNom(), this, donneesediteur);
    charge(pers->getPosX(), pers->getPosY(), pers->getPosZ());
    InfoPerVis inf;
    inf.classe = pers->getClasse();
    inf.nom = pers->getNom();
    inf.posmap = pers->getPosMap();
    m_fleche = addPixmap(QPixmap());
    m_fleche->setZValue(4+NBR_CASES_H);
    m_posFleche = QPoint(-1,-1);
    ajouteUnPerso(inf);
    redi(size);
}

GameField::~GameField()
{
    for(QMap<QString, AfficheJoueur*>::iterator i = m_persos.begin(); i != m_persos.end(); i++)
    {
        delete i.value();
    }
}

void GameField::redi(QSize const& nouvelle)
{
    GameScene::redi(nouvelle);
    for(QMap<QString,AfficheJoueur*>::iterator i = m_persos.begin(); i != m_persos.end(); i++)
    {
        i.value()->redi(m_lcase, m_hcase);
    }
}

void GameField::cliqueGauche(int x, int y)
{
    if(m_combatOuPas == HorsCombat)
    {
        QPoint p = fleche();
        QQueue<Dir> chem;
        if(p.x() != -1)//gere la fleche et le changement de map
        {
            chem = m_dataMap->calculchemin(getJoueur(m_personnage->getNom())->posALaFin(), p);
            if(!chem.isEmpty())
                envoyerM(m_socket, "dep/"+m_personnage->getNom()+'*'+QString::number(p.x())+QString::number(p.y()));
            if(!chem.isEmpty() || p == getJoueur(m_personnage->getNom())->posALaFin())
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
                deplace(m_personnage->getNom(), chem, Actions_personnage::ChangeDeMap);
            }
            else
            {
                deplace(m_personnage->getNom(), chem);
            }
            return;
        }
        p = getJeu()->dataMap()->ccase(x, y,getlmap(),gethmap(),getlcase(),gethcase(),true);
        if(p.x() != -1)//gere le deplacement sans changer de map
        {
            chem = m_dataMap->calculchemin(getJoueur(m_personnage->getNom())->posALaFin(), p);
            if(!chem.isEmpty())
            {
                deplace(m_personnage->getNom(), chem);
                envoyerM(m_socket, "dep/"+m_personnage->getNom()+'*'+QString::number(p.x()) +'*'+QString::number(p.y()));
            }
        }
    }
    else if(m_combatOuPas == EnPlacement)
    {
        QPoint p = getJeu()->dataMap()->ccase(x, y,getlmap(),gethmap(),getlcase(),gethcase(),true);
        if(m_dataMap->estCaseDeDepart(p.x(),p.y(),m_personnage->equipe()))
        {
            if(!contientJoueur(p))
            {
                envoyerM(m_socket, "combat/changePosDep/"+QString::number(p.x())+"*"+QString::number(p.y()));
            }
        }
    }
    else if(m_combatOuPas == EnCombat && m_personnage->monTour() && getJoueur(m_personnage->getNom())->isImobile())
    {
        if(!m_sort_a_utiliser)
        {
            QPoint arrivee = getJeu()->dataMap()->ccase(x, y,getlmap(),gethmap(),getlcase(),gethcase(),true);
            QQueue<Dir> chem = m_dataMap->calculcheminCombat(getJoueur(m_personnage->getNom())->posALaFin(), arrivee, m_personnage->getPCCombat());
            if(!chem.isEmpty())
            {
                m_personnage->use_pc(chem.size());
                emit changePC(m_personnage->getPCCombat());
                envoyerM(m_socket, "combat/dep/"+QString::number(arrivee.x())+"*"+QString::number(arrivee.y()));
            }
        }
        else
        {
            QPoint p = posCaseVisee();
            stopUtiliseSort();
            if(p.x() != -1)
            {
                m_personnage->use_pc(m_sort_a_utiliser->points_combat());
                emit changePC(m_personnage->getPCCombat());
                envoyerM(m_socket,"combat/attaque/"+m_sort_a_utiliser->nom()+"/"+QString::number(p.x())+"/"+QString::number(p.y()));
            }
            m_sort_a_utiliser = 0;
        }
    }
}

void GameField::setMonTour(bool monTour)
{
    effaceChemin();
    m_personnage->nouveau_tour();
    m_personnage->setTour(monTour);
    m_sort_a_utiliser = 0;
    emit changePC(m_personnage->getPCCombat());
}

void GameField::veut_utiliserSort(Sort *sort)
{
    qDebug() << "nom sort : " << sort->nom();
    effaceChemin();
    m_sort_a_utiliser = sort;
    utiliseSort(sort);
}

void GameField::phasePlacement(Combat *combat,int equipe)
{
    m_personnage->setEquipe(equipe);
    m_combatOuPas = EnPlacement;
    afficheCasesCombat(m_dataMap);
    setMonTour(false);
}

void GameField::phaseCombat()
{
    m_combatOuPas = EnCombat;
    masqueCaseCombat();
    marche_pas(m_dataMap);
}

void GameField::phaseFinCombat()
{
    if(m_combatOuPas == EnPlacement)
        masqueCaseCombat();
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
}

void GameField::ajouteUnPerso(InfoPerVis perso)
{
    ajouteUnPerso(perso);
}

void GameField::supprimeUnPerso(QString const& nom)
{
    supprimeUnPerso(nom);
}

AfficheJoueur *GameField::getJoueur(QString const& nom)
{
    return getJoueur(nom);
}

void GameField::utileClique(QPoint const& pos)
{
    if(m_combatOuPas == HorsCombat)
    {
        qDebug() << "clique utile !";
        Objet *obj = m_dataMap->objet(pos.x(),pos.y(),2);
        if(obj->categorie() == "pnj")
        {
            qDebug() << "pnj";
            emit pnjclique(obj->numero(),pos);
        }
        else if(obj->categorie() == "forge")
        {
            Metier_Base *metier = m_donnees_editeur->metiers->forge_to_metier(obj);
            if(metier)
            {
                if(!m_personnage->arme())
                {
                    emit pourChat(QObject::trUtf8("Vous n'avez pas l'arme appropriée pour exercer ce métier : ")+metier->arme());
                }
                else if(m_personnage->arme()->getEquipement()->getRessource()->categorie() == metier->arme())
                {
                    m_nomMetier = metier->nom();//pour les recettes
                    QPoint p;
                    QQueue<Dir> chemin = m_dataMap->calculcheminJusquaLObjet(getJoueur(m_personnage->getNom())->posALaFin() , pos, &p);
                    if(!chemin.isEmpty())
                    {
                        deplace(m_personnage->getNom(), chemin, Actions_personnage::Recettes);
                        envoyerM(m_socket, "dep/"+m_personnage->getNom()+'*'+QString::number(p.x()) +'*'+QString::number(p.y()));
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
            Metier_Base *metier = m_donnees_editeur->metiers->objet_coupable_to_metier(obj);
            if(metier)
            {
                if(!m_personnage->arme())
                {
                    emit pourChat(QObject::trUtf8("Vous ne pouvez pas pas récolter cette ressource"));
                }
                else if(m_personnage->arme()->getEquipement()->getRessource()->categorie() == metier->arme() && m_personnage->getMetier(metier->nom()) != 0 && metier->objet_coupable(obj->numero())->lvl() <= m_personnage->getMetier(metier->nom())->getLvl())
                {
                    QPoint p;
                    QQueue<Dir> chemin = m_dataMap->calculcheminJusquaLObjet(getJoueur(m_personnage->getNom())->posALaFin() , pos, &p);
                    if(!chemin.isEmpty())
                    {
                        deplace(m_personnage->getNom(), chemin, Actions_personnage::Recolter);
                        m_orientation = orientation_vers_objet(p, pos);
                        envoyerM(m_socket, "dep/"+m_personnage->getNom()+'*'+QString::number(p.x()) +'*'+QString::number(p.y()));
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
    recolte(m_personnage->getNom(), m_personnage->getMetier(m_nomMetier)->getMetierBase()->verbe(), m_orientation, m_personnage->getMetier(m_nomMetier)->nbrCoups(), Actions_personnage::ARecolter);
    envoyerM(m_socket, "cut/"+m_personnage->getNom()+'*'+m_personnage->getMetier(m_nomMetier)->getMetierBase()->verbe()+'*'+QString::number(orientation)+'*'+QString::number(m_personnage->getMetier(m_nomMetier)->nbrCoups()));
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
    Metier *metier = m_personnage->getMetier(m_nomMetier);
    int xp = xpCoupeRessource(metier->getMetierBase()->objet_coupable(numobj)->lvl());
    int nombre_ressources = metier->nombre_ressources(numobj);
    metier->gagneXp(xp);
    QString ajoutees = m_personnage->gagneRessources(metier->getMetierBase()->objet_coupable(numobj)->getRessource(), nombre_ressources);
    ressourceRecoltee(m_pos_ressource);
    envoyerM(m_socket, "cop/"+QString::number(m_pos_ressource.x())+'*'+QString::number(m_pos_ressource.y())+'/'+metier->getNomMetier()+'/'+QString::number(xp)+'/'+ajoutees);
}

void GameField::infos_map(QString infos)
{
    QString unJoueur;
    InfoPerVis perso;
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
        ajouteUnPerso(perso);
        infos = infos.section('/', 1);
    }
}

void GameField::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    int x = mouseEvent->scenePos().x(), y = mouseEvent->scenePos().y();
    if(m_parent->phase() == HorsCombat)
    {
        for(QMap<QString,AfficheJoueur*>::iterator it = m_persos.begin();it != m_persos.end(); it++)
        {
            if(it.value()->isUnderMouse())
                it.value()->aide();
            else
                it.value()->desaide();
        }
        m_fleche->setVisible(false);
        m_posFleche.setX(-1);
        m_posFleche.setY(-1);
        if(x < m_mlcase)
        {
            m_posFleche = m_parent->dataMap()->case_gauche(m_parent->dataMap()->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true));
            if(m_posFleche.x() != -1)
            {
                m_directionChangeMap = G;
                m_fleche->setVisible(true);
                m_fleche->setPixmap(QPixmap("../data/interface/flecheg.png").scaled(QSize(50,75)));
                m_fleche->setPos(0, m_parent->dataMap()->cposy(m_posFleche.y(),m_hcase,true)-m_fleche->pixmap().height()/2);
            }
        }
        else if(x > m_lmap-m_mlcase)
        {
            m_posFleche = m_parent->dataMap()->case_droite(m_parent->dataMap()->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true));
            if(m_posFleche.x() != -1)
            {
                m_directionChangeMap = D;
                m_fleche->setVisible(true);
                m_fleche->setPixmap(QPixmap("../data/interface/fleched.png").scaled(QSize(50,75)));
                m_fleche->setPos(m_lmap-m_fleche->pixmap().width(), m_parent->dataMap()->cposy(m_posFleche.y(),m_hcase,true)-m_fleche->pixmap().height()/2);
            }
        }
        else if(y < m_mhcase)
        {
            m_posFleche = m_parent->dataMap()->case_haut(m_parent->dataMap()->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true));
            if(m_posFleche.x() != -1)
            {
                m_directionChangeMap = O;
                m_fleche->setVisible(true);
                m_fleche->setPixmap(QPixmap("../data/interface/flecheo.png").scaled(QSize(75,50)));
                m_fleche->setPos(m_parent->dataMap()->cposx(m_posFleche.x(), m_posFleche.y(),m_lcase,true)-m_fleche->pixmap().width()/2, 0);
            }
        }
        else if(y > (int) ((double) m_hcase * (double) (NBR_CASES_H-CASESCACHEESY*2)/2))
        {
            m_posFleche = m_parent->dataMap()->case_bas(m_parent->dataMap()->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true));
            if(m_posFleche.x() != -1)
            {
                m_directionChangeMap = B;
                m_fleche->setVisible(true);
                m_fleche->setPixmap(QPixmap("../data/interface/flecheb.png").scaled(QSize(75,50)));
                m_fleche->setPos(m_parent->dataMap()->cposx(m_posFleche.x(), m_posFleche.y(),m_lcase,true)-m_fleche->pixmap().width()/2, m_hmap-m_fleche->pixmap().height());
            }
        }
    }
    else if(m_parent->phase() == EnPlacement)
    {
        for(QMap<QString,AfficheJoueur*>::iterator it = m_persos.begin();it != m_persos.end(); it++)
        {
            if(it.value()->isUnderMouse())
                it.value()->aide();
            else
                it.value()->desaide();
        }
    }
    else if(m_parent->phase() == EnCombat)
    {
        if(m_parent->sort())
        {
            m_posCaseVisee = QPoint(-1,-1);
            for(QMap<QString,AfficheJoueur*>::iterator it = m_persos.begin();it != m_persos.end(); it++)
            {
                if(it.value()->isUnderMouse())
                {
                    it.value()->aide();
                    m_posCaseVisee = it.value()->posALaFin();
                }
                else
                    it.value()->desaide();
            }
            if(m_posCaseVisee.x() == -1)
            {
                m_posCaseVisee = m_parent->dataMap()->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true);
            }
            if(caseExiste(m_posCaseVisee.x(),m_posCaseVisee.y()) && m_cases_ateignables[m_posCaseVisee.x()][m_posCaseVisee.y()])
            {
                m_imgCaseVisee->setVisible(true);
                m_imgCaseVisee->setPos(m_parent->dataMap()->cposx(m_posCaseVisee.x(),m_posCaseVisee.y(),m_lcase,true)-m_mlcase, m_parent->dataMap()->cposy(m_posCaseVisee.y(),m_hcase,true)-m_mhcase);
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
                    it.value()->aide();
                else
                    it.value()->desaide();
            }
            if(m_parent->monTour() && m_persos[m_nom]->isImobile())
            {
                QPoint arrivee = m_parent->dataMap()->ccase(x,y,m_lmap,m_hmap,m_lcase,m_hcase,true);
                if(arrivee.x() != -1)
                {
                    if(arrivee != m_ancienne)
                    {
                        effaceChemin();
                        m_ancienne = arrivee;
                        QQueue<Dir> chem = m_parent->dataMap()->calculcheminCombat(getJoueur(m_nom)->posALaFin(), arrivee, m_parent->getPerso()->getPCCombat());
                        if(!chem.isEmpty())
                        {
                            afficheChemin(getJoueur(m_nom)->posALaFin(), chem);
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

void GameField::utiliseSort(Sort *sort)
{
    portee(m_cases_ateignables, m_persos[m_nom]->posALaFin().x(), m_persos[m_nom]->posALaFin().y(),sort->portee_min(), sort->portee_max());
    affichePortee();
}

void GameField::marche_pas(DataMap *dataMap)
{
    for(QMap<QString,AfficheJoueur*>::iterator it = m_persos.begin(); it != m_persos.end(); it++)
    {
        QPoint p = it.value()->posALaFin();
        dataMap->setCasePleineCombat(p.x(),p.y(),2);
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

void GameField::changePos(QString const& qui, int x, int y)
{
    m_persos[qui]->changePos(x,y);
}

void GameField::setVie(QString const& nom, int vie)
{
    m_persos[nom]->setTexteAide(nom+" ("+QString::number(vie)+")");
}

void GameField::meurt(QString const& nom)
{
    m_persos[nom]->setPos(-100,-100);
}
