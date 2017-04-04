#include "spellLayout.h"

SpellLayout::SpellLayout(Spell *spell) : QWidget()
{
    m_nom = spell->nom();
    QHBoxLayout *layout = new QHBoxLayout();
    QLabel *labelImage = new QLabel();
    QPixmap image = QPixmap(DOSSIER_IMAGES_SORTS+spell->nom()).scaled(QSize(30,30));
    QLabel *nom = new QLabel(spell->nom());
    QLabel *niveau = new QLabel("niveau : "+QString::number(spell->niveau()));
    labelImage->setPixmap(image);
    layout->addWidget(labelImage);
    layout->addWidget(nom);
    layout->addWidget(niveau);
    this->setLayout(layout);
    installEventFilter(this);
}

bool SpellLayout::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj == this && ev->type() == QEvent::MouseButtonPress)
    {
        emit clique(m_nom);
        return true;
    }
    else
    {
        return QWidget::eventFilter(obj,ev);
    }
}
