#ifndef EDITERPNJS_H
#define EDITERPNJS_H

#include <QDialog>
#include "editobject.h"
#include "createnpc.h"
#include "scenery/scenery.h"
#include <QTableWidgetItem>

namespace Ui {
class EditerPnjs;
}

class Bouton2 : public QPushButton
{
    Q_OBJECT

public:
    Bouton2(QString const& texte, qint16 num);

public slots:
    void clique();
signals:
    void clique(qint16 num);

private:
    qint16 m_num;
};

class EditerPnjs : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditerPnjs(QWidget *parent, Scenery *decors);
    ~EditerPnjs();

public slots:

    void chargepnjs();
    void ajouterNouveau(qint16 num = 0);
    void modifierpnj_objet(qint16 num);
    void modifierpnj_dialogues(qint16 num);
    
private:
    Ui::EditerPnjs *ui;
    QVector<Bouton2*>bouts_spell_objet;
    QVector<Bouton2*>bouts_spell_dialogues;
    QMap<qint16, QTableWidgetItem*>m_names;
    Scenery *m_decors;
};

#endif // EDITERPNJS_H
