#include "windowactions.h"
#include <QDebug>

#define WIDTH 500
#define HEIGHT 100

WindowActions::WindowActions(GameScene *gameScene, QString const& clas, const QString &name) : SubWindow(gameScene,Centered,WIDTH,HEIGHT)
{
    m_name = name;
    m_fightButton.setText("Attack");
    m_fightButton.setFlat(true);
    m_layout.addWidget(&m_fightButton);
    m_content.setLayout(&m_layout);
    connect(&m_fightButton,SIGNAL(clicked(bool)), this, SLOT(fight()));
    setTitle(clas);
}

void WindowActions::fight()
{
    closeWindow();
    emit attackMonster(m_name);
}
