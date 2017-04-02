#include "subwindow.h"
#include "graphic/gamescene.h"
#include <QGraphicsProxyWidget>
#include <QDebug>
#include "scenery/constants.h"
#include <QStyleOption>

SubWindow::SubWindow(GameScene *gameScene, Place place, int width, int height) : m_closeButton()
{
    m_gameScene = gameScene;
    m_gameScene->setSubWinOpened(true);
    qDebug() << "entering subwindow";
    m_closeButton.setFixedSize(40,40);
    m_closeButton.setObjectName("closeButton");
    m_closeButton.setIcon(QIcon("../data/interface/buttonClose.png"));
    m_closeButton.setIconSize(QSize(30,30));
    m_closeButton.setFlat(true);
    m_place = place;
    m_item = gameScene->addWidget(this);
    m_item->setZValue(1000);
    m_item->resize(width,height);
    gameResized();
    this->setLayout(&m_mainLayout);
    m_titleBar.addWidget(&m_title);
    m_titleBar.addWidget(&m_closeButton);
    m_mainLayout.addLayout(&m_titleBar);
    m_mainLayout.addWidget(&m_content);
    m_mainLayout.addStretch();
    setTitle("Titre");
    m_title.setObjectName("title");
    m_mainLayout.setMargin(0);  // No space between window's element and the border
    m_mainLayout.setSpacing(0); // No space between window's element
    connect(&m_closeButton,SIGNAL(pressed()), this, SLOT(closeWindow()));
    //connect(&m_closeButton,SIGNAL(clicked(bool)),this,SLOT(closeWindow()));
}

void SubWindow::gameResized()
{
    if(m_place == Centered)
    {
        m_item->setPos(m_gameScene->getlmap()/2-this->width()/2,m_gameScene->gethmap()/2-this->height()/2);
    }
}

void SubWindow::setTitle(const QString &title)
{
    m_title.setText(title);
}

void SubWindow::closeWindow()
{
    //closeActions();
    m_gameScene->setSubWinOpened(false);
    m_gameScene->removeItem(m_item);
}

void SubWindow::closeActions()
{
    //nothing done here, only if class inherited
}
