#ifndef IMAGES_CLASSE_H
#define IMAGES_CLASSE_H

#include <QString>
#include <QPixmap>
#include <QVector>
#include <QMap>
#include "infoMonde/unecreature.h"

class Images_action
{
public:
    Images_action(QString const& nom_classe, const QString &nom_action, const QSize &size);
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

class Images_Classe
{
public:
    Images_Classe(UneCreature *uneCreature, const QSize &taille);
    Images_action *getImagesAction(QString const& nomAction);
    void redimentionne(QSize const& nouvelle);
private:
    QSize m_taille;
    UneCreature *m_uneCreature;
    QMap<QString,Images_action*>m_images;
};

class Images_Classes
{
public:
    Images_Classes(QMap<QString, UneCreature*>creatures, QSize const& taille);
    Images_Classe *getImagesUneCreature(QString const& nom) const;
    void redimentionne(QSize const& taille);
    ~Images_Classes();
private:
    QMap<QString,Images_Classe*>m_creatures;
};

#endif // IMAGES_CLASSE_H
