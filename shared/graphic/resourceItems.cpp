#include "items.h"

#include "inventory/resources.h"

Items::Items(QVector<Resss>ressources, int nbrobjh, int nbrobjv, LesRessources *lesressources)
{
    m_lesRessources = lesressources;
    m_nbrh = nbrobjh;
    m_nbrv = nbrobjv;
    m_scroll = new QScrollBar(Qt::Vertical);
    m_layout = new QGridLayout();
    m_layout->setSpacing(0);
    addLayout(m_layout);
    addWidget(m_scroll);
    m_scroll->setMinimum(0);
    m_scroll->setPageStep(m_nbrv);
    int max = qCeil((double) ressources.size()/(double) nbrobjh)-nbrobjv;
    if(max < 0)
        max = 0;
    m_scroll->setMaximum(max);

    if(!m_scroll->maximum())
        m_scroll->setVisible(false);

    for(int i = 0; i < ressources.size(); i++)
    {
        if(ressources[i].ress)
        {
            m_items.push_back(new Item(ressources[i].ress, ressources[i].nbr, i));
            connect(m_items[i], SIGNAL(clique(int)), this, SLOT(cliqueObjet(int)));
            connect(m_items[i], SIGNAL(dbclique(int)), this, SLOT(dbcliqueObjet(int)));
        }
        else
            m_items.push_back(new Item());
    }
    remplire(0);

    connect(m_scroll, SIGNAL(valueChanged(int)), this, SLOT(scrool(int)));
}

Items::Items(QVector<Eqips>equipements, int nbrobjh, int nbrobjv, LesRessources *lesressources)
{
    m_lesRessources = lesressources;
    m_nbrh = nbrobjh;
    m_nbrv = nbrobjv;
    m_scroll = new QScrollBar(Qt::Vertical);
    m_layout = new QGridLayout();
    m_layout->setSpacing(0);
    addLayout(m_layout);
    addWidget(m_scroll);
    m_scroll->setMinimum(0);
    m_scroll->setPageStep(m_nbrv);
    int max = qCeil((double) equipements.size()/(double) nbrobjh)-nbrobjv;
    if(max < 0)
        max = 0;
    m_scroll->setMaximum(max);

    if(!m_scroll->maximum())
        m_scroll->setVisible(false);

    for(int i = 0; i < equipements.size(); i++)
    {
        if(equipements[i].equipement)
        {
            m_items.push_back(new Item(equipements[i].equipement, equipements[i].nbr, i));
            connect(m_items[i], SIGNAL(clique(int)), this, SLOT(cliqueObjet(int)));
            connect(m_items[i], SIGNAL(dbclique(int)), this, SLOT(dbcliqueObjet(int)));
        }
        else
            m_items.push_back(new Item());
    }
    remplire(0);

    connect(m_scroll, SIGNAL(valueChanged(int)), this, SLOT(scrool(int)));
}

Items::Items(QVector<Armes>armes, int nbrobjh, int nbrobjv, LesRessources *lesressources)
{
    m_lesRessources = lesressources;
    m_nbrh = nbrobjh;
    m_nbrv = nbrobjv;
    m_scroll = new QScrollBar(Qt::Vertical);
    m_layout = new QGridLayout();
    m_layout->setSpacing(0);
    addLayout(m_layout);
    addWidget(m_scroll);
    m_scroll->setMinimum(0);
    m_scroll->setPageStep(m_nbrv);
    int max = qCeil((double) armes.size()/(double) nbrobjh)-nbrobjv;
    if(max < 0)
        max = 0;
    m_scroll->setMaximum(max);

    if(!m_scroll->maximum())
        m_scroll->setVisible(false);

    for(int i = 0; i < armes.size(); i++)
    {
        if(armes[i].arme)
        {
            m_items.push_back(new Item(armes[i].arme, armes[i].nbr, i));
            connect(m_items[i], SIGNAL(clique(int)), this, SLOT(cliqueObjet(int)));
            connect(m_items[i], SIGNAL(dbclique(int)), this, SLOT(dbcliqueObjet(int)));
        }
        else
            m_items.push_back(new Item());
    }
    remplire(0);

    connect(m_scroll, SIGNAL(valueChanged(int)), this, SLOT(scrool(int)));
}

