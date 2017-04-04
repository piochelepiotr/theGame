#include "sortmonstres.h"
#include "ui_sortmonstres.h"

EditerMonstres::EditerMonstres(QWidget *parent, Resources *ressources) :
    QDialog(parent),
    ui(new Ui::EditerMonstres)
{
    m_nbrRessources = 0;
    m_lesRessources = ressources;
    ui->setupUi(this);
    m_creature = new EditerCreature(this,ressources);
    ui->layout_prin->addWidget(m_creature);
    connect(ui->ajoute_ressource,SIGNAL(clicked()),this,SLOT(ajouterRessource()));
    connect(m_creature,SIGNAL(s_enregistrerClasse()),this,SLOT(enregistrerMonstre()));
    connect(m_creature,SIGNAL(s_chargerClasse(QString)),this,SLOT(chargeMonstre(QString)));
    connect(m_creature,SIGNAL(s_supprimeClasse(QString)),this,SLOT(supprimeMonstre(QString)));
    connect(m_creature,SIGNAL(s_clear()),this,SLOT(clear()));
    connect(this,SIGNAL(accepted()),this,SLOT(accepter()));
    connect(m_creature,SIGNAL(s_changeClasse(QString,QString)),this,SLOT(changeMonstre(QString,QString)));
    chargeMonstres();
    exec();
}

EditerMonstres::~EditerMonstres()
{
    delete ui;
}

void EditerMonstres::ajouterRessource()
{
    ui->tab_ressources->insertRow(m_nbrRessources);
    QComboBox *ressources = new QComboBox;
    ressources->addItems(m_lesRessources->ressources());
    QDoubleSpinBox *proba = new QDoubleSpinBox;
    NumberButton *bout = new NumberButton("supprimer", m_nbrRessources);
    ui->tab_ressources->setCellWidget(m_nbrRessources, 0, ressources);
    ui->tab_ressources->setCellWidget(m_nbrRessources, 1, proba);
    ui->tab_ressources->setCellWidget(m_nbrRessources, 2, bout);
    m_nbrRessources++;
    connect(bout, SIGNAL(clique(int)), this, SLOT(ressourceSupprimme(int)));
}

void EditerMonstres::ressourceSupprimme(int num)
{
    ui->tab_ressources->removeRow(num);
    m_nbrRessources--;
    NumberButton *bout = 0;
    for(int i = num; i < m_nbrRessources; i++)
    {
        bout = (NumberButton*) ui->tab_ressources->cellWidget(i,2);
        bout->moinsnum();
    }
}

QString EditerMonstres::monstre_to_texte()
{
    QString text = m_creature->classe_to_texte() + "/MONSTRE";
    text += "/" + QString::number(ui->vieMin->value());
    text += "/" + QString::number(ui->vieMax->value());
    text += "/" + QString::number(ui->niveauMin->value());
    text += "/" + QString::number(ui->niveauMax->value());
    for(int i = 0; i < m_nbrRessources; i++)
    {
        QComboBox *ress = (QComboBox*) ui->tab_ressources->cellWidget(i,0);
        QDoubleSpinBox *prob = (QDoubleSpinBox*) ui->tab_ressources->cellWidget(i,1);
        text += "/" + ress->currentText() + "/" + QString::number(prob->value());
    }
    return text;
}

void EditerMonstres::texte_to_monstre(QString const& text)
{
    QStringList liste = text.split("MONSTRE");
    m_creature->texte_to_classe(liste[0]);
    QStringList liste2 = liste[1].split('/');
    liste2.removeAll("");
    ui->vieMin->setValue(liste2[0].toInt());
    liste2.pop_front();
    ui->vieMax->setValue(liste2[0].toInt());
    liste2.pop_front();
    ui->niveauMin->setValue(liste2[0].toInt());
    liste2.pop_front();
    ui->niveauMax->setValue(liste2[0].toInt());
    liste2.pop_front();
    int n = liste2.size();
    for(int i = 0; i < n;i+=2)
    {
        ajouterRessource();
        QComboBox *ress = (QComboBox*)ui->tab_ressources->cellWidget(i/2,0);
        QDoubleSpinBox *prob = (QDoubleSpinBox*)ui->tab_ressources->cellWidget(i/2,1);;
        ress->setCurrentIndex(ress->findText(liste2[i]));
        prob->setValue(liste2[i+1].toDouble());
    }
}

