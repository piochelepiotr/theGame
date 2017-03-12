#include "additionalActions/actionObjets.h"


bool operator<(QPoint const &a, QPoint const& b)
{
    if(a.y() < b.y())
        return true;
    else if(a.y() > b.y())
        return false;
    if(a.x() < b.x())
        return true;
    else
        return false;
}

void enregistreMap(int cooX, int cooY,int cooZ, Objet *objets[3] [NBR_CASES_L] [NBR_CASES_H], QMap <QPoint, Transporteur> const& transpos, qint8 casepleines[NBR_CASES_L] [NBR_CASES_H], QString fond, QPoint casescbt[2] [MAX_PAR_EQUIP], QMap<QString, double>monstres, QVector<QString>musiques, int undo)
{
    QFile fichier;
    if(undo != -1)
        fichier.setFileName("../data/maps/undo/"+QString::number(undo)+".bin");
    else
        fichier.setFileName("../data/maps/["+QString::number(cooX)+";"+QString::number(cooY)+";"+QString::number(cooZ)+"].bin");

    if(fichier.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&fichier);
        for(int i = 0; i < NBR_CASES_L; i++)
        {
            for(int j = 0; j < NBR_CASES_H; j++)
            {
                stream << objets[0] [i] [j]->numero() << objets[1] [i] [j]->numero() << objets[2] [i] [j]->numero();
            }
        }

        for(int i = 0; i < NBR_CASES_L; i++)
        {
            for(int j = 0; j < NBR_CASES_H; j++)
            {
                stream << casepleines[i] [j];
            }
        }

        for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < MAX_PAR_EQUIP; j++)
            {
                stream << (qint8) casescbt[i] [j].x() << (qint8) casescbt[i] [j].y();
            }
        }

        //et la chaine QString

        QString reste;

        reste += fond + '/';

        for(int i = 0; i < musiques.size(); i++)
        {
            reste += musiques[i] + '/';
        }

        reste += "FINMUSIQUES/";

        for(QMap<QString, double>::iterator it = monstres.begin(); it != monstres.end(); it++)
        {
            reste += it.key() + '/' + QString::number(it.value()) + '/';
        }

        reste += "FINMONSTRES/";

        for(QMap<QPoint, Transporteur>::const_iterator it = transpos.begin(); it != transpos.end(); it++)
        {
            reste += it.value().getNom();
            reste += '/';
            reste += it.value().getNomArr();
            reste += '/';
            reste += QString::number(it.value().getMapX());
            reste += '/';
            reste += QString::number(it.value().getMapY());
            reste += '/';
            reste += QString::number(it.value().getMapZ());
            reste += '/';
            reste += QString::number((int)it.value().getLargage());
            reste += '/';
            reste += QString::number(it.key().x());
            reste += '/';
            reste += QString::number(it.key().y());
            reste += '/';
        }
        stream << reste;
        fichier.close();
    }
}


