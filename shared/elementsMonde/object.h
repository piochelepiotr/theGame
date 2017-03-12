#ifndef OBJECT_H
#define OBJECT_H

#include <QString>
#include <QPixmap>

class Object
{
public:
    Object(QString const& name, int mapWidth, int mapHeight, QString const& dispName = "");
    QString const& name() const { return m_name; }
    QString const& dispName() const { return m_dispName; }
    void setDispName(QString const& dispName) { m_dispName = dispName; }
    QPixmap const& image();
    void resize(int mapWidth, int mapHeight);

private:
    QPixmap m_image;
    QPixmap m_originalImage;
    QString m_name;
    QString m_dispName;
    int m_mapWidth;
    int m_mapHeight;
    bool m_resize;
};

#endif // OBJECT_H
