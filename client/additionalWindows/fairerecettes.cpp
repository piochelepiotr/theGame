#include "additionalWindows/fairerecettes.h"
#include "ui_fairerecettes.h"

Ressource_type::Ressource_type()
{
    setVide();
}

Ressource_type::Ressource_type(Weapon *arme, int nombre)
{
    setArme(arme, nombre);
}

Ressource_type::Ressource_type(Outfit *equipement, int nombre)
{
    setEquipement(equipement, nombre);
}

Ressource_type::Ressource_type(Resource *ressource, int nombre)
{
    setRessource(ressource, nombre);
}

void Ressource_type::setVide()
{
    m_type = AucunType;
}

void Ressource_type::setArme(Weapon *arme, int nombre)
{
    m_nombre = nombre;
    m_type = UneArme;
    m_arme = arme;
}

void Ressource_type::setEquipement(Outfit *equipement, int nombre)
{
    m_nombre = nombre;
    m_type = UnEquipement;
    m_equipement = equipement;
}

void Ressource_type::setRessource(Resource *ressource, int nombre)
{
    m_nombre = nombre;
    m_type = UneRessource;
    m_ressource = ressource;
}

bool Ressource_type::enleve(int nombre)
{
    m_nombre -= nombre;
    if(m_nombre <= 0)
    {
        setVide();
        return true;
    }
    return false;
}


FaireRecettes::FaireRecettes(QWidget *parent, const QString &metier, Data *donnees_editeur, Character *personnage, Reseau *reseau) :
    QDialog(parent),
    ui(new Ui::FaireRecettes)
{
    m_reseau = reseau;
    m_recette = 0;
    ui->setupUi(this);
    m_metier = personnage->getMetier(metier);
    m_personnage = personnage;
    m_donnees_editeur = donnees_editeur;
    m_inventaire = new Inventaire_complet(m_personnage, donnees_editeur->ressources);
    ui->horizontalLayout->addWidget(m_inventaire);
    m_items = new ResourceItems(m_metier->getNbrCases(),METIER_LVL_MAX/METIER_LVLS_1CASEENPLUS+METIER_NBR_CASES_DEPART, m_donnees_editeur->ressources);
    ui->lay_milieu->insertLayout(0, m_items);
    m_objet_cree = new ResourceItem();
    ui->lay_objet_cree->addWidget(m_objet_cree);
    ui->recettes->setLayout(new Recipes(m_metier, m_donnees_editeur->ressources));
    ui->quantite->setMaximum(0);
    setWindowTitle(trUtf8("métier ")+m_metier->getMetierBase()->nom()+trUtf8(" niveau ")+QString::number(m_metier->getLvl()));

    for(int i = 0; i < m_metier->getNbrCases(); i++)
    {
        m_ingredients.push_back(Ressource_type());
    }

    connect(m_inventaire, SIGNAL(s_ressource_double_clique(int)), this, SLOT(double_clique_ressources(int)));
    connect(m_inventaire, SIGNAL(s_equipdblclique(int)), this, SLOT(double_clique_equipements(int)));
    connect(m_inventaire, SIGNAL(s_armedblclique(int)), this, SLOT(double_clique_armes(int)));
    connect(m_items, SIGNAL(ressdbclique(int)), this, SLOT(double_clicue_ingredients(int)));
    connect(ui->lancer, SIGNAL(clicked()), this, SLOT(lance1fois()));
    connect(ui->lancer_tout, SIGNAL(clicked()), this, SLOT(lancexfois()));

    this->exec();
}

void FaireRecettes::double_clique_armes(int num)//on prend une arme de l'inventaire
{
    Weapon *arme = m_inventaire->arme_num(num);
    for(int i = 0; i < m_ingredients.size(); i++)
    {
        if(m_ingredients[i].type() == Ressource_type::UneArme)
        {
            if(m_ingredients[i].arme() == arme)
            {
                m_ingredients[i].ajoute();
                m_items->setItemArme(i,m_ingredients[i].arme(), m_ingredients[i].nombre());
                m_inventaire->enlever_arme(num, 1);
                metAJourRecette();
                return;
            }
        }
    }
    for(int i = 0; i < m_ingredients.size(); i++)
    {
        if(m_ingredients[i].type() == Ressource_type::AucunType)
        {
            m_ingredients[i].setArme(arme);
            m_items->setItemArme(i,m_ingredients[i].arme());
            m_inventaire->enlever_arme(num,1);
            metAJourRecette();
            return;
        }
    }
}

void FaireRecettes::double_clique_equipements(int num)
{
    Outfit *equipement = m_inventaire->equipement_num(num);
    for(int i = 0; i < m_ingredients.size(); i++)
    {
        if(m_ingredients[i].type() == Ressource_type::UnEquipement)
        {
            if(m_ingredients[i].equipement() == equipement)
            {
                m_ingredients[i].ajoute();
                m_items->setItemEquipement(i,m_ingredients[i].equipement(), m_ingredients[i].nombre());
                m_inventaire->enlever_equipement(num,1);
                metAJourRecette();
                return;
            }
        }
    }
    for(int i = 0; i < m_ingredients.size(); i++)
    {
        if(m_ingredients[i].type() == Ressource_type::AucunType)
        {
            m_ingredients[i].setEquipement(equipement);
            m_items->setItemEquipement(i,m_ingredients[i].equipement());
            m_inventaire->enlever_equipement(num,1);
            metAJourRecette();
            return;
        }
    }

}

