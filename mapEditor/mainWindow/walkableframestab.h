#ifndef WALKABLEFRAMESTAB_H
#define WALKABLEFRAMESTAB_H

#include <QWidget>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QGroupBox>

class MainWindow;
class Jeu2d;


class walkableFramesTab : public QWidget
{
    Q_OBJECT
public:
    explicit walkableFramesTab(MainWindow *mainWindow, Jeu2d *gamePanel);

    QVBoxLayout *m_layCasesMarchables;
        QGroupBox *m_groupTaille;
            QHBoxLayout *m_laytaille;
                QRadioButton *m_un;
                QRadioButton *m_trois;
                QRadioButton *m_cinq;

signals:

public slots:

};

#endif // WALKABLEFRAMESTAB_H
