#ifndef VARIOUSTAB_H
#define VARIOUSTAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>


class MainWindow;
class Jeu2d;


class VariousTab : public QWidget
{
    Q_OBJECT
public:
    explicit VariousTab(MainWindow *mainWindow);

    QVBoxLayout *m_lay_divers;
        QGroupBox *m_groupzoom;
            QHBoxLayout *m_layzoom;
                QRadioButton *m_vue_large;
                QRadioButton *m_vue_reduite;
        QGroupBox *m_groupoutils;
            QHBoxLayout *m_layout_outils;
                QRadioButton *m_outil_objets;
                QRadioButton *m_outil_transporteurs;
                QRadioButton *m_outil_cases_marchables;
                QRadioButton *m_outil_casescbt;
                QRadioButton *m_outil_casespo;
        QPushButton *m_charger_contour;

signals:

public slots:

};

#endif // VARIOUSTAB_H
