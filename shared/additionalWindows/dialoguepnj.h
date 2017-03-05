#ifndef DIALOGUEPNJ_H
#define DIALOGUEPNJ_H

#include <QDialog>
#include <QPushButton>
#include "infoMonde/persnonj.h"
#include <QPlainTextEdit>
#include <QVBoxLayout>

class Bouton_num : public QPushButton
{
    Q_OBJECT
public :
    Bouton_num(QString const& texte, int num);
private:
    int m_num;
signals:
    void clique(int);
public slots:
    void cliquer();
};

class Dialoguepnj : public QDialog
{
    Q_OBJECT
public:
    explicit Dialoguepnj(QWidget *parent, PersNonJ *pers, QString *rep);
    void affiche();
    
signals:
    
public slots:

    void reponsecliquee(int num);

private:
    QString *m_reponse;
    Reponses *m_repactuelles;
    QVector<Bouton_num*>m_reponses;
    QPlainTextEdit *m_replique;
    QVBoxLayout *m_lay;
};

#endif // DIALOGUEPNJ_H