void FaireRecettes::double_clique_ressources(int num)
{
    Resource *ressource = m_inventaire->ressource_num(num);
    for(int i = 0; i < m_ingredients.size(); i++)
    {
        if(m_ingredients[i].type() == Ressource_type::UneRessource)
        {
            if(m_ingredients[i].ressource() == ressource)
            {
                m_ingredients[i].ajoute();
                m_items->setItemRessource(i,m_ingredients[i].ressource(), m_ingredients[i].nombre());
                m_inventaire->enlever_ressource(num,1);
                metAJourRecette();
                return;
            }
        }
    }
    for(int i = 0; i < m_ingredients.size(); i++)
    {
        if(m_ingredients[i].type() == Ressource_type::AucunType)
        {
            m_ingredients[i].setRessource(ressource);
            m_items->setItemRessource(i,m_ingredients[i].ressource());
            m_inventaire->enlever_ressource(num,1);
            metAJourRecette();
            return;
        }
    }
}

void FaireRecettes::double_clicue_ingredients(int num)
{
    if(m_ingredients[num].type() == Ressource_type::UneRessource)
    {
        Resss ressources;
        ressources.ress = m_ingredients[num].ressource();
        ressources.nbr = 1;
        m_inventaire->ajoute_ressource(ressources);
        if(m_ingredients[num].enleve())
            m_items->setItemRessource(num,0,0);
        else
            m_items->setItemRessource(num, m_ingredients[num].ressource(), m_ingredients[num].nombre());
    }
    else if(m_ingredients[num].type() == Ressource_type::UnEquipement)
    {
        Eqips equipements;
        equipements.equipement = new Outfit(*m_ingredients[num].equipement());
        equipements.nbr = 1;
        m_inventaire->ajoute_equipement(equipements);
        if(m_ingredients[num].enleve())
            m_items->setItemEquipement(num,0,0);
        else
            m_items->setItemEquipement(num, m_ingredients[num].equipement(), m_ingredients[num].nombre());
    }
    else if(m_ingredients[num].type() == Ressource_type::UneArme)
    {
        Armes armes;
        armes.arme = new Weapon(*m_ingredients[num].arme());
        armes.nbr = 1;
        m_inventaire->ajoute_arme(armes);
        if(m_ingredients[num].enleve())
            m_items->setItemArme(num,0,0);
        else
            m_items->setItemArme(num, m_ingredients[num].arme(), m_ingredients[num].nombre());
    }
    metAJourRecette();
}

FaireRecettes::~FaireRecettes()
{
    delete ui;
}

void FaireRecettes::metAJourRecette()
{
    bool efface = false;
    int quantite;
    if(m_recette)
        efface = true;
    m_recette = chercheRecette(&quantite);
    ui->quantite->setMaximum(quantite);
    if(m_recette)
    {
        ui->quantite->setValue(1);
        ui->lay_objet_cree->removeWidget(m_objet_cree);
        delete m_objet_cree;
        m_objet_cree = item(m_donnees_editeur->ressources, m_recette->objet_cree());
        ui->lay_objet_cree->addWidget(m_objet_cree);
    }
    else if(efface)
    {
        vide(false);
    }
}

void FaireRecettes::vide(bool efface_ingredients)
{
    m_recette = 0;
    ui->quantite->setValue(0);
    ui->lay_objet_cree->removeWidget(m_objet_cree);
    delete m_objet_cree;
    m_objet_cree = new ResourceItem();
    ui->lay_objet_cree->addWidget(m_objet_cree);
    if(efface_ingredients)
    {
        for(int i = 0; i < m_ingredients.size(); i++)
        {
            m_ingredients[i].setVide();
            m_items->setItemRessource(i,0,0);
        }
    }
}

