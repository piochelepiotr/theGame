#include "additionalWindows/caracteristiques.h"
#include "ui_caracteristiques.h"
#include <QFile>
#include <QTextStream>

Caracteristiques::Caracteristiques(QWidget *parent, Personnage *perso, Reseau *reseau, Donnees_editeur *donnees_editeur):
    QDialog(parent),
    ui(new Ui::Caracteristiques)
{
    setWindowTitle(trUtf8("Caractéristiques"));
    m_donnees_editeur = donnees_editeur;
    m_reseau = reseau;
    m_perso = perso;
    ui->setupUi(this);

    m_inventaire = new Inventaire(m_perso, m_donnees_editeur->ressources);
    ui->lay_inventaire->addWidget(m_inventaire);

    ui->pod->setMaximum(m_perso->getPodsMax());
    ui->pod->setValue(m_perso->getPods());
    ui->pod->setFormat("%v / %m");
    ui->nom->setText(m_perso->getNom());
    ui->classe_lvl->setText(m_perso->getClasse()+", niveau "+QString::number(m_perso->getNiveau()));
    ui->barre_xp->setMaximum(Personnage::xpDeNiveau(perso->getNiveau()+1));
    ui->barre_xp->setMinimum(Personnage::xpDeNiveau(perso->getNiveau()));
    ui->barre_xp->setValue(perso->getXp());
    ui->barre_xp->setFormat("%v / %m");

    m_description_sort = new Description_sort();
    ui->attaque->layout()->addWidget(m_description_sort);

    caracteristiques();
    competences();

    ui->descr_effet->setReadOnly(true);
    ui->descr_effet->setReadOnly(true);


    ui->argent->setText(QString::number(perso->getArgent()));

    QVector<Eqips>equiped;
    QVector<Eqips>equipeg;

    Eqips equip;
    equip.nbr = 0;
    equip.equipement = 0;

    if(m_perso->coiffe())
    {
        equip.equipement = perso->coiffe();
        equip.nbr = 1;
    }
    else
    {
        equip.equipement = 0;
        equip.nbr = 0;
    }
    equiped.push_back(equip);


    if(m_perso->cape())
    {
        equip.equipement = perso->cape();
        equip.nbr = 1;
    }
    else
    {
        equip.equipement = 0;
        equip.nbr = 0;
    }
    equiped.push_back(equip);

    if(m_perso->anog())
    {
        equip.equipement = perso->anog();
        equip.nbr = 1;
    }
    else
    {
        equip.equipement = 0;
        equip.nbr = 0;
    }
    equiped.push_back(equip);

    if(m_perso->bottes())
    {
        equip.equipement = perso->bottes();
        equip.nbr = 1;
    }
    else
    {
        equip.equipement = 0;
        equip.nbr = 0;
    }
    equiped.push_back(equip);

    if(m_perso->arme())
    {
        equip.equipement = perso->arme()->getEquipement();
        equip.nbr = 1;
    }
    else
    {
        equip.equipement = 0;
        equip.nbr = 0;
    }
    equipeg.push_back(equip);

    if(m_perso->amulette())
    {
        equip.equipement = perso->amulette();
        equip.nbr = 1;
    }
    else
    {
        equip.equipement = 0;
        equip.nbr = 0;
    }
    equipeg.push_back(equip);

    if(m_perso->anod())
    {
        equip.equipement = perso->anod();
        equip.nbr = 1;
    }
    else
    {
        equip.equipement = 0;
        equip.nbr = 0;
    }
    equipeg.push_back(equip);

    if(m_perso->ceinture())
    {
        equip.equipement = perso->ceinture();
        equip.nbr = 1;
    }
    else
    {
        equip.equipement = 0;
        equip.nbr = 0;
    }
    equipeg.push_back(equip);



    m_equipementsG = new Items(equipeg, 1, 4, m_donnees_editeur->ressources);
    m_equipementsD = new Items(equiped, 1, 4, m_donnees_editeur->ressources);

    if(m_perso->arme())
    {
        m_equipementsG->setItemArme(0,m_perso->arme());
    }

    ui->objets_gauche->setLayout(m_equipementsG);
    ui->objets_droite->setLayout(m_equipementsD);

    connect(m_inventaire, SIGNAL(s_ressclique(Ressource*)), this, SLOT(decriRess(Ressource*)));
    connect(m_inventaire, SIGNAL(s_equipclique(Equipement*)), this, SLOT(decriObj(Equipement*)));
    connect(m_inventaire, SIGNAL(s_armeclique(Arme*)), this, SLOT(decriArme(Arme*)));

    connect(m_inventaire, SIGNAL(s_equipdblclique(int)), this, SLOT(metEquip(int)));
    connect(m_inventaire, SIGNAL(s_armedblclique(int)), this, SLOT(metArme(int)));

    connect(m_equipementsD, SIGNAL(ressclique(int)), this, SLOT(cotedclique(int)));
    connect(m_equipementsG, SIGNAL(ressclique(int)), this, SLOT(cotegclique(int)));
    connect(m_equipementsD, SIGNAL(ressdbclique(int)), this, SLOT(coteddbclique(int)));
    connect(m_equipementsG, SIGNAL(ressdbclique(int)), this, SLOT(cotegdbclique(int)));

    ui->widgetSort->setLayout(new LayoutDescriptionSort(m_perso));

    this->exec();
}

