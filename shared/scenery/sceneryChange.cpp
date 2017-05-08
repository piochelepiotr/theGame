#include "scenery/sceneryChange.h"
#include "map/map.h"

void ajouteUnTheme(QString const& name)
{
    QFile fichier("../data/objets/themes.txt");

    if(fichier.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream flux(&fichier);
        flux << name << endl;
        fichier.close();
    }
}

qint16 trouveNumero()
{
    QString chemin = "../data/objets/";
    qint16 numero = 1;
    while(QFile::exists(chemin+QString::number((int)numero)+".png"))
    {
        numero++;
    }
    return numero;
}

void ajouteObjet(Object *objet, QString const& chemin_vers_image)
{
    QString ligne;
    QString texte = QString::number((int)objet->numero()) + '/' + objet->name() + '/' + objet->categorie() + '/' + QString::number(objet->propx()) + '/' + QString::number(objet->propy());
    QFile ancien_fichier("../data/objets/objets.txt");
    QFile nouveau_fichier("../data/objets/objets2.txt");

    if(ancien_fichier.open(QIODevice::ReadOnly) && nouveau_fichier.open(QIODevice::WriteOnly))
    {
        QTextStream ancien_stream(&ancien_fichier);
        QTextStream nouveau_stream(&nouveau_fichier);

        if(objet->numero() == 1)
        {
            nouveau_stream << texte << endl;
        }
        else
        {
            while(!ancien_stream.atEnd())
            {
                ligne = ancien_stream.readLine();
                nouveau_stream << ligne << endl;
                if(ligne.section('/', 0, 0).toInt() == (int)objet->numero()-1)
                    nouveau_stream << texte << endl;
            }
        }
        ancien_fichier.close();
        nouveau_fichier.close();

        QFile::remove("../data/objets/objets.txt");
        QFile::rename("../data/objets/objets2.txt", "../data/objets/objets.txt");
    }

    QFile::copy(chemin_vers_image, "../data/objets/"+QString::number((int) objet->numero())+ ".png");
}


void editAnObject(Object *objet)
{
    QString ligne, texte = QString::number((int)objet->numero()) + '/' + objet->name() + '/' + objet->categorie() + '/' + QString::number(objet->propx()) + '/' + QString::number(objet->propy());

    QFile ancien_fichier("../data/objets/objets.txt");
    QFile nouveau_fichier("../data/objets/objets2.txt");

    if(ancien_fichier.open(QIODevice::ReadOnly) && nouveau_fichier.open(QIODevice::WriteOnly))
    {
        QTextStream ancien_flux(&ancien_fichier);
        QTextStream nouveau_flux(&nouveau_fichier);

        while(!ancien_flux.atEnd())
        {
            ligne = ancien_flux.readLine();
            if(ligne.section('/', 0, 0).toInt() == (int) objet->numero())
                nouveau_flux << texte << endl;
            else
                nouveau_flux << ligne << endl;
        }



        ancien_fichier.close();
        nouveau_fichier.close();

        QFile::remove("../data/objets/objets.txt");
        QFile::rename("../data/objets/objets2.txt", "../data/objets/objets.txt");
    }
}

void supprimerObjet(Scenery *decors, Object *objet)
{
    QString ligne;

    QFile fichier_ancien("../data/objets/objets.txt");
    QFile fichier_nouveau("../data/objets/objets2.txt");

    if(fichier_ancien.open(QIODevice::ReadOnly) && fichier_nouveau.open(QIODevice::WriteOnly))
    {
        QTextStream flux_ancien(&fichier_ancien);
        QTextStream flux_nouveau(&fichier_nouveau);

        while(!flux_ancien.atEnd())
        {
            ligne = flux_ancien.readLine();
            if(!ligne.isEmpty() && ligne.section('/', 0, 0).toInt() != (int) objet->numero())
            {
                flux_nouveau << ligne << endl;
            }
        }

        fichier_ancien.close();
        fichier_nouveau.close();

        QFile::remove("../data/objets/objets.txt");
        QFile::rename("../data/objets/objets2.txt", "../data/objets/objets.txt");
    }

    Object *objets[3] [Map::mapWidth] [Map::mapHeight];
    QMap <QPoint, Gate>transpos;
    qint8 casepleines[Map::mapWidth] [Map::mapHeight];
    QString namefond;
    QPoint casescbt [2] [MAX_PAR_EQUIP];
    QMap<QString, double>monstres;
    QVector<QString>musiques;

    for(int i = 0; i < Map::worldWidth; i++)
    {
        for(int j = 0; j < Map::worldHeight; j++)
        {
            for(int z = 0; z < Map::worldDepth; z++)
            {
                if(Map::exist(i,j,z))
                {

                    //chargeMap(decors, i,j,z,objets,transpos, casepleines, &namefond, casescbt, &monstres, &musiques);
                    for(int i1 = 0; i1 < Map::mapWidth; i1++)
                    {
                        for(int j1 = 0; j1 < Map::mapHeight; j1++)
                        {
                            for(int x = 0; x < 3; x++)
                            {
                                if(objets[x] [i1] [j1] == objet)
                                {
                                    objets[x] [i1] [j1] = decors->objet(0);
                                }
                            }
                        }
                    }
                    //enregistreMap(i, j, z, objets, transpos, casepleines, namefond, casescbt, monstres, musiques);
                }
            }
        }
    }
    QString name = "../data/objets/"+QString::number((int)objet->numero())+".png";
    decors->supprimeObjet(objet);
    QFile::remove(name);
}
