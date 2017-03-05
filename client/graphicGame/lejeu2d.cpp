#include "graphicGame/lejeu2d.h"

/////////////////////////////////////////////////////////////////

Jeu2d::Jeu2d(QSize const& size, Personnage *pers, QTcpSocket *sock, Donnees_editeur *donneesediteur)
{
    m_sort_a_utiliser = 0;
    m_combat = 0;
    m_dataMap = 0;
    m_nomMetier = "";
    m_combatOuPas = HorsCombat;
    m_donnees_editeur = donneesediteur;
    m_socket = sock;
    m_personnage = pers;
    m_graphique = new Jeu_graphique(size, pers->getNom(), this, donneesediteur);
    charge(pers->getPosX(), pers->getPosY(), pers->getPosZ());
    InfoPerVis inf;
    inf.classe = pers->getClasse();
    inf.nom = pers->getNom();
    inf.posmap = pers->getPosMap();
    ajouteUnPerso(inf);
    redi(size);
}

Jeu2d::~Jeu2d()
{

}

void Jeu2d::redi(QSize const& nouvelle)
{
    m_graphique->redi(nouvelle, m_dataMap);
}

void Jeu2d::nouvelle()
{
    m_dataMap->vide();
    m_graphique->nouvelle();
}

void Jeu2d::setCasePleine(int i, int j, int value)
{
    m_dataMap->setCasePleine(i,j,value);
    m_graphique->setCasepleine(i,j,value);
}

bool Jeu2d::charge(int cooX, int cooY, int cooZ)
{
    if(DataMap::exist(cooX,cooY,cooZ))
    {
        if(m_dataMap)
        {
            delete m_dataMap;
            m_dataMap = 0;
        }
        m_dataMap = new DataMap(m_donnees_editeur,cooX,cooY,cooZ);
        m_graphique->charge(m_dataMap);
        return true;
    }
    return false;
}

void Jeu2d::caseEgale(int i, int j, Objet *objet, int fond)
{
    m_dataMap->setObjet(i,j,fond,objet);
    m_graphique->caseEgale(i,j,objet,fond);
}




void Jeu2d::VaChangerDeMap(const QPoint &p)
{
    /*Transporteur ancien = m_dataMap->transporteur(p);
    changeDeMap(ancien.getMapX(), ancien.getMapY(), ancien.getMapZ(), ancien.getNomArr());*/
}

void Jeu2d::changeDeMap(int mapx, int mapy, int mapz, const QString &transpo)
{
    /*charge(mapx,mapy, mapz);
    int largX = 0, largY = 0;
    for(QMap<QPoint, Transporteur>::iterator i = m_lestranspo.begin(); i != m_lestranspo.end(); i++)
    {
        if(i.value().getNom() == transpo)
        {
            largX = i.value().getLargageX();
            largY = i.value().getLargageY();
            i = m_lestranspo.end()-1;
        }
    }
    m_graphique->changeDeMap(largX, largY);

    QString mess = "cdm/"+QString::number(mapx)+"/"+QString::number(mapy)+"/"+QString::number(mapz)+"/"+QString::number(largX)+"/"+QString::number(largY);
    envoyerM(m_socket, mess);*/

}

void Jeu2d::changeDeMap(int mapx, int mapy, int mapz, int coox,int cooy)
{
    charge(mapx,mapy, mapz);
    m_graphique->changeDeMap(coox, cooy);
    QString mess = "cdm/"+QString::number(mapx)+"/"+QString::number(mapy)+"/"+QString::number(mapz)+"/"+QString::number(coox)+"/"+QString::number(cooy);
    envoyerM(m_socket, mess);
}

void Jeu2d::imagesuivante()
{
    m_graphique->imagesuivante();
}


void Jeu2d::ajouteTranspo(QPoint const& pos, Transporteur const& transpo)
{
    /*m_lestranspo[pos] = transpo;
    m_graphique->ajouteTranspo(pos);*/
}

void Jeu2d::ajouteUnPerso(InfoPerVis perso)
{
    m_graphique->ajouteUnPerso(perso);
}

void Jeu2d::supprimeUnPerso(QString const& nom)
{
    m_graphique->supprimeUnPerso(nom);
}

