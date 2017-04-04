#include "editspells.h"
#include "ui_editspells.h"

EditerSpells::EditerSpells(QWidget *parent, Resources *resources) :
    QDialog(parent),
    ui(new Ui::EditerSpells)
{
    ui->setupUi(this);
    m_resources = resources;
    connect(ui->ajoute_editer, SIGNAL(clicked()), this, SLOT(ajouterNouveau()));
    chargeSpells();
    exec();
}

EditerSpells::~EditerSpells()
{
    delete ui;
}

void EditerSpells::chargeSpells()
{
    QString ligne;
    QFile fichier(QString(DONNEES)+QString("editers.txt"));
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

void EditerSpells::ajouterNouveau(QString const& lenom)
{
    QString nom = lenom;
    bool ok = true;
    if(nom.isEmpty())
    {
        while(ok && (nom.isEmpty() || m_resources->estUnSpell(nom)))
        {
            nom = QInputDialog::getText(this, trUtf8("Création d'un nouveau editer"), trUtf8("Entrez le nom du nouveau editer"), QLineEdit::Normal, "", &ok);
            if(m_resources->estUnSpell(nom))
                QMessageBox::critical(this, trUtf8("Spell déjà créé"), trUtf8("Ce editer existe déjà, choisissez un autre nom"));
        }
        if(ok)
        {
            SpellModel *editer = SpellModel::nouveau(nom);
            EditerUnSpell boite(this, editer, true);
            if(ok)
                m_resources->ajouteSpell(editer);
        }
    }
    if(ok)
    {
        int num = ui->tab_editers->rowCount();
        ui->tab_editers->insertRow(num);
        NumberButton *boutEditer = new NumberButton(trUtf8("éditer"),num), *boutSupprimer = new NumberButton(trUtf8("supprimer"), num);
        connect(boutEditer, SIGNAL(clique(int)), this, SLOT(modifierSpell(int)));
        connect(boutSupprimer, SIGNAL(clique(int)), this, SLOT(supprimeSpell(int)));
        bouts_editer.push_back(boutEditer);
        bouts_supprimer.push_back(boutSupprimer);
        ui->tab_editers->setItem(num, 0, new QTableWidgetItem(nom));
        ui->tab_editers->item(num, 0)->setFlags(Qt::NoItemFlags);
        ui->tab_editers->setCellWidget(num, 1, boutEditer);
        ui->tab_editers->setCellWidget(num, 2, boutSupprimer);
    }
}

void EditerSpells::supprimeSpell(int i)
{
    QString nom = ui->tab_editers->item(i, 0)->text();
    if(QMessageBox::question(this, trUtf8("Supression d'un editer"), trUtf8("Voulez vous vraiment supprimer le editer ")+nom, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        m_resources->enleveSpell(nom);
        EditerUnSpell::supprimer(nom);
        ui->tab_editers->removeRow(i);
        for(int j = i; j < ui->tab_editers->rowCount(); j++)
        {
            bouts_editer[j]->moinsnum();
            bouts_supprimer[j]->moinsnum();
        }
    }
}

void EditerSpells::modifierSpell(int i)
{
    QString nom = ui->tab_editers->item(i, 0)->text();
    EditerUnSpell boite(this, m_resources->getSpell(nom), false);
}
