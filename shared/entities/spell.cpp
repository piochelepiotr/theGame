#include "entities/spell.h"

Spell::Spell(QString const& nom, int niveau, int points_fight, int portee_min, int portee_max, int degats_terre_min, int degats_terre_max)
{
    m_nom = nom;
    m_niveau = niveau;
    m_points_fight = points_fight;
    m_portee_min = portee_min;
    m_portee_max = portee_max;
    m_degats_terre_min = degats_terre_min;
    m_degats_terre_max = degats_terre_max;
}

QString Spell::decrit(Spell *spell)
{
    QString texte;
    texte += "<table width=\"100%\" >";
    texte += "<tr>";
    texte += "<td><b>"+QObject::trUtf8("attaque : ")+spell->nom()+"</b></td>";
    texte += "<td align=\"right\" >"+QObject::trUtf8("niveau ")+QString::number(spell->niveau())+"</td>";
    texte += "</tr><tr>";
    texte += "<td>"+QObject::trUtf8("portée : ")+QString::number(spell->portee_min())+QObject::trUtf8(" à ")+QString::number(spell->portee_max())+"</td>";
    texte += "<td align=\"right\" >"+QString::number(spell->points_fight())+QObject::trUtf8(" PC") + "</td>";
    texte += "</tr>";
    texte += "</table";

    texte += "<p>"+QObject::trUtf8("dommages : ")+"</p>";

    if(spell->degats_terre_min()*spell->degats_terre_max()<0)//signes différents
        texte += "<li style=\"color:rgb(131,27,81);\" >"+QString::number(qMin(spell->degats_terre_min(), spell->degats_terre_max()))+QObject::trUtf8(" soins terre à ")+QString::number(qMax(spell->degats_terre_min(), spell->degats_terre_max()))+QObject::trUtf8(" dégâts terre")+"</li>";
    else if(spell->degats_terre_max() > 0)//212 44 0
        texte += "<li style=\"color:rgb(212,44,0);\" >"+QString::number(spell->degats_terre_min())+QObject::trUtf8(" à ")+QString::number(spell->degats_terre_max())+QObject::trUtf8(" dégâts terre")+"</li>";
    else if(spell->degats_terre_min() < 0)
        texte += "<li style=\"color:rgb(27,88,131);\" >"+QString::number(-spell->degats_terre_max())+QObject::trUtf8(" à ")+QString::number(-spell->degats_terre_min())+QObject::trUtf8(" soins terre")+"</li>";

    return texte;
}

int Spell::degats()
{
    return qrand()%(m_degats_terre_max-m_degats_terre_min+1)+m_degats_terre_min;
}

QString Spell::enString() const
{
    return m_nom + "/" + QString::number(m_niveau) + "/";
}

QString Spell::longue_description()
{
    return Spell::decrit(this);
}

bool operator==(Spell const& a, Spell const& b)
{
    if(a.nom() != b.nom())
        return false;
    return a.niveau() == b.niveau();
}
