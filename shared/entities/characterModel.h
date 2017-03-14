#ifndef CLASSE_H
#define CLASSE_H

#include "entities/spellModel.h"
#include "entities/entityModel.h"

class Classe : public UneCreature
{
public:
    Classe(QString const& donnees, QMap<QString, UnSort*>const&sorts);
    QString arme() const { return m_arme; }
    QString metier() const { return m_metier; }

private:
    QString m_metier;
    QString m_arme;
};

#endif // CLASSE_H