#ifndef MONDE_H
#define MONDE_H

#include "scenery/constants.h"
#include <QMap>
#include <QObject>
#include "scenery/scenery.h"
#include "scenery/sceneryChange.h"
#include "map/point.h"
#include <QTimer>
#include <QSignalMapper>
#include "monde/combat.h"
#include "map/map.h"
#include "monde/map.h"

class Monde : public QObject
{
    Q_OBJECT

signals:
    void repousse(Point posmap, int posx,int posy);
    //void s_envoie(QString qui,QString message);

public:
    Monde(Data *donnees_editeur, Ecran *ecran);
    ServerMap *map(Point const& p) const { return m_maps[p]; }
    void connectPlayer(Joueur *player);
    void disconnectPlayer(QString const& nom);
    void sendMessage(QString const& nom, QString const& message);
    ~Monde();
public slots:
    //void envoie(QString qui,QString message);
private:
    QMap<Point, ServerMap*>m_maps;
    Data *m_donnees_editeur;
    Ecran *m_ecran;
    QMap<QString, Joueur *>m_players;
};

#endif // MONDE_H
