#ifndef LAYHOME_H
#define LAYHOME_H

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QFrame>
#include <QLineEdit>

class LayHome : public QWidget
{
public:
    LayHome();
    ~LayHome();
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_layCenter;
    QFrame *m_centerFrame;
    QVBoxLayout *m_layFrame;
    QHBoxLayout *m_layButtons;
    QHBoxLayout *m_layName;
    QHBoxLayout *m_layPassword;
    QLabel *m_labelPassword;
    QLabel *m_labelName;
    QLineEdit *m_password;
    QLineEdit *m_name;
    QPushButton *m_subscribeButton;
    QPushButton *m_connectButton;
};

#endif // LAYHOME_H
