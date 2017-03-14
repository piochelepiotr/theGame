#ifndef LAYOUTBARREOUTIL_H
#define LAYOUTBARREOUTIL_H

#include <QHBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QListWidget>
#include <QLabel>
#include "graphic/boutonimgString.h"
#include "entities/character.h"

class FenPrin;

class LayoutBarreOutil : public QHBoxLayout
{
    Q_OBJECT
public:
    explicit LayoutBarreOutil(FenPrin *parent,Personnage *perso);
    QListWidget *getChat() const { return m_chat; }
    QLineEdit *getLineEditChat() const { return m_bar_chat; }
    void phasePlacement();
    void phaseCombat();
    void setPret(bool pret);
    void setMonTour(bool monTour);

signals:

public slots:

    void setPC(int pc);
    void setVie(int vie);
private:
    FenPrin *m_parent;
    QListWidget *m_chat;
    QLineEdit *m_bar_chat;
    QVBoxLayout *m_lay_chat;
    QPushButton *m_bout_cara;
    QPushButton *m_bout_passer_tour;
    QProgressBar *m_bar_vie;
    QHBoxLayout *m_lay_sorts;
    BoutonImgString *m_bout_cac;
    QLabel *m_labelPC;
};

#endif // LAYOUTBARREOUTIL_H
