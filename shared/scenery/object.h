#ifndef OBJET_H
#define OBJET_H

#include <QPixmap>

class Object
{
public:
    Object(qint16 numero, QString const& name, QString const& categorie, double propx, double propy, int lcase, int hcase);
    Object();
    qint16 numero() const { return m_numero; }
    QString name() const { return m_name; }
    QString categorie() const { return m_categorie; }
    double propx() const { return m_propx; }
    double propy() const { return m_propy; }
    void setPropx(double propx, int lcase, int hcase);
    void setPropy(double propy, int lcase, int hcase);
    void setNom(QString const& name) { m_name = name; }
    QPixmap image();
    void resize(int lcase, int hcase);

private:
    QPixmap m_image;
    QString m_name;
    qint16 m_numero;
    QString m_categorie;
    double m_propx;
    double m_propy;
    int m_largeur;
    int m_hauteur;
};

bool ordreAlphabetique(Object *a, Object *b);

#endif // OBJET_H