Caracteristiques::~Caracteristiques()
{
    delete ui;
}

void Caracteristiques::decriRess(Ressource *ress)
{
    ui->description->setPlainText(trUtf8("Catégorie : ") + ress->categorie() + '\n' + ress->description());
    ui->imageobjet->setPixmap(ress->imageg());
    ui->nomobjet->setText(ress->nom());
    ui->podobjet->setText(trUtf8("pods : ")+QString::number(ress->pods()));
    ui->nivobjet->setText(trUtf8("niveau : ")+QString::number(ress->niveau()));
    ui->descr_effet->setText("");
    m_description_sort->setSort(0);
}


void Caracteristiques::decriObj(Equipement *obj)
{
    Ressource *ress = obj->getRessource();
    decriRess(ress);
    ui->descr_effet->setText(Equipement::descr_effet(obj));
}

void Caracteristiques::decriArme(Arme *arme)
{
    decriObj(arme->getEquipement());
    m_description_sort->setSort(m_donnees_editeur->ressources->getArme(arme->getEquipement()->getRessource()->nom())->getSort());
}

void Caracteristiques::cotedclique(int num)
{
    if(num == 0)
        decriObj(m_perso->coiffe());
    else if(num == 1)
        decriObj(m_perso->cape());
    else if(num == 2)
        decriObj(m_perso->anog());
    else if(num == 3)
        decriObj(m_perso->bottes());
}

void Caracteristiques::cotegclique(int num)
{
    if(num == 0)
        decriArme(m_perso->arme());
    else if(num == 1)
        decriObj(m_perso->amulette());
    else if(num == 2)
        decriObj(m_perso->anod());
    else if(num == 3)
        decriObj(m_perso->ceinture());
}

void Caracteristiques::coteddbclique(int num)
{
    int place = m_perso->desequipe(num);
    m_inventaire->ajouteEquip(m_perso->equipement_num(place), 1, place);
    m_equipementsD->setItemEquipement(num, 0);
    m_reseau->envoyer("eeq/"+QString::number(num));
    caracteristiques();
}

void Caracteristiques::cotegdbclique(int num)
{
    if(num == 0)
    {
        int place = m_perso->desequipeArme();
        m_inventaire->ajouteArme(m_perso->armenum(place), 1, place);
        m_equipementsG->setItemArme(0, 0);
        m_reseau->envoyer("ear");
    }
    else
    {
        int place = m_perso->desequipe(num+4);
        m_inventaire->ajouteEquip(m_perso->equipement_num(place), 1, place);
        m_equipementsG->setItemEquipement(num, 0);

        m_reseau->envoyer("eeq/"+QString::number(num+4));
    }
    caracteristiques();
}

