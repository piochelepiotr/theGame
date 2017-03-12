#include "object.h"

#define DEFAULT_MAP_WIDTH 1920
#define DEFAULT_MAP_HEIGHT 1080

Object::Object(QString const& name, int mapWidth, int mapHeight, QString const& dispName)
{
    m_name = name;
    m_dispName = dispName;
    m_mapWidth = mapWidth;
    m_mapHeight = mapHeight;
    m_resize = true;
}

QPixmap const& Object::image()
{
    if(m_image.isNull())
    {
        m_originalImage = QPixmap("../data/objects/"+m_name);
    }
    if(m_resize)
    {
        m_image = m_originalImage.scaled((m_originalImage.width() * m_mapWidth)/DEFAULT_MAP_WIDTH, (m_originalImage.height() * m_mapHeight)/DEFAULT_MAP_HEIGHT);
        m_resize = false;
    }
    return m_image;
}

void Object::resize(int mapWidth, int mapHeight)
{
    m_mapWidth = mapWidth;
    m_mapHeight = mapHeight;
    m_resize = true;
}

