#ifndef CLASSE_H
#define CLASSE_H

#include "entities/spellModel.h"
#include "entities/entityModel.h"

class CharacterModel : public EntityModel
{
public:
    CharacterModel(QString const& donnees, QMap<QString, SpellModel*>const&getSpells);
    QString arme() const { return m_arme; }
    QString metier() const { return m_metier; }
    virtual bool isMonster() const { return false; }
private:
    QString m_metier;
    QString m_arme;
};

#endif // CLASSE_H
