#include "subwindow.h"
#include "graphic/gamescene.h"
#include <QGraphicsProxyWidget>
#include <QDebug>
#include "scenery/constants.h"

SubWindow::SubWindow(GameScene *gameScene, Place place, int width, int height)
{
    m_gameScene = gameScene;
    m_place = place;
    m_item = gameScene->addWidget(this);
    m_item->setZValue(1000);
    m_item->resize(width,height);
    gameResized();
    m_mainLayout.setMargin(0);  // No space between window's element and the border
    m_mainLayout.setSpacing(0); // No space between window's element
    setLayout(&m_mainLayout);
    m_mainLayout.addWidget(&m_titleBar,0,0,1,1);
    m_mainLayout.addWidget(&m_content,1,0,1,1);
    m_mainLayout.setRowStretch(1,2);
    m_titleBar.updateWindowTitle("BLABLABA");
    connect(&m_titleBar,SIGNAL(closeWindow()),this,SLOT(closeWindow()));
}

void SubWindow::gameResized()
{
    if(m_place == Centered)
    {
        m_item->setPos(m_gameScene->getlmap()/2-this->width()/2,m_gameScene->gethmap()/2-this->height()/2);
    }
}

void SubWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush background(QColor(23,23,34));
    painter.setBrush(background);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0,0,this->width(),this->height());
}

void SubWindow::setTitle(const QString &title)
{
    m_titleBar.updateWindowTitle(title);
}

/*void SubWindow::closeWindow()
{
    //closeActions();
}*/

/*void SubWindow::closeActions()
{
    //nothing done here, only if class inherited
}*/
