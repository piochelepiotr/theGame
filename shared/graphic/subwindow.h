#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QFrame>
#include <QLabel>

class GameScene;

enum Place{Centered,Right};

class SubWindow : public QFrame
{
    Q_OBJECT
public:
    SubWindow(GameScene *gameScene,Place place,int width,int height);
    void gameResized();
    void setTitle(const QString &title);
public slots:
    void closeWindow();
private:
    GameScene *m_gameScene;
    Place m_place;
    QGraphicsProxyWidget *m_item;
protected:
    virtual void closeActions();
    QVBoxLayout m_mainLayout;
    QHBoxLayout m_titleBar;
    QLabel m_title;
    QPushButton m_closeButton;
    QFrame m_content;
};

#endif // SUBWINDOW_H
