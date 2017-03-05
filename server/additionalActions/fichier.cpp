#include "additionalActions/fichier.h"

bool verifi(QString const& ndc, QString const& mdp)
{
    QString texte;
    QFile fichier("joueur/"+ndc+".txt");
    if(!fichier.exists())
        return false;
    else
    {
        if(fichier.open(QFile::ReadOnly))
        {
            QTextStream stream(&fichier);
            texte = stream.readLine();
            if(texte.section('/',0,0) == mdp)
            {
                fichier.close();
                return true;
            }
            else
            {
                fichier.close();
                return false;
            }
        }
        else
            return false;
    }

}

QString chargePerso(QString const& ndc)
{
    QString perso;
    QFile fichier("joueur/"+ndc+".txt");
    if(fichier.open(QFile::ReadOnly))
    {
        QTextStream stream(&fichier);
        perso = stream.readLine();
        fichier.close();
    }
    return perso.section('/', 1);
}


void enregistrePerso(QString const& texte)
{
    QFile nfichier("joueur/"+texte.section('/',0,0)+"n.txt"), fichier("joueur/"+texte.section('/',0,0)+".txt");//si un joueur s'apelle xxxx et un autre xxxxn il y a un probleme
    QString vf;
    QStringList vieuxFichier;

    if(fichier.open(QFile::ReadOnly) && nfichier.open(QFile::WriteOnly))
    {
        QTextStream stream_vfichier(&fichier);
        QTextStream stream_nfichier(&nfichier);
        stream_vfichier >> vf;
        vieuxFichier = vf.split('/');
        stream_nfichier << vieuxFichier[0] <<'/';
        stream_nfichier << texte.section('/',1);

        fichier.close();
        nfichier.close();

        QFile::remove("joueur/"+texte.section('/',0,0)+".txt");
        QFile::rename("joueur/"+texte.section('/',0,0)+"n.txt", "joueur/"+texte.section('/',0,0)+".txt");
    }
}



