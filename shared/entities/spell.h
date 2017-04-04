#ifndef SORT_H
#define SORT_H

#include <QString>
#include <QObject>

class Spell
{
public:
    Spell(QString const& nom,int niveau, int points_fight, int portee_min, int portee_max, int degats_terre_min, int degats_terre_max);
    int degats_terre_min() const { return m_degats_terre_min; }
    int degats_terre_max() const { return m_degats_terre_max; }
    int portee_min() const { return m_portee_min; }
    int portee_max() const { return m_portee_max; }
    int points_fight() const { return m_points_fight; }
    QString nom() const { return m_nom; }
    int niveau() const { return m_niveau; }
    static QString decrit(Spell *sort);
    int degats();
    QString enString() const;
    QString longue_description();
private:
    QString m_nom;
    int m_points_fight;
    int m_portee_min;
    int m_portee_max;
    int m_degats_terre_min;
    int m_degats_terre_max;
    int m_niveau;
};

bool operator==(Spell const& a, Spell const& b);

#endif // SORT_H
