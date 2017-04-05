#include "layhome.h"

LayHome::LayHome()
{
    m_mainLayout = new QVBoxLayout();
    m_layCenter = new QHBoxLayout();
    m_centerFrame = new QFrame;
    m_layFrame = new QVBoxLayout();
    m_layButtons = new QHBoxLayout();
    m_layName = new QHBoxLayout();
    m_layPassword = new QHBoxLayout();
    m_labelPassword = new QLabel("Mot de passe");
    m_labelName = new QLabel("Nom de compte");
    m_password = new QLineEdit();
    m_name = new QLineEdit();
    m_subscribeButton = new QPushButton("S'inscrire");
    m_connectButton = new QPushButton("Se connecter");

    this->setLayout(m_mainLayout);

    m_layButtons->addWidget(m_subscribeButton);
    m_layButtons->addWidget(m_connectButton);

    m_layName->addWidget(m_labelName);
    m_layName->addWidget(m_name);

    m_layPassword->addWidget(m_labelPassword);
    m_layPassword->addWidget(m_password);

    m_layCenter->addStretch();
    m_layCenter->addWidget(m_centerFrame);
    m_layCenter->addStretch();

    m_centerFrame->setLayout(m_layFrame);
    m_layFrame->addLayout(m_layName);
    m_layFrame->addLayout(m_layPassword);
    m_layFrame->addLayout(m_layButtons);


    m_mainLayout->addStretch();
    m_mainLayout->addLayout(m_layCenter);
    m_mainLayout->addStretch();
}

LayHome::~LayHome()
{

}
