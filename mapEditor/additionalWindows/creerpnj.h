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
#include "additionalActions/constantes.h"
#include "additionalActions/actionObjets.h"
#include <QMouseEvent>

namespace Ui {
class CreerPnj;
}

class Bout : public QPushButton
{
    Q_OBJECT
public:
    Bout(QString const& texte, QString const& nom);
signals:
    void ajoute(QString nom);
    void edite(QString nom);
    void detruit(QString nom);
private:
    QString m_nom;
protected:
    void mousePressEvent(QMouseEvent *event);
};

class CreerPnj : public QDialog
{
    Q_OBJECT
    
public:
    CreerPnj(QWidget *parent, qint16 *num, bool *ok, bool creation);
    QString enString();
    QString ecritReplique(QString const& nom);
    static void supprimerPnj(qint16 numero);
    void chargerPnj();
    void ajouteReponses(QString const& nom, QString *donnees);
    void ajoutePiste(QString nom, QString *donnees);
    ~CreerPnj();

public slots:

    void accepter();
    void boutclique(QString nom, QString texte = "-1");
    void editerBouton(QString nom);
    void effaceReplique(QString nom);
    
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
