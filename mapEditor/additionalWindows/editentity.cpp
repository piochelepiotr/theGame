#include "editentity.h"
#include "ui_editentity.h"

EditerCreature::EditerCreature(QWidget *parent, Resources *lesRessources) :
    QWidget(parent),
    ui(new Ui::EditerCreature)
{
    m_lesRessources = lesRessources;
    m_classeActuelle = -1;
    m_nbrSpells = 0;
    ui->setupUi(this);
    connect(ui->ajoute_classe, SIGNAL(clicked()), this, SLOT(ajouterClasse()));
    connect(ui->supprime_classe, SIGNAL(clicked()), this, SLOT(supprimerClasseActuelle()));
    connect(ui->ajoute_spell, SIGNAL(clicked()), this, SLOT(ajouterSpell()));
    connect(ui->select_classe, SIGNAL(currentIndexChanged(int)), this, SLOT(changeClasse(int)));
}

EditerCreature::~EditerCreature()
{
    delete ui;
}

void EditerCreature::changeClasse(int nouvelle)
{
    QString nameActuel = "",nameNouveau = "";
    if(m_classeActuelle != -1)
        nameActuel = ui->select_classe->itemText(m_classeActuelle);
    if(nouvelle != -1)
        nameNouveau = ui->select_classe->itemText(nouvelle);
    m_classeActuelle = nouvelle;
    emit s_changeClasse(nameActuel,nameNouveau);
}

void EditerCreature::ajouterClasse()
{
    bool ok;
    QString name = QInputDialog::getText(this, trUtf8("Nouvelle classe"), trUtf8("Entrez le name de la nouvelle classe"), QLineEdit::Normal, QString(), &ok);
    if(ok)
    {
        ui->select_classe->addItem(name);
    }
}

void EditerCreature::supprimerClasseActuelle()
{
    if(m_classeActuelle != -1)
    {
        QString name = ui->select_classe->itemText(m_classeActuelle);
        if(QMessageBox::question(this, trUtf8("Supression d'une classe"), trUtf8("Voulez vous vraiment supprimer la classe ")+name, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            m_classeActuelle = -1;
            emit s_supprimeClasse(name);
            ui->select_classe->removeItem(ui->select_classe->currentIndex());
        }
    }
}

void EditerCreature::ajouterSpell()
{
    if(m_classeActuelle != -1)
    {
        ui->tab_spells->insertRow(m_nbrSpells);
        NumberButton *bout = new NumberButton("supprimer", m_nbrSpells);
        QComboBox *spells = new QComboBox();
        spells->addItems(m_lesRessources->spells());
        ui->tab_spells->setCellWidget(m_nbrSpells, 1, bout);
        ui->tab_spells->setCellWidget(m_nbrSpells, 0, spells);
        m_nbrSpells++;
        connect(bout, SIGNAL(clique(int)), this, SLOT(supprimerSpell(int)));
    }
}

void EditerCreature::supprimerSpell(int num)
{
    ui->tab_spells->removeRow(num);
    m_nbrSpells--;
    NumberButton *bout = 0;
    for(int i = num; i < m_nbrSpells; i++)
    {
        bout = (NumberButton*) ui->tab_spells->cellWidget(i,1);
        bout->moinsnum();
    }
}

void EditerCreature::clearClasse()
{
    ui->tab_spells->setRowCount(0);
    m_nbrSpells = 0;
    ui->propx->setValue(0);
    ui->propy->setValue(0);
}

QString EditerCreature::classe_to_texte()
{
    QString texte = ui->select_classe->itemText(m_classeActuelle);
    texte += '/';
    texte += QString::number(ui->propx->value()) + '/' + QString::number(ui->propy->value());
    for(int i = 0; i < m_nbrSpells; i++)
    {
        QComboBox *spell = (QComboBox*) ui->tab_spells->cellWidget(i,0);
        texte += '/' + spell->currentText();
    }
    return texte;
}

void EditerCreature::texte_to_classe(QString const& texte)
{
    QStringList liste = texte.split('/');
    liste.pop_front();//on enlève le name
    ui->propx->setValue(liste[0].toDouble());
    liste.pop_front();
    ui->propy->setValue(liste[0].toDouble());
    liste.pop_front();
    liste.removeAll("");
    while(liste.size() > 0)
    {
        ajouterSpell();
        QComboBox *spell = (QComboBox*) ui->tab_spells->cellWidget(m_nbrSpells-1,0);
        spell->setCurrentIndex(spell->findText(liste[0]));
        liste.pop_front();
    }
}

void EditerCreature::chargeClasses(QStringList classes)
{
    ui->select_classe->addItems(classes);
}
