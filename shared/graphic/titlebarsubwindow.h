#ifndef TITLEBARSUBWINDOW_H
#define TITLEBARSUBWINDOW_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include "graphic/windowbutton.h"

class TitleBarSubWindow : public QWidget
{
    Q_OBJECT
public:
    TitleBarSubWindow(const QString &title = "title", QWidget *parent = 0);
    void updateWindowTitle(QString const& title);
public slots:
    void quitWindow();
signals:
    void closeWindow();
private:
    QPixmap *m_cache;
protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void paintEvent (QPaintEvent  *event);
    QLabel m_title;
    WindowButton m_close;
};

#endif // TITLEBARSUBWINDOW_H
