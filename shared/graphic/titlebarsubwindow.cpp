#include "titlebarsubwindow.h"
#include <QPainter>

TitleBarSubWindow::TitleBarSubWindow(QString const&title, QWidget *parent) : QWidget(parent), m_title(this), m_close(WindowButton::BUTTON_CLOSE,this)
{
    setFixedHeight(33);
    m_title.setStyleSheet("color: white; font-family: Sans; font-weight: bold; font-size: 14px");
    updateWindowTitle(title);
    connect(&m_close,SIGNAL(clicked()),this, SLOT(quitWindow()));
}

void TitleBarSubWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    delete m_cache;
    m_cache = new QPixmap(size());  // Create a cache with same size as the widget

    m_cache->fill(Qt::transparent);  // Create a the transparent background

     QPainter painter(m_cache); // Start painting the cache

     QColor lightBlue    (177, 177, 203, 255);
     QColor gradientStart(  0,   0,   0,   0);
     QColor gradientEnd  (  0,   0,   0, 220);

     QLinearGradient linearGrad(QPointF(0, 0), QPointF(0, height()));
     linearGrad.setColorAt(0, gradientStart);
     linearGrad.setColorAt(1, gradientEnd);

     /********** Title bar's frame **********/
     QPolygon frame;

     frame << QPoint(         20,  4)
           << QPoint(width() - 4,  4)
           << QPoint(width() - 4, 32)
           << QPoint(          4, 32)
           << QPoint(          4, 20);

     painter.setPen  (QPen  (lightBlue ));
     painter.setBrush(QBrush(linearGrad));

     painter.drawPolygon(frame);
     /***************************************/

     /********** Title bar's buttons area **********/
     QPolygon buttons;

     buttons << QPoint(width() - 50,  4)
             << QPoint(width() -  4,  4)
             << QPoint(width() -  4, 32)
             << QPoint(width() - 58, 32)
             << QPoint(width() - 58, 12);

     painter.setPen  (QPen  (lightBlue));
     painter.setBrush(QBrush(lightBlue));

     painter.drawPolygon(buttons);

     m_title.move  (28, 4);
     m_title.resize(width() - 116, 29);
     //m_close.move(100,50);
     m_close.resize(45,26);
     m_close.move(width() - 50,5);
}

void TitleBarSubWindow::paintEvent (QPaintEvent  *event)
{
    Q_UNUSED(event);
    if(m_cache != NULL)
      {
        QPainter painter(this);

        painter.drawPixmap(0, 0, *m_cache);
      }
}

void TitleBarSubWindow::updateWindowTitle(const QString &title)
{
    m_title.setText(title);
}

void TitleBarSubWindow::quitWindow()
{
    emit closeWindow();
}

