#include "spellLayout.h"

SpellLayout::SpellLayout(Spell *spell) : QWidget()
{
    m_name = spell->name();
    QHBoxLayout *layout = new QHBoxLayout();
    QLabel *labelImage = new QLabel();
    QPixmap image = QPixmap(DOSSIER_IMAGES_SORTS+spell->name()).scaled(QSize(30,30));
    QLabel *name = new QLabel(spell->name());
    QLabel *niveau = new QLabel("niveau : "+QString::number(spell->niveau()));
    labelImage->setPixmap(image);
    layout->addWidget(labelImage);
    layout->addWidget(name);
    layout->addWidget(niveau);
    this->setLayout(layout);
    installEventFilter(this);
}

bool SpellLayout::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj == this && ev->type() == QEvent::MouseButtonPress)
    {
        emit clique(m_name);
        return true;
    }
    else
    {
        return QWidget::eventFilter(obj,ev);
    }
}
