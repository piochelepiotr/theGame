#include "scenery/object.h"

Object::Object(qint16 numero, const QString &name, const QString &categorie, double propx, double propy, int lcase, int hcase)
{
    m_numero = numero;
    m_name = name;
    m_categorie = categorie;
    m_propx = propx;
    m_propy = propy;
    m_largeur = (int)((double)lcase*m_propx);
    m_hauteur = (int)((double)hcase*m_propy);
}

Object::Object()
{
    m_numero = 0;
    m_name = "";
    m_categorie = "aucune";
    m_propx = 0;
    m_propy = 0;
    m_largeur = 0;
    m_hauteur = 0;
}

QPixmap Object::image()
{
    if(m_image.isNull())
    {
        m_image = QPixmap("../data/objets/"+QString::number(m_numero)).scaled(m_largeur, m_hauteur);
    }
    return m_image;
}

void Object::resize(int lcase, int hcase)
{
    m_largeur = (int)((double)lcase*m_propx);
    m_hauteur = (int)((double)hcase*m_propy);
    if(!m_image.isNull())
    {
        m_image = QPixmap();
    }
}

void Object::setPropx(double propx, int lcase, int hcase)
{
    m_propx = propx;
    m_largeur = (int)((double)lcase*m_propx);
    m_hauteur = (int)((double)hcase*m_propy);
}

void Object::setPropy(double propy, int lcase, int hcase)
{
    m_propy = propy;
    m_largeur = (int)((double)lcase*m_propx);
    m_hauteur = (int)((double)hcase*m_propy);
}

bool ordreAlphabetique(Object *a, Object *b)
{
    return QString::compare(a->name(), b->name(), Qt::CaseInsensitive) < 0;
}
