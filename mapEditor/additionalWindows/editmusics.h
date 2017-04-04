#ifndef EDITERMUSIQUES_H
#define EDITERMUSIQUES_H

#include <QDialog>
#include <QVector>

namespace Ui {
class EditerMusiques;
}

class EditerMusiques : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditerMusiques(QWidget *parent, QVector<QString>*musiques);
    ~EditerMusiques();

public slots:

    void accepter();
    void ajouter();
    
private:
    Ui::EditerMusiques *ui;
    QVector<QString>*m_musiques;
    int m_nbr;
};

#endif // EDITERMUSIQUES_H
