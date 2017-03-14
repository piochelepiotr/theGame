#ifndef BOUTON_H
#define BOUTON_H

#include <QPushButton>

class Bouton : public QPushButton
{
    Q_OBJECT

public:
    Bouton(QString const& texte, int num);
    void moinsnum() { m_num--; }

public slots:
    void clique();
signals:
    void clique(int num);

private:
    int m_num;
};

#endif // BOUTON_H