void Caracteristiques::metEquip(int num)
{
    //QMessageBox::information(this, "rien", QString::number(num));
    if(m_perso->peutequipe(m_perso->equipement_num(num)))
    {
        QString categorie = m_perso->equipement_num(num)->getRessource()->categorie();
        bool anog;
        //QMessageBox::information(this, "avant place", categorie);
        int place = m_perso->equipeEquipement(num,categorie, &anog);
        //QMessageBox::information(this, "apres place", QString::number(place));
        m_inventaire->enleveEquip(num, 1);
        //QMessageBox::information(this, "apres inventaire", "");
        if(place != -2)
        {
            m_inventaire->ajouteEquip(m_perso->equipement_num(place), 1, place);
            //QMessageBox::information(this, "apres ajoute equipe", "");
        }
        if(categorie == "coiffe")
            m_equipementsD->setItemEquipement(0, m_perso->coiffe());
        else if(categorie == "cape")
            m_equipementsD->setItemEquipement(1, m_perso->cape());
        else if(categorie == "amulette")
            m_equipementsG->setItemEquipement(1, m_perso->amulette());
        else if(categorie == "ceinture")
            m_equipementsG->setItemEquipement(3, m_perso->ceinture());
        else if(categorie == "bottes")
            m_equipementsD->setItemEquipement(3, m_perso->bottes());
        else if(anog)
            m_equipementsD->setItemEquipement(2, m_perso->anog());
        else
            m_equipementsG->setItemEquipement(2, m_perso->anod());
        //QMessageBox::information(this, "apres set item", QString::number(num));

        m_reseau->envoyer("eqi/"+QString::number(num)+"/"+categorie);
        caracteristiques();
    }
}


void Caracteristiques::metArme(int num)
{
    qDebug() << "met arme";
    if(m_perso->peutequipe(m_perso->armenum(num)->getEquipement()))
    {
        qDebug() << "ok !! on peut y aller";
        int place = m_perso->equipeArme(num);
        m_inventaire->enleveArme(num, 1);
        if(place != -2)
        {
            //QMessageBox::information(this,"titre","la place est "+QString::number(place));
            m_inventaire->ajouteArme(m_perso->armenum(place), 1, place);
        }
        m_equipementsG->setItemArme(0, m_perso->arme());
        m_reseau->envoyer("eqa/"+QString::number(num));

        caracteristiques();
    }
}


void Caracteristiques::caracteristiques()
{
    ui->tab_cara->setItem(0,0, new QTableWidgetItem(QString::number(m_perso->getBaseForce())));
    ui->tab_cara->setItem(1,0, new QTableWidgetItem(QString::number(m_perso->getBasePC())));
    ui->tab_cara->setItem(2,0, new QTableWidgetItem(QString::number(m_perso->getBaseVie())));

    ui->tab_cara->setItem(0,1, new QTableWidgetItem(QString::number(m_perso->getBonusForce())));
    ui->tab_cara->setItem(1,1, new QTableWidgetItem(QString::number(m_perso->getBonusPC())));
    ui->tab_cara->setItem(2,1, new QTableWidgetItem(QString::number(m_perso->getBonusVie())));

    ui->tab_cara->setItem(0,2, new QTableWidgetItem(QString::number(m_perso->getTotalForce())));
    ui->tab_cara->setItem(1,2, new QTableWidgetItem(QString::number(m_perso->getTotalPC())));
    ui->tab_cara->setItem(2,2, new QTableWidgetItem(QString::number(m_perso->getTotalVie())));
}

