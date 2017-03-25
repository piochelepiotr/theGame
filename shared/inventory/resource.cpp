#include "inventory/resource.h"

Resource::Resource(const QString &nom, int pods, const QString &description, int niveau, const QString &categorie)
{
    m_nom = nom;
    m_pods = pods;
    m_description = description;
    m_niveau = niveau;
    m_categorie = categorie;
    m_imageg = QPixmap("../data/Ressources/images/"+m_nom+".png").scaled(150,150);
    m_imagep = QPixmap("../data/Ressources/images/"+m_nom+".png").scaled(40,40);
}

QString Resource::enString(Resss const& resss)
{
    return QString::number(resss.nbr)+ '/' + resss.ress->nom() + '/';
}

Resss Resource::chargeRess(int nbr, Resource *ressource)
{
    Resss resss;
    resss.ress = ressource;
    resss.nbr = nbr;
    return resss;
}

Resource *Resource::nouvelle(QString const& nom, const QString &chemin)
{
    QFile::copy(chemin, "../data/Ressources/images/"+nom+".png");
    return new Resource(nom, 1, "", 1, "ressources");
}

void Resource::setImage(QString const& chemin)
{
    QFile::remove("../data/Ressources/images/"+m_nom+".png");
    QFile::copy(chemin, "../data/Ressources/images/"+m_nom+".png");
    m_imageg = QPixmap("../data/Ressources/images/"+m_nom+".png").scaled(150,150);
    m_imagep = QPixmap("../data/Ressources/images/"+m_nom+".png").scaled(40,40);
}

QString Resource::longue_description()
{
    QString texte;
    texte += "<table width=\"100%\" >";
    texte += "<tr>";
    texte += "<td><b>"+nom()+"</b></td>";
    texte += "<td align=\"right\" >"+QObject::trUtf8("niveau ")+QString::number(niveau())+"</td>";
    texte += "</tr><tr>";
    texte += "<td>"+QObject::trUtf8("catégorie : ")+categorie()+"</td>";
    texte += "<td align=\"right\" >"+QString::number(pods());
    if(pods() == 1)
       texte += QObject::trUtf8(" pod");
    else
       texte += QObject::trUtf8(" pods");
    texte += "</td>";
    texte += "</tr>";
    texte += "</table";
    texte += "<p>"+description()+"</p>";
    return texte;
}

bool operator==(Resss const &a, Resss const& b)
{
    return a.ress == b.ress && a.nbr == b.nbr;
}
