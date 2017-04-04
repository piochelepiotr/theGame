#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <QString>
#include <QPixmap>
#include <QMap>
#include <QFile>

class Resource;

typedef struct Resss Resss;
struct Resss
{
    int nbr;
    Resource *ress;
};

bool operator==(Resss const &a, Resss const& b);

class Resource
{
public:
    Resource(QString const& nom, int pods, QString const& description, int niveau, QString const& categorie);
    QString nom() const { return m_nom; }
    int pods() const { return m_pods; }
    QString description() const { return m_description; }
    int niveau() const { return m_niveau; }
    QString categorie() const { return m_categorie; }
    QPixmap imagep() const { return m_imagep; }
    QPixmap imageg() const { return m_imageg; }
    void setCategorie(QString const& categorie) { m_categorie = categorie; }
    void setPods(int pods) { m_pods = pods; }
    void setNiveau(int niveau) { m_niveau = niveau; }
    void setDescription(QString const& description) { m_description = description; }
    void setImage(QString const& chemin);
    static QString enString(Resss const& resss);
    static Resss chargeRess(int nbr, Resource *resource);
    static Resource *nouvelle(const QString &nom, QString const& chemin);
    QString longue_description();

private:

    QString m_nom;
    int m_pods;
    QString m_description;
    int m_niveau;
    QString m_categorie;
    QPixmap m_imagep;
    QPixmap m_imageg;
};

#endif // RESSOURCE_H