Items::Items(int nbrPossible, int nbrMax, LesRessources *lesressources)
{
    m_nbrh = nbrMax;
    m_nbrv = 1;
    m_lesRessources = lesressources;
    m_scroll = new QScrollBar(Qt::Vertical);
    m_layout = new QGridLayout();
    m_layout->setSpacing(0);
    addLayout(m_layout);
    addWidget(m_scroll);
    m_scroll->setMinimum(0);
    m_scroll->setPageStep(m_nbrv);
    m_scroll->setMaximum(0);
    m_scroll->setVisible(false);

    for(int i = 0; i < nbrPossible; i++)
    {
        m_items.push_back(new Item());
    }
    for(int i = nbrPossible; i < nbrMax; i++)
    {
        m_items.push_back(new Item(false));
    }
    remplire(0);
}

void Items::scrool(int valeure)
{
    remplire(valeure);
}

void Items::remplire(int valeure)
{
    QPixmap pix = QPixmap("../data/interface/vide.png").scaled(40,40);
    int v;

    for(int y = 0; y < m_nbrv; y++)
    {
        for(int x = 0; x < m_nbrh; x++)
        {
            if(m_layout->itemAtPosition(y,x) != 0)
            {
                QWidget *widget = m_layout->itemAtPosition(y,x)->widget();
                widget->setVisible(false);
            }
        }
    }

    for(int i = 0; i < m_vides.size(); i++)
    {
        delete m_vides[i];
    }
    m_vides.clear();

    for(int y = 0; y < m_nbrv; y++)
    {
        for(int x = 0; x < m_nbrh; x++)
        {
            v = (valeure+y)*m_nbrh+x;
            if(v<m_items.size())
            {
                m_items[v]->setVisible(true);
                m_layout->addWidget(m_items[v],y,x);
            }
            else
            {
                m_vides.push_back(new QLabel());
                m_vides.last()->setPixmap(pix);
                m_layout->addWidget(m_vides.last(), y, x);
            }
        }
    }
}


void Items::cliqueObjet(int num)
{
    emit ressclique(num);
}

void Items::dbcliqueObjet(int num)
{
    emit ressdbclique(num);
}

void Items::enlevRess(int num, int nbr)
{
    int n = 0;
    m_items[num]->enleve(nbr);
    if(m_items[num]->quantite() < 1)
    {
        m_layout->removeWidget(m_items[num]);
        delete m_items[num];
        m_items.remove(num);
        for(int i = num; i < m_items.size(); i++)
        {
            m_items[i]->numMoins();
        }
        if(m_scroll->isVisible())
        {
            if(m_scroll->maximum() > 0 && (m_scroll->maximum()+m_nbrv)*m_nbrh-m_items.size() == m_nbrh)
            {
                m_scroll->setMaximum(m_scroll->maximum()-1);
                if(m_scroll->maximum() == 0)
                    m_scroll->setVisible(false);
                else
                    n = m_scroll->value();
            }
        }
    }
    remplire(n);
}


void Items::ajouteRess(Resss const& a, int num)
{
    int n = 0;
    if(m_scroll->isVisible())
        n = m_scroll->value();
    if(num >= m_items.size())
    {
        m_items.push_back(new Item(a.ress, a.nbr, num));
        connect(m_items[num], SIGNAL(clique(int)), this, SLOT(cliqueObjet(int)));
        connect(m_items[num], SIGNAL(dbclique(int)), this, SLOT(dbcliqueObjet(int)));
        if(m_items.size() > (m_scroll->maximum()+m_nbrv)*m_nbrh)
        {
            m_scroll->setMaximum(m_scroll->maximum()+1);
            m_scroll->setVisible(true);
        }
    }
    else
    {
        m_items[num]->ajoute(a.nbr);
    }
    remplire(n);
}