bool chargeMap(Decors *decors, int cooX, int cooY,int cooZ, Objet *objets[3] [NBR_CASES_L] [NBR_CASES_H], QMap <QPoint, Transporteur> & transpos, qint8 casepleines[NBR_CASES_L] [NBR_CASES_H], QString *fond, QPoint casescbt[2] [MAX_PAR_EQUIP], QMap<QString, double> *monstres, QVector<QString>*musiques, int undo)
{
    QFile fichier;
    if(undo != -1)
        fichier.setFileName("../data/maps/undo/"+QString::number(undo-1)+".bin");
    else
        fichier.setFileName("../data/maps/["+QString::number(cooX)+";"+QString::number(cooY)+";"+QString::number(cooZ)+"].bin");
    if(!fichier.exists())
        return false;

    if(fichier.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&fichier);
        qint16 num;
        qint8 num2;

        for(int i = 0; i < NBR_CASES_L; i++)
        {
            for(int j = 0; j < NBR_CASES_H; j++)
            {
                for(int x = 0; x < 3; x++)
                {
                    stream >> num;
                    objets[x] [i] [j] = decors->objet(num);
                }
            }
        }

        for(int i = 0; i < NBR_CASES_L; i++)
        {
            for(int j = 0; j < NBR_CASES_H; j++)
            {
                stream >> casepleines[i] [j];
            }
        }

        QPoint p;

        for(int i = 0; i < 2; i++)
        {
            for(int j = 0; j < MAX_PAR_EQUIP; j++)
            {
                stream >> num2;
                p.setX((int)num2);
                stream >> num2;
                p.setY((int)num2);
                casescbt[i] [j] = p;
            }
        }

        QString texte;
        stream >> texte;

        fichier.close();

        QStringList liste = texte.split("/");

        *fond = liste.front();
        liste.pop_front();

        while(liste[0] != "FINMUSIQUES")
        {
            musiques->push_back(liste[0]);
            liste.pop_front();
        }

        liste.pop_front();

        while(liste[0] != "FINMONSTRES")
        {
            (*monstres)[liste[0]] = liste[1].toDouble();
            liste.pop_front();
            liste.pop_front();
        }

        if(liste.size() > 0)
            liste.pop_front();

        for(int i = 0; i < liste.size()-2; i+=8)
        {
            transpos[QPoint(liste[i+6].toInt(), liste[i+7].toInt())] = Transporteur(liste[i], liste[i+1], liste[i+2].toInt(), liste[i+3].toInt(), liste[i+4].toInt(), (Dir)liste[i+5].toInt(), liste[i+6].toInt(), liste[i+7].toInt());
        }

        if(undo != -1)
            QFile::remove("maps/undo/"+QString::number(undo)+".bin");

        return true;
    }
    else
        return false;
}


void ajouteUnTheme(QString const& nom)
{
    QFile fichier("../data/objets/themes.txt");

    if(fichier.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream flux(&fichier);
        flux << nom << endl;
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

void ajouteObjet(Objet *objet, QString const& chemin_vers_image)
{
    QString ligne;
    QString texte = QString::number((int)objet->numero()) + '/' + objet->nom() + '/' + objet->categorie() + '/' + QString::number(objet->propx()) + '/' + QString::number(objet->propy());
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

    QFile::copy(chemin_vers_image, "objets/"+QString::number((int) objet->numero())+ ".png");
}


void editerUnObjet(Objet *objet)
{
    QString ligne, texte = QString::number((int)objet->numero()) + '/' + objet->nom() + '/' + objet->categorie() + '/' + QString::number(objet->propx()) + '/' + QString::number(objet->propy());

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

void supprimerObjet(Decors *decors, Objet *objet)
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

    Objet *objets[3] [NBR_CASES_L] [NBR_CASES_H];
    QMap <QPoint, Transporteur>transpos;
    qint8 casepleines[NBR_CASES_L] [NBR_CASES_H];
    QString nomfond;
    QPoint casescbt [2] [MAX_PAR_EQUIP];
    QMap<QString, double>monstres;
    QVector<QString>musiques;

    for(int i = 0; i < NBR_DE_MAPS_X; i++)
    {
        for(int j = 0; j < NBR_DE_MAPS_Y; j++)
        {
            for(int z = 0; z < NBR_DE_MAPS_Z; z++)
            {
                if(mapexiste(i,j,z))
                {
                    chargeMap(decors, i,j,z,objets,transpos, casepleines, &nomfond, casescbt, &monstres, &musiques);
                    for(int i1 = 0; i1 < NBR_CASES_L; i1++)
                    {
                        for(int j1 = 0; j1 < NBR_CASES_H; j1++)
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
                    enregistreMap(i, j, z, objets, transpos, casepleines, nomfond, casescbt, monstres, musiques);
                }
            }
        }
    }
    QString nom = "../data/objets/"+QString::number((int)objet->numero())+".png";
    decors->supprimeObjet(objet);
    QFile::remove(nom);
}

bool mapexiste(int x, int y, int z)
{
    if(x < 0 || y < 0 || z < 0 || x > NBR_DE_MAPS_X-1 || y > NBR_DE_MAPS_Y-1 || z > NBR_DE_MAPS_Z-1)
        return false;
    QFile fichier("../data/maps/["+QString::number(x)+";"+QString::number(y)+";"+QString::number(z)+"].bin");
    return fichier.exists();
}
