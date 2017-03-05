#ifndef OBJSURSCENE_H
#define OBJSURSCENE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Jeu_graphique;

class ObjSurScene : public QGraphicsPixmapItem
{
public:
    ObjSurScene(Jeu_graphique *parent, int largeurScene, QPoint const& pos = QPoint(-1,-1));
    void utile(QString const& aide);
    void inutile();
    void redi(int largeurScene);

protected:

    void mousePressEvent (QGraphicsSceneMouseEvent *);
private:
    bool m_utile;
    int m_largeurScene;
    QPoint m_pos;
    Jeu_graphique *m_parent;
};

#endif // OBJSURSCENE_H
