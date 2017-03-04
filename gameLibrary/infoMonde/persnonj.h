#ifndef PERSNONJ_H
#define PERSNONJ_H

#include <QString>
#include <QVector>

class Reponses;
class Piste;

class Reponses
{
public:
    Reponses(QString donnee, QString *reste);
    ~Reponses();
    int nbrpistes() const { return m_pistes.size(); }
    Piste *pistenum(int i) const { return m_pistes[i]; }

private:
    QVector<Piste*>m_pistes;
};

class Piste
{
public:
    Piste(QString donnees, QString *reste);
    ~Piste();
    Reponses *reponses() const { return m_reponses; }
    QString replique() const { return m_replique; }
    QString reponse() const { return m_reponse; }

private:
    QString m_reponse;
    QString m_replique;
    Reponses *m_reponses;
};

class PersNonJ
{
public:
    PersNonJ(QString donnes);
    ~PersNonJ();
    QString replique() const { return m_replique; }
    Reponses *reponses() const { return m_reponses; }
    QString nom() const { return m_nom; }

private:
    QString m_replique;
    Reponses *m_reponses;
    QString m_nom;
};

bool repliqueFinale(QString const& replique);

#endif // PERSNONJ_H
