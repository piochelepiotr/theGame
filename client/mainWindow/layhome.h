#ifndef LAYHOME_H
#define LAYHOME_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QFrame>
#include <QLineEdit>

class LayHome : public QVBoxLayout
{
public:
    LayHome();
    QHBoxLayout m_layButtons;
    QHBoxLayout m_layName;
    QHBoxLayout m_layPassword;
    QHBoxLayout m_layCenter;
    QVBoxLayout m_layFrame;
    QFrame m_centerFrame;
    //QSpacerItem m_topSpacer;
    //QSpacerItem m_bottomSpacer;
    //QSpacerItem m_leftSpacer;
    //QSpacerItem m_rightSpacer;
    QLabel m_labelPassword;
    QLabel m_labelName;
    QLineEdit m_password;
    QLineEdit m_name;
    QPushButton m_subscribeButton;
    QPushButton m_connectButton;
};

#endif // LAYHOME_H
