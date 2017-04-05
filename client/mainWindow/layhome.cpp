#include "layhome.h"

LayHome::LayHome()
{
    m_labelName.setText("Nom de compte");
    m_labelPassword.setText("Mot de passe");
    m_connectButton.setText("Se connecter");
    m_subscribeButton.setText("S'inscrire");


    m_layButtons.addWidget(&m_subscribeButton);
    m_layButtons.addWidget(&m_connectButton);

    m_layName.addWidget(&m_labelName);
    m_layName.addWidget(&m_name);

    m_layPassword.addWidget(&m_labelPassword);
    m_layPassword.addWidget(&m_password);

    m_layCenter.addStretch();
    //m_layCenter.addWidget(&m_leftSpacer);
    m_layCenter.addWidget(&m_centerFrame);
    //m_layCenter.addWidget(&m_rightSpacer);
    m_layCenter.addStretch();

    m_centerFrame.setLayout(&m_layFrame);
    m_layFrame.addLayout(&m_layName);
    m_layFrame.addLayout(&m_layPassword);
    m_layFrame.addLayout(&m_layButtons);


    this->addStretch();
    //this->addWidget(&m_topSpacer);
    this->addLayout(&m_layCenter);
    //this->addWidget(&m_bottomSpacer);
    this->addStretch();
}
