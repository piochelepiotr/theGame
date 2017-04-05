#include "laygame.h"

LayGame::LayGame()
{
    m_game = new QGraphicsView();
    m_game->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_game->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_toolBar = new QFrame();
    m_mainLayout = new QVBoxLayout();
    this->setLayout(m_mainLayout);
    m_mainLayout->addWidget(m_game);
    m_mainLayout->addWidget(m_toolBar);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);
}
