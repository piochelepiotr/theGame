#include "windowactions.h"
#include <QDebug>

#define WIDTH 500
#define HEIGHT 300

WindowActions::WindowActions(GameScene *gameScene, Action *action) : SubWindow(gameScene,Centered,WIDTH,HEIGHT)
{
    qDebug() << "Entering windowActions";
    m_action = action;
    m_fightButton.setText("Attack");
    m_layout.addWidget(&m_fightButton);
    m_content.setLayout(&m_layout);
    connect(&m_fightButton,SIGNAL(clicked(bool)), this, SLOT(fight()));
}

void WindowActions::fight()
{
    *m_action = Fight;
    close();
}
