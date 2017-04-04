#ifndef BOUTONIMG_H
#define BOUTONIMG_H

#include <QPushButton>

class ImageButtonString : public QPushButton
{
    Q_OBJECT

public:
    ImageButtonString(QString name,QString const& cheminImage);

public slots:
    void clique();
signals:
    void clique(QString name);

private:
    QString m_name;
};

#endif // BOUTONIMG_H
