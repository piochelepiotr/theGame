#ifndef MONDE_H
#define MONDE_H

#include "additionalActions/constantes.h"
#include <QMap>
#include <QObject>
#include "elementsMonde/decors.h"
#include "additionalActions/actionObjets.h"
#include "additionalActions/point.h"
#include <QTimer>
#include <QSignalMapper>
#include "monde/combat.h"
#include "additionalActions/datamap.h"
#include "monde/map.h"

class Monde : public QObject
{
    Q_OBJECT

signals:
    void repousse(Point posmap, int posx,int posy);
    //void s_envoie(QString qui,QString message);

public:
    Monde(Donnees_editeur *donnees_editeur, Ecran *ecran);
    Map *map(Point const& p) const { return m_maps[p]; }
    void connectPlayer(Joueur *player);
    void disconnectPlayer(QString const& nom);
    void sendMessage(QString const& nom, QString const& message);
    ~Monde();
public slots:
    //void envoie(QString qui,QString message);
private:
    QMap<Point, Map*>m_maps;
    Donnees_editeur *m_donnees_editeur;
    Ecran *m_ecran;
    QMap<QString, Joueur *>m_players;
};

#endif // MONDE_H
