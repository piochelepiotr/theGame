#ifndef OBJET_H
#define OBJET_H

#include <QPixmap>

class Object
{
public:
    Object(qint16 numero, QString const& nom, QString const& categorie, double propx, double propy, int lcase, int hcase);
    Object();
    qint16 numero() const { return m_numero; }
    QString nom() const { return m_nom; }
    QString categorie() const { return m_categorie; }
    double propx() const { return m_propx; }
    double propy() const { return m_propy; }
    void setPropx(double propx, int lcase, int hcase);
    void setPropy(double propy, int lcase, int hcase);
    void setNom(QString const& nom) { m_nom = nom; }
    QPixmap image();
    void resize(int lcase, int hcase);

private:
    QPixmap m_image;
    QString m_nom;
    qint16 m_numero;
    QString m_categorie;
    double m_propx;
    double m_propy;
    int m_largeur;
    int m_hauteur;
};

bool ordreAlphabetique(Object *a, Object *b);

#endif // OBJET_H
