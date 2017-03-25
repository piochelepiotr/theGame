#include "editersorts.h"
#include "ui_editersorts.h"

EditerSorts::EditerSorts(QWidget *parent, Resources *ressources) :
    QDialog(parent),
    ui(new Ui::EditerSorts)
{
    ui->setupUi(this);
    m_ressources = ressources;
    connect(ui->ajoute_sort, SIGNAL(clicked()), this, SLOT(ajouterNouveau()));
    chargeSorts();
    exec();
}

EditerSorts::~EditerSorts()
{
    delete ui;
}

void EditerSorts::chargeSorts()
{
    QString ligne;
    QFile fichier(QString(DONNEES)+QString("sorts.txt"));
    if(fichier.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fichier);
        while(!(ligne = stream.readLine()).isNull())
        {
            if(!ligne.isEmpty())
            {
                ajouterNouveau(ligne.section('/', 0, 0));
            }
        }
        fichier.close();
    }
}

void EditerSorts::ajouterNouveau(QString const& lenom)
{
    QString nom = lenom;
    bool ok = true;
    if(nom.isEmpty())
    {
        while(ok && (nom.isEmpty() || m_ressources->estUnSort(nom)))
        {
            nom = QInputDialog::getText(this, trUtf8("Création d'un nouveau sort"), trUtf8("Entrez le nom du nouveau sort"), QLineEdit::Normal, "", &ok);
            if(m_ressources->estUnSort(nom))
                QMessageBox::critical(this, trUtf8("Sort déjà créé"), trUtf8("Ce sort existe déjà, choisissez un autre nom"));
        }
        if(ok)
        {
            SpellModel *sort = SpellModel::nouveau(nom);
            EditerUnSort boite(this, sort, true);
            if(ok)
                m_ressources->ajouteSort(sort);
        }
    }
    if(ok)
    {
        int num = ui->tab_sorts->rowCount();
        ui->tab_sorts->insertRow(num);
        NumberButton *boutEditer = new NumberButton(trUtf8("éditer"),num), *boutSupprimer = new NumberButton(trUtf8("supprimer"), num);
        connect(boutEditer, SIGNAL(clique(int)), this, SLOT(modifierSort(int)));
        connect(boutSupprimer, SIGNAL(clique(int)), this, SLOT(supprimeSort(int)));
        bouts_editer.push_back(boutEditer);
        bouts_supprimer.push_back(boutSupprimer);
        ui->tab_sorts->setItem(num, 0, new QTableWidgetItem(nom));
        ui->tab_sorts->item(num, 0)->setFlags(Qt::NoItemFlags);
        ui->tab_sorts->setCellWidget(num, 1, boutEditer);
        ui->tab_sorts->setCellWidget(num, 2, boutSupprimer);
    }
}

void EditerSorts::supprimeSort(int i)
{
    QString nom = ui->tab_sorts->item(i, 0)->text();
    if(QMessageBox::question(this, trUtf8("Supression d'un sort"), trUtf8("Voulez vous vraiment supprimer le sort ")+nom, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        m_ressources->enleveSort(nom);
        EditerUnSort::supprimer(nom);
        ui->tab_sorts->removeRow(i);
        for(int j = i; j < ui->tab_sorts->rowCount(); j++)
        {
            bouts_editer[j]->moinsnum();
            bouts_supprimer[j]->moinsnum();
        }
    }
}

void EditerSorts::modifierSort(int i)
{
    QString nom = ui->tab_sorts->item(i, 0)->text();
    EditerUnSort boite(this, m_ressources->getSort(nom), false);
}
