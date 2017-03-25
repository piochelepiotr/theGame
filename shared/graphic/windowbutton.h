#ifndef WINDOWBUTTON_H
#define WINDOWBUTTON_H

#include <QAbstractButton>
#include <QPixmap>

class WindowButton : public QAbstractButton
{
    Q_OBJECT

public:
    enum ButtonType
    {
        BUTTON_MINIMIZE, BUTTON_MAXIMIZE, BUTTON_CLOSE
    };

    WindowButton(ButtonType type, QWidget *parent = 0);
    ~WindowButton();

protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void paintEvent (QPaintEvent  *event);
    virtual void enterEvent       (QEvent      *event);
    virtual void leaveEvent       (QEvent      *event);
    virtual void mousePressEvent  (QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    enum ButtonState
    {
        STATE_NORMAL, STATE_HOVERED, STATE_CLICKED
    };

    ButtonType  m_Type   ;
    ButtonState m_State  ;
    QPixmap    *m_Normal ;
    QPixmap    *m_Hovered;
    QPixmap    *m_Clicked;

    void InitPixmaps (                );
    void InitPixmap  (QPixmap **pixmap);
    void InitMinimize(                );
    void InitMaximize(                );
    void InitClose   (                );
};

#endif
