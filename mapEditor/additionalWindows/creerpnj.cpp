#include "creerpnj.h"
#include "ui_creerpnj.h"

Bout::Bout(QString const& texte, const QString &nom) : QPushButton(texte)
{
    m_nom = nom;
}

void Bout::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        emit ajoute(m_nom);
    else if(event->button() == Qt::RightButton)
        emit edite(m_nom);
    else if(event->button() == Qt::MiddleButton)
        emit detruit(m_nom);
}

CreerPnj::CreerPnj(QWidget *parent, qint16 *num, bool *ok, bool creation) : QDialog(parent),
    ui(new Ui::CreerPnj)
{
    ui->setupUi(this);
    connect(this, SIGNAL(accepted()), this, SLOT(accepter()));

    m_creation = creation;
    m_ok = ok;
    *m_ok = false;
    m_num = num;
    if(creation)
        *m_num = trouveNumero();
    m_repliques["0"] = new Bout("pas de nom", "0");
    m_enfrepliques["0"] = new QVBoxLayout();
    ui->lay_0->addWidget(m_repliques["0"]);
    ui->lay_0->addLayout(m_enfrepliques["0"]);
    connect(m_repliques["0"], SIGNAL(ajoute(QString)), this, SLOT(boutclique(QString)));
    connect(m_repliques["0"], SIGNAL(edite(QString)), this, SLOT(editerBouton(QString)));
    this->setWindowTitle(trUtf8("éditer un personnage non joueur"));

    if(!creation)
        chargerPnj();

    this->exec();
}

CreerPnj::~CreerPnj()
{
    delete ui;
}

void CreerPnj::accepter()
{
    *m_ok = true;
    QFile fichier(QString(DONNEES)+QString("pnj.txt"));

    if(m_creation)
    {
        if(fichier.open(QIODevice::Append))
        {
            QTextStream stream(&fichier);
            stream << enString();
            stream << '\n';
            fichier.close();
        }
    }
    else
    {
        QFile fichier2(QString(DONNEES)+QString("pnj2.txt"));
        if(fichier.open(QIODevice::ReadOnly) && fichier2.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&fichier);
            QTextStream stream2(&fichier2);
            QString ligne;
            while(!stream.atEnd())
            {
                ligne = stream.readLine();
                if(!ligne.isEmpty())
                {
                    if(ligne.section('/', 0, 0).toInt() == (int) (*m_num))
                        stream2 << enString() << endl;
                    else
                        stream2 << ligne << endl;
                }
            }
            fichier.close();
            fichier2.close();
            QFile::remove(QString(DONNEES)+QString("pnj.txt"));
            QFile::rename(QString(DONNEES)+QString("pnj2.txt"),QString(DONNEES)+QString("pnj.txt"));
        }
    }
}

void CreerPnj::editerBouton(QString nom)
{
    bool ok;
    QString texte = QInputDialog::getText(this, trUtf8("nouveau dialogue"), trUtf8("nouvelle réplique:"), QLineEdit::Normal, QString(), &ok);
    if(ok)
    {
        m_repliques[nom]->setText(texte);
    }
}

void CreerPnj::boutclique(QString nom, QString texte)
{
    bool ok = true;
    if(texte == "-1")
        texte = QInputDialog::getText(this, "nouveau dialogue", "parole suivante :", QLineEdit::Normal, QString(), &ok);
    if(ok)
    {
        QString new_nom = nom + '_' + QString::number(m_enfrepliques[nom]->children().size());
        Bout *bout = new Bout(texte, new_nom);
        QHBoxLayout *layh = new QHBoxLayout;
        QVBoxLayout *layv = new QVBoxLayout;
        layh->addWidget(bout);
        layh->addLayout(layv);
        m_enfrepliques[nom]->addLayout(layh);
        m_enfrepliques[new_nom] = layv;
        m_repliques[new_nom] = bout;
        m_layrepliques[new_nom] = layh;
        connect(bout, SIGNAL(ajoute(QString)), this, SLOT(boutclique(QString)));
        connect(bout, SIGNAL(edite(QString)), this, SLOT(editerBouton(QString)));
        connect(bout, SIGNAL(detruit(QString)), this, SLOT(effaceReplique(QString)));
    }
}

QString CreerPnj::ecritReplique(QString const& nom)
{
    QString texte = m_repliques[nom]->text();
    QString sous_nom;
    texte += '/';
    int i;
    for(i = 0; i < m_enfrepliques[nom]->children().size(); i++)
    {
        sous_nom = nom + '_' + QString::number(i);
        texte += ecritReplique(sous_nom);
    }
    if(i > 0)
        texte += "fin/";
    return texte;
}

QString CreerPnj::enString()
{
    QString texte;
    texte += QString::number((int)(*m_num));
    texte += '/';
    texte += ecritReplique("0");
    return texte;
}

void CreerPnj::effaceReplique(QString nom)
{
    if(nom == "0")
        return;
    for(int i = 0; i < m_enfrepliques[nom]->children().size(); i++)
    {
        effaceReplique(nom+'_'+QString::number(i));
    }
    m_repliques[nom]->deleteLater();
    m_enfrepliques[nom]->deleteLater();
    m_layrepliques[nom]->deleteLater();
}

void CreerPnj::ajoutePiste(QString nom, QString *donnees)
{
    boutclique(nom.mid(0, nom.size()-2) ,donnees->section('/',0,0));
    boutclique(nom, donnees->section('/', 1, 1));
    nom += "_0";
    *donnees = donnees->section('/', 2);
    ajouteReponses(nom, donnees);
}

void CreerPnj::ajouteReponses(QString const& nom, QString *donnees)
{
    int i = 0;
    while(donnees->section('/',0,0) != "fin")
    {
        ajoutePiste(nom+'_'+QString::number(i), donnees);
        i++;
    }
    *donnees = donnees->section('/', 1);
}

void CreerPnj::chargerPnj()
{
    QFile fichier(QString(DONNEES)+QString("pnj.txt"));
    if(fichier.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fichier);
        QString pnj;
        while(!stream.atEnd())
        {
            pnj = stream.readLine();
            if(pnj.section('/', 0, 0).toInt() == (int)(*m_num))
            {
                m_repliques["0"]->setText(pnj.section('/',1,1));
                QString reste = pnj.section('/', 2);
                ajouteReponses("0", &reste);
                return;
            }
        }
        fichier.close();
    }
}

void CreerPnj::supprimerPnj(qint16 numero)
{
    QFile fichier(QString(DONNEES)+QString("pnj.txt"));
    QFile fichier2(QString(DONNEES)+QString("pnj2.txt"));
    if(fichier.open(QIODevice::ReadOnly) && fichier2.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&fichier);
        QTextStream stream2(&fichier2);
        QString pnj;
        while(!stream.atEnd())
        {
            pnj = stream.readLine();
            if(!pnj.isEmpty() && pnj.section('/', 0, 0).toInt() != (int)numero)
                stream2 << pnj << endl;
        }
        fichier.close();
        fichier2.close();

        QFile::remove(QString(DONNEES)+QString("pnj.txt"));
        QFile::rename(QString(DONNEES)+QString("pnj2.txt"),QString(DONNEES)+QString("pnj.txt"));
    }
}