void Items::ajouteEquipement(Eqips const& a, int num)
{
    int n = 0;
    if(m_scroll->isVisible() && m_scroll->value() > 0)
        n = m_scroll->value();
    if(num >= m_items.size())
    {
        m_items.push_back(new Item(a.equipement, a.nbr, num));
        connect(m_items[num], SIGNAL(clique(int)), this, SLOT(cliqueObjet(int)));
        connect(m_items[num], SIGNAL(dbclique(int)), this, SLOT(dbcliqueObjet(int)));
        if(m_items.size() > (m_scroll->maximum()+m_nbrv)*m_nbrh)
        {
            m_scroll->setMaximum(m_scroll->maximum()+1);
            m_scroll->setVisible(true);
        }
    }
    else
    {
        m_items[num]->ajoute(a.nbr);
    }
    remplire(n);
}

void Items::ajouteArme(Armes const& a, int num)
{
    int n = 0;
    if(m_scroll->isVisible())
        n = m_scroll->value();
    if(num >= m_items.size())
    {
        m_items.push_back(new Item(a.arme, a.nbr, num));
        connect(m_items[num], SIGNAL(clique(int)), this, SLOT(cliqueObjet(int)));
        connect(m_items[num], SIGNAL(dbclique(int)), this, SLOT(dbcliqueObjet(int)));
        if(m_items.size() > (m_scroll->maximum()+m_nbrv)*m_nbrh)
        {
            m_scroll->setMaximum(m_scroll->maximum()+1);
            m_scroll->setVisible(true);
        }
    }
    else
    {
        m_items[num]->ajoute(a.nbr);
    }
    remplire(n);
}

void Items::setItemRessource(int num, const Resss &resss)
{
    setItemRessource(num, resss.ress, resss.nbr);
}

void Items::setItemEquipement(int num, Eqips const& equipements)
{
    setItemEquipement(num, equipements.equipement, equipements.nbr);
}

void Items::setItemArme(int num, Armes const& armes)
{
    setItemArme(num, armes.arme, armes.nbr);
}

void Items::setItemRessource(int num, Ressource *ressource, int nombre)
{
    m_layout->removeWidget(m_items[num]);
    delete m_items[num];
    if(!ressource || !nombre)
        m_items[num] = new Item();
    else
    {
        m_items[num] = new Item(ressource, nombre, num);
        connect(m_items[num], SIGNAL(clique(int)), this, SLOT(cliqueObjet(int)));
        connect(m_items[num], SIGNAL(dbclique(int)), this, SLOT(dbcliqueObjet(int)));
    }
    remplire(0);
}

void Items::setItemEquipement(int num, Equipement *equipement, int nombre)
{
    m_layout->removeWidget(m_items[num]);
    delete m_items[num];
    if(!equipement || !nombre)
        m_items[num] = new Item();
    else
    {
        m_items[num] = new Item(equipement, nombre, num);
        connect(m_items[num], SIGNAL(clique(int)), this, SLOT(cliqueObjet(int)));
        connect(m_items[num], SIGNAL(dbclique(int)), this, SLOT(dbcliqueObjet(int)));
    }
    remplire(0);
}

void Items::setItemArme(int num, Arme *arme, int nombre)
{
    m_layout->removeWidget(m_items[num]);
    delete m_items[num];
    if(!arme || !nombre)
    {
        m_items[num] = new Item();
    }
    else
    {
        m_items[num] = new Item(arme, nombre, num);
        connect(m_items[num], SIGNAL(clique(int)), this, SLOT(cliqueObjet(int)));
        connect(m_items[num], SIGNAL(dbclique(int)), this, SLOT(dbcliqueObjet(int)));
    }
    remplire(0);
}

Item *item(LesRessources *lesressources, Ressource *ressource, int quantite, int num)
{
    if(lesressources->estUnEquipement(ressource->nom()))
    {
        if(lesressources->estUneArme(ressource->nom()))
        {
            return new Item(lesressources->getArme(ressource->nom()), quantite, num);
        }
        else
        {
            return new Item(lesressources->getEquipement(ressource->nom()), quantite, num);
        }
    }
    else
    {
        return new Item(ressource, quantite, num);
    }
}
