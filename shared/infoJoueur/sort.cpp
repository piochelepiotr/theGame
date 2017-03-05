#include "sort.h"

Sort::Sort(QString const& nom, int niveau, int points_combat, int portee_min, int portee_max, int degats_terre_min, int degats_terre_max)
{
    m_nom = nom;
    m_niveau = niveau;
    m_points_combat = points_combat;
    m_portee_min = portee_min;
    m_portee_max = portee_max;
    m_degats_terre_min = degats_terre_min;
    m_degats_terre_max = degats_terre_max;
}

QString Sort::decrit(Sort *sort)
{
    QString texte;
    texte += "<table width=\"100%\" >";
    texte += "<tr>";
    texte += "<td><b>"+QObject::trUtf8("attaque : ")+sort->nom()+"</b></td>";
    texte += "<td align=\"right\" >"+QObject::trUtf8("niveau ")+QString::number(sort->niveau())+"</td>";
    texte += "</tr><tr>";
    texte += "<td>"+QObject::trUtf8("portée : ")+QString::number(sort->portee_min())+QObject::trUtf8(" à ")+QString::number(sort->portee_max())+"</td>";
    texte += "<td align=\"right\" >"+QString::number(sort->points_combat())+QObject::trUtf8(" PC") + "</td>";
    texte += "</tr>";
    texte += "</table";

    texte += "<p>"+QObject::trUtf8("dommages : ")+"</p>";

    if(sort->degats_terre_min()*sort->degats_terre_max()<0)//signes différents
        texte += "<li style=\"color:rgb(131,27,81);\" >"+QString::number(qMin(sort->degats_terre_min(), sort->degats_terre_max()))+QObject::trUtf8(" soins terre à ")+QString::number(qMax(sort->degats_terre_min(), sort->degats_terre_max()))+QObject::trUtf8(" dégâts terre")+"</li>";
    else if(sort->degats_terre_max() > 0)//212 44 0
        texte += "<li style=\"color:rgb(212,44,0);\" >"+QString::number(sort->degats_terre_min())+QObject::trUtf8(" à ")+QString::number(sort->degats_terre_max())+QObject::trUtf8(" dégâts terre")+"</li>";
    else if(sort->degats_terre_min() < 0)
        texte += "<li style=\"color:rgb(27,88,131);\" >"+QString::number(-sort->degats_terre_max())+QObject::trUtf8(" à ")+QString::number(-sort->degats_terre_min())+QObject::trUtf8(" soins terre")+"</li>";

    return texte;
}

int Sort::degats()
{
    return qrand()%(m_degats_terre_max-m_degats_terre_min+1)+m_degats_terre_min;
}

QString Sort::enString() const
{
    return m_nom + "/" + QString::number(m_niveau) + "/";
}

QString Sort::longue_description()
{
    return Sort::decrit(this);
}

bool operator==(Sort const& a, Sort const& b)
{
    if(a.nom() != b.nom())
        return false;
    return a.niveau() == b.niveau();
}