Donnees_editeur *Jeu2d::donneesediteur()
{
    return m_graphique->donneesediteur();
}

AfficheJoueur *Jeu2d::getJoueur(QString const& nom)
{
    return m_graphique->getJoueur(nom);
}

Jeu_graphique *Jeu2d::graphique() const
{
    return m_graphique;
}

void Jeu2d::cliqueGauche(int x, int y)
{
    if(m_combatOuPas == HorsCombat)
    {
        QPoint p = m_graphique->fleche();
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

                if(m_graphique->direction_fleche() == O)
                {
                    m_maparry--;
                    m_cooarry += NBR_CASES_H-CASESCACHEESY*2-1;
                }
                else if(m_graphique->direction_fleche() == B)
                {
                    m_maparry++;
                    m_cooarry -= NBR_CASES_H-CASESCACHEESY*2-1;
                }
                else if(m_graphique->direction_fleche() == G)
                {
                    m_maparrx--;
                    m_cooarrx = NBR_CASES_L-CASESCACHEESX-1;
                }
                else
                {
                    m_maparrx++;
                    m_cooarrx = CASESCACHEESX;
                }
                m_graphique->deplace(m_personnage->getNom(), chem, Actions_personnage::ChangeDeMap);
            }
            else
            {
                m_graphique->deplace(m_personnage->getNom(), chem);
            }
            return;
        }
        p = m_graphique->getJeu()->dataMap()->ccase(x, y,m_graphique->getlmap(),m_graphique->gethmap(),m_graphique->getlcase(),m_graphique->gethcase(),true);
        if(p.x() != -1)//gere le deplacement sans changer de map
        {
            chem = m_dataMap->calculchemin(getJoueur(m_personnage->getNom())->posALaFin(), p);
            if(!chem.isEmpty())
            {
                m_graphique->deplace(m_personnage->getNom(), chem);
                envoyerM(m_socket, "dep/"+m_personnage->getNom()+'*'+QString::number(p.x()) +'*'+QString::number(p.y()));
            }
        }
    }
    else if(m_combatOuPas == EnPlacement)
    {
        QPoint p = m_graphique->getJeu()->dataMap()->ccase(x, y,m_graphique->getlmap(),m_graphique->gethmap(),m_graphique->getlcase(),m_graphique->gethcase(),true);
        if(m_dataMap->estCaseDeDepart(p.x(),p.y(),m_personnage->equipe()))
        {
            if(!m_graphique->contientJoueur(p))
            {
                envoyerM(m_socket, "combat/changePosDep/"+QString::number(p.x())+"*"+QString::number(p.y()));
            }
        }
    }
    else if(m_combatOuPas == EnCombat && m_personnage->monTour() && m_graphique->getJoueur(m_personnage->getNom())->isImobile())
    {
        if(!m_sort_a_utiliser)
        {
            QPoint arrivee = m_graphique->getJeu()->dataMap()->ccase(x, y,m_graphique->getlmap(),m_graphique->gethmap(),m_graphique->getlcase(),m_graphique->gethcase(),true);
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
            QPoint p = m_graphique->posCaseVisee();
            m_graphique->stopUtiliseSort();
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

void Jeu2d::utileClique(QPoint const& pos)
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
                        m_graphique->deplace(m_personnage->getNom(), chemin, Actions_personnage::Recettes);
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
                        m_graphique->deplace(m_personnage->getNom(), chemin, Actions_personnage::Recolter);
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

void Jeu2d::changeMap()
{
    changeDeMap(m_maparrx, m_maparry, m_maparrz, m_cooarrx, m_cooarry);
}

void Jeu2d::fait_recettes()
{
    emit faitRecette(m_nomMetier);
}

void Jeu2d::doit_recolter()
{
    int orientation = m_orientation;
    m_graphique->recolte(m_personnage->getNom(), m_personnage->getMetier(m_nomMetier)->getMetierBase()->verbe(), m_orientation, m_personnage->getMetier(m_nomMetier)->nbrCoups(), Actions_personnage::ARecolter);
    envoyerM(m_socket, "cut/"+m_personnage->getNom()+'*'+m_personnage->getMetier(m_nomMetier)->getMetierBase()->verbe()+'*'+QString::number(orientation)+'*'+QString::number(m_personnage->getMetier(m_nomMetier)->nbrCoups()));
}

void Jeu2d::ressourceRecoltee(QPoint pos)
{
    caseEgale(pos.x(), pos.y(), m_donnees_editeur->metiers->getSoucheParObjet(m_dataMap->objet(pos.x(),pos.y(),2)->numero()), 2);
}

void Jeu2d::ressource_repousse(int posx, int posy)
{
    caseEgale(posx, posy, m_donnees_editeur->metiers->getObjetParSouche(m_dataMap->objet(posx,posy,2)->numero()), 2);
}

void Jeu2d::a_coupe()
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

Dir orientation_vers_objet(QPoint const& pos, QPoint const& pos_obj)
{
    if(pos.y() == pos_obj.y()+2)
        return O;
    else if(pos.y() == pos_obj.y()-2)
        return B;
    else if(pos.y() == pos_obj.y() && pos.x() == pos_obj.x()+1)
        return G;
    else if(pos.y() == pos_obj.y() && pos.x() == pos_obj.x()-1)
        return D;
    else if(pos.y()%2==0)
    {
        if(pos.x() == pos_obj.x() && pos.y() == pos_obj.y()+1)
            return OD;
        else if(pos.x() == pos_obj.x() && pos.y() == pos_obj.y()-1)
            return BD;
        else if(pos.x() == pos_obj.x()+1 && pos.y() == pos_obj.y()+1)
            return OG;
        else
            return BG;
    }
    else
    {
        if(pos.x() == pos_obj.x() && pos.y() == pos_obj.y()+1)
            return OG;
        else if(pos.x() == pos_obj.x() && pos.y() == pos_obj.y()-1)
            return BG;
        else if(pos.x() == pos_obj.x()-1 && pos.y() == pos_obj.y()+1)
            return OD;
        else
            return BD;
    }
}

void Jeu2d::infos_map(QString infos)
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

void Jeu2d::setMonTour(bool monTour)
{
    m_graphique->effaceChemin();
    m_personnage->nouveau_tour();
    m_personnage->setTour(monTour);
    m_sort_a_utiliser = 0;
    emit changePC(m_personnage->getPCCombat());
}

void Jeu2d::veut_utiliserSort(Sort *sort)
{
    qDebug() << "nom sort : " << sort->nom();
    m_graphique->effaceChemin();
    m_sort_a_utiliser = sort;
    m_graphique->utiliseSort(sort);
}


void Jeu2d::portee(bool cases_ateignables[NBR_CASES_L] [NBR_CASES_H], int xdep, int ydep, int portee_min, int portee_max)
{
    m_dataMap->calculPortee(cases_ateignables, xdep, ydep, portee_min,portee_max);
}

void Jeu2d::updateObjet(QPoint pos)
{
    m_graphique->updateObjet(pos.x(),pos.y(),m_dataMap->objet(pos.x(),pos.y(),2));
}

void Jeu2d::phasePlacement(Combat *combat,int equipe)
{
    m_personnage->setEquipe(equipe);
    m_combatOuPas = EnPlacement;
    m_graphique->afficheCasesCombat(m_dataMap);
    setMonTour(false);
}

void Jeu2d::phaseCombat()
{
    m_combatOuPas = EnCombat;
    m_graphique->masqueCaseCombat();
    m_graphique->marche_pas(m_dataMap);
}

void Jeu2d::phaseFinCombat()
{
    if(m_combatOuPas == EnPlacement)
        m_graphique->masqueCaseCombat();
    m_combatOuPas = HorsCombat;
    m_combat = 0;
    m_graphique->effaceChemin();
    //m_graphique->cachePortee();
}

void Jeu2d::deplaceCombat(const QString &qui, const QPoint &ou)
{
    QPoint dep = getJoueur(qui)->posALaFin();
    graphique()->deplace(qui, m_dataMap->calculcheminCombat(dep,ou, 1000));
    m_dataMap->setCasePleineCombat(dep.x(), dep.y(), 0);
    m_dataMap->setCasePleineCombat(ou.x(), ou.y(), 2);
}

void Jeu2d::clearMap()
{
    //QList<QPoint>posCollectedRessources = m_dataMap->posC
}

