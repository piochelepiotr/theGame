#ifndef COMBATFRAMESTAB_H
#define COMBATFRAMESTAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QGroupBox>


class MainWindow;
class Jeu2d;

class CombatFramesTab : public QWidget
{
    Q_OBJECT
public:
    explicit CombatFramesTab(MainWindow *mainWindow, Jeu2d *gamePanel);

    QVBoxLayout *m_layCasesCombat;
        QGroupBox *m_groupCasesCbt;
            QHBoxLayout *m_laycasescbt;
                QRadioButton *m_equipe_une;
                QRadioButton *m_equipe_deux;

signals:

public slots:

};

#endif // COMBATFRAMESTAB_H