void Caracteristiques::competences()
{
    QStringList metiers = m_perso->getMetiers();
    QLabel *label;
    QWidget *widget;
    QVBoxLayout *layout;
    QHBoxLayout *lay_niveau_xp;
    QProgressBar *xp;
    QTabWidget *onglets;
    QWidget *onglet_ressources;
    QWidget *onglet_recettes;
    QVBoxLayout *lay_ressources;
    QTableWidget *ressources;
    QVector<qint16>objets;
    QHBoxLayout *lay_ressource_collectee;
    QWidget *ressource_collectee;
    QLabel *texte_ressource_collectee;
    int lvl;
    qDebug() << metiers.size();
    for(int i = 0; i < metiers.size(); i++)
    {
        lvl = m_perso->getMetier(metiers[i])->getLvl();
        layout = new QVBoxLayout;
        lay_niveau_xp = new QHBoxLayout;
        widget = new QWidget;
        label = new QLabel(trUtf8("niveau ")+QString::number(lvl));
        xp = new QProgressBar;
        xp->setMinimum(xpMinlvl(lvl));
        xp->setMaximum(xpMinlvl(lvl+1));
        xp->setValue(m_perso->getMetier(metiers[i])->getXp());
        xp->setFormat("%v / "+QString::number(xpMinlvl(lvl+1)));
        lay_niveau_xp->addWidget(label);
        lay_niveau_xp->addWidget(xp);


        onglets = new QTabWidget;
        onglet_ressources = new QWidget;
        onglet_recettes = new QWidget;


        //debut ressources
        lay_ressources = new QVBoxLayout;
        ressources = new QTableWidget(0,5);
        ressources->horizontalHeader()->hide();
        ressources->verticalHeader()->hide();
        ressources->setColumnWidth(0,100);
        ressources->setColumnWidth(1,100);
        ressources->setColumnWidth(2,100);
        ressources->setColumnWidth(3,100);
        ressources->setColumnWidth(4,150);
        objets = m_perso->getMetier(metiers[i])->getMetierBase()->ressources_coupables(lvl);

        for(int j = 0; j < objets.size(); j++)
        {
            lay_ressource_collectee = new QHBoxLayout;
            ressource_collectee = new QWidget;
            texte_ressource_collectee = new QLabel(QString::number(m_perso->getMetier(metiers[i])->minRessources(objets[j]))+trUtf8(" à ")+QString::number(m_perso->getMetier(metiers[i])->maxRessources(objets[j]))+" ");
            lay_ressource_collectee->addWidget(texte_ressource_collectee);
            lay_ressource_collectee->addWidget(item(m_donnees_editeur->ressources, m_perso->getMetier(metiers[i])->getMetierBase()->objet_coupable(objets[j])->getRessource()));
            ressource_collectee->setLayout(lay_ressource_collectee);

            ressources->insertRow(j);
            ressources->setItem(j,0,new QTableWidgetItem(m_perso->getMetier(metiers[i])->getMetierBase()->verbe()));
            ressources->setItem(j,1,new QTableWidgetItem(m_donnees_editeur->decor->objet(objets[j])->nom()));
            ressources->setItem(j,2,new QTableWidgetItem(m_perso->getMetier(metiers[i])->getMetierBase()->arme()));
            ressources->setItem(j,3,new QTableWidgetItem(QString::number(m_perso->getMetier(metiers[i])->nbrCoups())+trUtf8(" coups")));
            ressources->setCellWidget(j,4,ressource_collectee);

            ressources->setRowHeight(j,50);
        }
        lay_ressources->addWidget(ressources);

        Recettes *recettes = new Recettes(m_perso->getMetier(metiers[i]), m_donnees_editeur->ressources);

        onglet_ressources->setLayout(lay_ressources);
        onglet_recettes->setLayout(recettes);
        onglets->addTab(onglet_ressources,trUtf8("Ressources"));
        onglets->addTab(onglet_recettes,trUtf8("Recettes"));

        layout->addLayout(lay_niveau_xp);
        layout->addWidget(onglets);
        widget->setLayout(layout);
        ui->tab_metiers->addTab(widget, metiers[i]);
    }
}

