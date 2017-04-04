#ifndef CREERPNJ_H
#define CREERPNJ_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include "scenery/constants.h"
#include "scenery/sceneryChange.h"
#include <QMouseEvent>

namespace Ui {
class CreerPnj;
}

class Bout : public QPushButton
{
    Q_OBJECT
public:
    Bout(QString const& texte, QString const& name);
signals:
    void ajoute(QString name);
    void edite(QString name);
    void detruit(QString name);
private:
    QString m_name;
protected:
    void mousePressEvent(QMouseEvent *event);
};

class CreerPnj : public QDialog
{
    Q_OBJECT
    
public:
    CreerPnj(QWidget *parent, qint16 *num, bool *ok, bool creation);
    QString enString();
    QString ecritReplique(QString const& name);
    static void supprimerPnj(qint16 numero);
    void chargerPnj();
    void ajouteReponses(QString const& name, QString *donnees);
    void ajoutePiste(QString name, QString *donnees);
    ~CreerPnj();

public slots:

    void accepter();
    void boutclique(QString name, QString texte = "-1");
    void spellBouton(QString name);
    void effaceReplique(QString name);
    
private:
    Ui::CreerPnj *ui;
    QMap<QString, Bout*>m_repliques;
    QMap<QString, QHBoxLayout*>m_layrepliques;
    QMap<QString, QVBoxLayout*>m_enfrepliques;
    qint16 *m_num;
    bool *m_ok;
    bool m_creation;
};

#endif // CREERPNJ_H
