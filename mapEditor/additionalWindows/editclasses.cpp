#include "editclasses.h"
#include "ui_editclasses.h"

EditerClasses::EditerClasses(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditerClasses)
{
    m_classeActuelle = -1;
    m_nbrSorts = 0;
    ui->setupUi(this);
    connect(ui->ajoute_classe, SIGNAL(clicked()), this, SLOT(ajouterClasse()));
    connect(ui->supprime_classe, SIGNAL(clicked()), this, SLOT(supprimerClasseActuelle()));
    connect(ui->ajoute_sort, SIGNAL(clicked()), this, SLOT(ajouterSort()));
    connect(this, SIGNAL(accepted()), this, SLOT(accepter()));
    connect(ui->select_classe, SIGNAL(currentIndexChanged(int)), this, SLOT(changeClasse(int)));
    chargeClasses();
    this->setWindowTitle(trUtf8("Editer les classes"));
    exec();
}

EditerClasses::~EditerClasses()
{
    delete ui;
}

void EditerClasses::changeClasse(int nouvelle)
{
    if(m_classeActuelle != -1 && m_classeActuelle != -2)
    {
        enregistrerClasse(m_classeActuelle);
    }
    if(m_classeActuelle != -2)
        clearClasse();
    m_classeActuelle = nouvelle;
    if(m_classeActuelle != -1)
    {
        chargeClasseActuelle();
    }
}

void EditerClasses::ajouterClasse()
{
    bool ok;
    QString nom = QInputDialog::getText(this, trUtf8("Nouvelle classe"), trUtf8("Entrez le nom de la nouvelle classe"), QLineEdit::Normal, QString(), &ok);
    if(ok)
    {
        ui->select_classe->addItem(nom);
    }
}

void EditerClasses::supprimerClasseActuelle()
{
    if(m_classeActuelle != -1)
    {
        QString nom = ui->select_classe->itemText(m_classeActuelle), ligne;
        if(QMessageBox::question(this, trUtf8("Supression d'une classe"), trUtf8("Voulez vous vraiment supprimer la classe ")+nom, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            enregistrerClasse(m_classeActuelle);
            m_classeActuelle = -1;
            clearClasse();
            ui->select_classe->removeItem(ui->select_classe->currentIndex());
            QFile fichier(QString(DONNEES)+QString("classes.txt"));
            QFile fichier2(QString(DONNEES)+QString("classes2.txt"));
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

                QFile::remove(QString(DONNEES)+QString("classes.txt"));
                QFile::rename(QString(DONNEES)+QString("classes2.txt"), QString(DONNEES)+QString("classes.txt"));
            }
        }
    }
}

void EditerClasses::chargeClasseActuelle()
{
    QString nom = ui->select_classe->itemText(m_classeActuelle), ligne;
    QFile fichier(QString(DONNEES)+QString("classes.txt"));
    if(fichier.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fichier);
        while(!(ligne = stream.readLine()).isNull())
        {
            if(ligne.section('/', 0,0) == nom)
            {
                texte_to_classe(ligne);
            }
        }
        fichier.close();
    }
}

void EditerClasses::ajouterSort()
{
    if(m_classeActuelle != -1)
    {
        ui->tab_sorts->insertRow(m_nbrSorts);
        NumberButton *bout = new NumberButton("supprimer", m_nbrSorts);
        ui->tab_sorts->setCellWidget(m_nbrSorts, 1, bout);
        ui->tab_sorts->setItem(m_nbrSorts, 0, new QTableWidgetItem(""));
        m_boutonsSorts.push_back(bout);
        m_nbrSorts++;
        connect(bout, SIGNAL(clique(int)), this, SLOT(supprimerSort(int)));
    }
}

void EditerClasses::supprimerSort(int num)
{
    ui->tab_sorts->removeRow(num);
    m_boutonsSorts.remove(num);
    m_nbrSorts--;
    for(int i = num; i < m_nbrSorts; i++)
    {
        m_boutonsSorts[i]->moinsnum();
    }
}

void EditerClasses::enregistrerClasse(int classe)
{
    bool existe = false;
    QString nom = ui->select_classe->itemText(classe), ligne, texte;
    texte = classe_to_texte();
    QFile fichier(QString(DONNEES)+QString("classes.txt"));
    QFile fichier2(QString(DONNEES)+QString("classes2.txt"));
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

        QFile::remove(QString(DONNEES)+QString("classes.txt"));
        QFile::rename(QString(DONNEES)+QString("classes2.txt"), QString(DONNEES)+QString("classes.txt"));
    }
}

void EditerClasses::clearClasse()
{
    ui->arme->setText("");
    ui->metier->setText("");
    ui->tab_sorts->setRowCount(0);
    m_nbrSorts = 0;
}

QString EditerClasses::classe_to_texte()
{
    QString texte = ui->select_classe->itemText(m_classeActuelle);
    texte += '/';
    texte += ui->arme->text() + '/' + ui->metier->text() + '/' + QString::number(ui->propx->value()) + '/' + QString::number(ui->propy->value());
    for(int i = 0; i < m_nbrSorts; i++)
    {
        texte += '/' + ui->tab_sorts->item(i, 0)->text();
    }
    return texte;
}

void EditerClasses::texte_to_classe(QString const& texte)
{
    QStringList liste = texte.split('/');
    liste.pop_front();//le texte est sans le nom
    ui->arme->setText(liste[0]);
    liste.pop_front();
    ui->metier->setText(liste[0]);
    liste.pop_front();
    ui->propx->setValue(liste[0].toDouble());
    liste.pop_front();
    ui->propy->setValue(liste[0].toDouble());
    liste.pop_front();
    while(liste.size() > 0)
    {
        ajouterSort();
        ui->tab_sorts->item(m_nbrSorts-1, 0)->setText(liste[0]);
        liste.pop_front();
    }
}

void EditerClasses::accepter()
{
    enregistrerClasse(m_classeActuelle);
}

void EditerClasses::chargeClasses()
{
    QString ligne;
    QFile fichier(QString(DONNEES)+QString("classes.txt"));
    if(fichier.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fichier);
        m_classeActuelle = -2;
        while(!(ligne = stream.readLine()).isNull())
        {
            if(!ligne.isEmpty())
            {
                ui->select_classe->addItem(ligne.section('/', 0, 0));
            }
        }
        if(m_classeActuelle == -2)
        {
            m_classeActuelle = -1;
        }
        fichier.close();
    }
}