Recipe *FaireRecettes::chercheRecette(int *quantite)//recherche si les ingredients correspondent à une recette
{
    QStringList recettes = m_metier->getMetierBase()->recettes();
    QVector<Resss>ingredients_necessaires;
    QVector<Resss>ingredients_disponibles;
    QVector<int>quantites_ingredients_disponibles;
    Recipe *recette;
    Resss ressource;
    //ajouter si on a trop de truc, recette impossible
    bool contient;
    int j;

    for(int i = 0; i < m_ingredients.size(); i++)
    {
        if(m_ingredients[i].type() != Ressource_type::AucunType)
        {
            ressource.nbr = m_ingredients[i].nombre();
            if(m_ingredients[i].type() == Ressource_type::UneRessource)
            {
                ressource.ress = m_ingredients[i].ressource();
                m_personnage->indexRessource(m_ingredients[i].ressource(), &j);
            }
            else if(m_ingredients[i].type() == Ressource_type::UnEquipement)
            {
                ressource.ress = m_ingredients[i].equipement()->getRessource();
                m_personnage->indexEquipement(m_ingredients[i].equipement(), &j);
            }
            else
            {
                ressource.ress = m_ingredients[i].arme()->getEquipement()->getRessource();
                m_personnage->indexArme(m_ingredients[i].arme(), &j);
            }
            ingredients_disponibles.push_back(ressource);
            quantites_ingredients_disponibles.push_back(j);
        }
    }

    for(int i = 0; i < recettes.size(); i++)
    {
        recette = m_metier->getMetierBase()->recette(recettes[i]);
        ingredients_necessaires = recette->ingredients();
        if(ingredients_necessaires.size() == ingredients_disponibles.size())
        {
            contient = true;
            j = 0;
            while(j < ingredients_disponibles.size() && contient)
            {
                contient = ingredients_disponibles.contains(ingredients_necessaires[j]);
                j++;
            }
            if(contient)
            {
                int nombre;
                *quantite = quantites_ingredients_disponibles[0] / ingredients_disponibles[0].nbr;
                for(int m = 0; m < ingredients_disponibles.size(); m++)
                {
                    nombre = quantites_ingredients_disponibles[m] / ingredients_disponibles[m].nbr;
                    if(nombre < *quantite)
                        *quantite = nombre;
                }
                return recette;
            }
        }
    }
    if(quantite != 0)
        *quantite = 0;
    return 0;
}

void FaireRecettes::lance1fois()//permet de lancer la fabrication de la recette 1 fois
{
    if(ui->quantite->value() <=0)
        return;
    ui->quantite->setValue(ui->quantite->value()-1);
    ui->quantite->setMaximum(ui->quantite->maximum()-1);
    QString message = "rrr/", objetAjoute;
    int xp = xpParCase(m_recette->nombre_cases()), index, index2, nbr;
    m_metier->gagneXp(xp);
    message += m_metier->getNomMetier() + '/' + QString::number(xp) + '/';
    objetAjoute = m_personnage->gagneRessources(m_recette->objet_cree(), 1, &index);
    message += objetAjoute;
    if(objetAjoute.section('/',0,0) == "r")
    {
        Resss ressource;
        ressource.nbr = 1;
        ressource.ress = m_personnage->ressnum(index);
        m_inventaire->ajoute_ressource(ressource);
    }
    else if(objetAjoute.section('/',0,0) == "e")
    {
        Eqips equipement;
        equipement.nbr = 1;
        equipement.equipement = m_personnage->equipement_num(index);
        m_inventaire->ajoute_equipement(equipement);
    }
    else
    {
        Armes arme;
        arme.nbr = 1;
        arme.arme = m_personnage->armenum(index);
        m_inventaire->ajoute_arme(arme);
    }
    for(int i = 0; i < m_ingredients.size(); i++)
    {
        if(m_ingredients[i].type() != Ressource_type::AucunType)
        {
            nbr = m_ingredients[i].nombre();
            if(m_ingredients[i].type() == Ressource_type::UneRessource)
            {
                index = m_personnage->indexRessource(m_ingredients[i].ressource());
                if(ui->quantite->value() > 0)
                {
                    index2 = m_inventaire->indexRessource(m_ingredients[i].ressource());
                    m_inventaire->enlever_ressource(index2, m_ingredients[i].nombre());
                }
                m_personnage->enleverRessource(index, m_ingredients[i].nombre());
                message += "r/"+QString::number(index)+'/'+QString::number(nbr)+'/';
            }
            else if(m_ingredients[i].type() == Ressource_type::UnEquipement)
            {
                index = m_personnage->indexEquipement(m_ingredients[i].equipement());
                if(ui->quantite->value() > 1)
                {
                    index2 = m_inventaire->indexEquipement(m_ingredients[i].equipement());
                    m_inventaire->enlever_equipement(index2, m_ingredients[i].nombre());
                }
                m_personnage->enleverEquipement(index, m_ingredients[i].nombre());
                message += "e/"+QString::number(index)+'/'+QString::number(nbr)+'/';
            }
            else
            {
                index = m_personnage->indexArme(m_ingredients[i].arme());
                if(ui->quantite->value() > 1)
                {
                    index2 = m_inventaire->indexArme(m_ingredients[i].arme());
                    m_inventaire->enlever_arme(index2, m_ingredients[i].nombre());
                }
                m_personnage->enleverArme(index, m_ingredients[i].nombre());
                message += "a/"+QString::number(index)+'/'+QString::number(nbr)+'/';
            }
        }
    }
    if(ui->quantite->value() <= 0)
        vide(true);
    m_reseau->envoyer(message);
}

void FaireRecettes::lancexfois()//permet de lancer la fabrication en boucle de la recette
{
    QTimer::singleShot(INTERVALE_RECETTE,this, SLOT(encoreUneFois()));
}

void FaireRecettes::encoreUneFois()
{
    lance1fois();
    if(ui->quantite->value() > 0)
    {
        QTimer::singleShot(INTERVALE_RECETTE,this, SLOT(encoreUneFois()));
    }
}
