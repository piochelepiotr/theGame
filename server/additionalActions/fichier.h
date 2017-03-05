#ifndef FICHIER_H
#define FICHIER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

bool verifi(QString const& ndc, QString const& mdp);
QString litUnMot(QFile & fichier);
QString chargePerso(QString const& ndc);
void enregistrePerso(QString const& texte);

#endif // FICHIER_H
