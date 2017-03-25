#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include "graphic/titlebarsubwindow.h"

class GameScene;

enum Place{Centered,Right};

class SubWindow : public QWidget
{
    //Q_OBJECT
public:
    SubWindow(GameScene *gameScene,Place place,int width,int height);
    void gameResized();
    void setTitle(const QString &title);
//public slots:
    //void closeWindow();
private:
    GameScene *m_gameScene;
    Place m_place;
    QGraphicsProxyWidget *m_item;
protected:
    //virtual void closeActions();
    virtual void paintEvent(QPaintEvent *event);
    QGridLayout m_mainLayout;
    TitleBarSubWindow m_titleBar;
    QFrame m_content;
};

#endif // SUBWINDOW_H
