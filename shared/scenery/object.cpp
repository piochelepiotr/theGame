#include "scenery/object.h"

Objet::Objet(qint16 numero, const QString &nom, const QString &categorie, double propx, double propy, int lcase, int hcase)
{
    m_numero = numero;
    m_nom = nom;
    m_categorie = categorie;
    m_propx = propx;
    m_propy = propy;
    m_largeur = (int)((double)lcase*m_propx);
    m_hauteur = (int)((double)hcase*m_propy);
}

Objet::Objet()
{
    m_numero = 0;
    m_nom = "";
    m_categorie = "aucune";
    m_propx = 0;
    m_propy = 0;
    m_largeur = 0;
    m_hauteur = 0;
}

QPixmap Objet::image()
{
    if(m_image.isNull())
    {
        m_image = QPixmap("../data/objets/"+QString::number(m_numero)).scaled(m_largeur, m_hauteur);
    }
    return m_image;
}

void Objet::resize(int lcase, int hcase)
{
    m_largeur = (int)((double)lcase*m_propx);
    m_hauteur = (int)((double)hcase*m_propy);
    if(!m_image.isNull())
    {
        m_image = QPixmap();
    }
}

void Objet::setPropx(double propx, int lcase, int hcase)
{
    m_propx = propx;
    m_largeur = (int)((double)lcase*m_propx);
    m_hauteur = (int)((double)hcase*m_propy);
}

void Objet::setPropy(double propy, int lcase, int hcase)
{
    m_propy = propy;
    m_largeur = (int)((double)lcase*m_propx);
    m_hauteur = (int)((double)hcase*m_propy);
}

bool ordreAlphabetique(Objet *a, Objet *b)
{
    return QString::compare(a->nom(), b->nom(), Qt::CaseInsensitive) < 0;
}
