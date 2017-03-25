#ifndef IMAGES_CLASSE_H
#define IMAGES_CLASSE_H

#include <QString>
#include <QPixmap>
#include <QVector>
#include <QMap>
#include "entities/entityModel.h"

class ImagesAction
{
public:
    ImagesAction(QString const& nom_classe, const QString &nom_action, const QSize &size);
    int nombre_images(Dir orientation) const { return m_images[(int)orientation].size(); }
    bool redimentionne(QSize const& nouvelle);
    QPixmap getImage(int num, Dir orientation) const;
    bool enMouvement() const { return m_enMouvement; }
    void plus_utilisateur() { m_nbrUtilisateur++; }
    void moins_utilisateur() { m_nbrUtilisateur--; }
    void definieEnMouvement();
private:
    QString m_nomClasse;
    QString m_nomAction;
    QVector<QPixmap>m_images[8];
    int m_nbrUtilisateur;
    bool m_enMouvement;
};

class ImagesEntity
{
public:
    ImagesEntity(EntityModel *uneCreature, const QSize &taille);
    ImagesAction *getImagesAction(QString const& nomAction);
    void redimentionne(QSize const& nouvelle);
private:
    QSize m_taille;
    EntityModel *m_uneCreature;
    QMap<QString,ImagesAction*>m_images;
};

class ImagesEntities
{
public:
    ImagesEntities(QMap<QString, EntityModel*>creatures, QSize const& taille);
    ImagesEntity *getImagesUneCreature(QString const& nom) const;
    void redimentionne(QSize const& taille);
    ~ImagesEntities();
private:
    QMap<QString,ImagesEntity*>m_creatures;
};

#endif // IMAGES_CLASSE_H
