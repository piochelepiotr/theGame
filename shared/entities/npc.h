#ifndef PERSNONJ_H
#define PERSNONJ_H

#include <QString>
#include <QVector>

class Answers;
class Dialog;

class Answers
{
public:
    Answers(QString donnee, QString *reste);
    ~Answers();
    int nbrpistes() const { return m_pistes.size(); }
    Dialog *pistenum(int i) const { return m_pistes[i]; }

private:
    QVector<Dialog*>m_pistes;
};

class Dialog
{
public:
    Dialog(QString donnees, QString *reste);
    ~Dialog();
    Answers *reponses() const { return m_reponses; }
    QString replique() const { return m_replique; }
    QString reponse() const { return m_reponse; }

private:
    QString m_reponse;
    QString m_replique;
    Answers *m_reponses;
};

class NPC
{
public:
    NPC(QString donnes);
    ~NPC();
    QString replique() const { return m_replique; }
    Answers *reponses() const { return m_reponses; }
    QString name() const { return m_name; }

private:
    QString m_replique;
    Answers *m_reponses;
    QString m_name;
};

bool repliqueFinale(QString const& replique);

#endif // PERSNONJ_H