void EditerMonstres::enregistrerMonstre(QString nomAlternatif)
{
    QString texte = monstre_to_texte();
    bool existe = false;
    if(!nomAlternatif.isEmpty())
    {
        texte = nomAlternatif + "/" + texte.section("/",1);
    }
    QString nom = texte.section('/',0,0), ligne;
    QFile fichier(QString(DONNEES)+QString("monstres.txt"));
    QFile fichier2(QString(DONNEES)+QString("monstres2.txt"));
    if(fichier.open(QIODevice::ReadOnly) && fichier2.open(QIODevice::WriteOnly))
    {
        QTextStream stream1(&fichier);
        QTextStream stream2(&fichier2);

        while(!(ligne = stream1.readLine()).isNull() && !ligne.isEmpty())
        {
            if(ligne.section('/', 0,0) == nom)
            {
                stream2 << texte << endl;
                existe = true;
            }
            else
                stream2 << ligne << endl;
        }

        if(!existe)
        {
            stream2.seek(stream2.pos()-1);
            stream2 << endl << texte;
        }

        fichier.close();
        fichier2.close();

        QFile::remove(QString(DONNEES)+QString("monstres.txt"));
        QFile::rename(QString(DONNEES)+QString("monstres2.txt"), QString(DONNEES)+QString("monstres.txt"));
    }
}

void EditerMonstres::chargeMonstre(QString const& nom)
{
    QString ligne;
    QFile fichier(QString(DONNEES)+QString("monstres.txt"));
    if(fichier.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fichier);
        while(!(ligne = stream.readLine()).isNull())
        {
            if(ligne.section('/', 0,0) == nom)
            {
                texte_to_monstre(ligne);
            }
        }
        fichier.close();
    }
}

void EditerMonstres::clear()
{
    ui->tab_ressources->setRowCount(0);
    m_creature->clearClasse();
    ui->vieMin->setValue(0);
    ui->vieMax->setValue(0);
    ui->niveauMin->setValue(0);
    ui->niveauMax->setValue(0);
    m_nbrRessources = 0;
}

void EditerMonstres::supprimeMonstre(QString const& nom)
{
    clear();
    QFile fichier(QString(DONNEES)+QString("monstres.txt"));
    QFile fichier2(QString(DONNEES)+QString("monstres2.txt"));
    QString ligne;
    if(fichier.open(QIODevice::ReadOnly) && fichier2.open(QIODevice::WriteOnly))
    {
        QTextStream stream1(&fichier);
        QTextStream stream2(&fichier2);

        while(!(ligne = stream1.readLine()).isNull() && !ligne.isEmpty())
        {
            if(ligne.section('/', 0,0) != nom)
                stream2 << ligne << endl;
        }

        fichier.close();
        fichier2.close();

        QFile::remove(QString(DONNEES)+QString("monstres.txt"));
        QFile::rename(QString(DONNEES)+QString("monstres2.txt"), QString(DONNEES)+QString("monstres.txt"));
    }
}

void EditerMonstres::chargeMonstres()
{
    QStringList monstres;
    QString ligne;
    QFile fichier(QString(DONNEES)+QString("monstres.txt"));
    if(fichier.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fichier);
        while(!(ligne = stream.readLine()).isNull())
        {
            if(!ligne.isEmpty())
            {
                monstres.append(ligne.section('/',0,0));
            }
        }
        fichier.close();
    }
    m_creature->chargeClasses(monstres);
}

void EditerMonstres::accepter()
{
    if(m_creature->classeOuverte())
        enregistrerMonstre();
}

void EditerMonstres::changeMonstre(const QString &ancien, const QString &nouveau)
{
    if(!ancien.isEmpty())
        enregistrerMonstre(ancien);
    clear();
    if(!nouveau.isEmpty())
        chargeMonstre(nouveau);
}
