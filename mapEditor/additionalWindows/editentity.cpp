#include "editentity.h"
#include "ui_editentity.h"

EditerCreature::EditerCreature(QWidget *parent, Resources *lesRessources) :
    QWidget(parent),
    ui(new Ui::EditerCreature)
{
    m_lesRessources = lesRessources;
    m_classeActuelle = -1;
    m_nbrSorts = 0;
    ui->setupUi(this);
    connect(ui->ajoute_classe, SIGNAL(clicked()), this, SLOT(ajouterClasse()));
    connect(ui->supprime_classe, SIGNAL(clicked()), this, SLOT(supprimerClasseActuelle()));
    connect(ui->ajoute_sort, SIGNAL(clicked()), this, SLOT(ajouterSort()));
    connect(ui->select_classe, SIGNAL(currentIndexChanged(int)), this, SLOT(changeClasse(int)));
}

EditerCreature::~EditerCreature()
{
    delete ui;
}

void EditerCreature::changeClasse(int nouvelle)
{
    QString nomActuel = "",nomNouveau = "";
    if(m_classeActuelle != -1)
        nomActuel = ui->select_classe->itemText(m_classeActuelle);
    if(nouvelle != -1)
        nomNouveau = ui->select_classe->itemText(nouvelle);
    m_classeActuelle = nouvelle;
    emit s_changeClasse(nomActuel,nomNouveau);
}

void EditerCreature::ajouterClasse()
{
    bool ok;
    QString nom = QInputDialog::getText(this, trUtf8("Nouvelle classe"), trUtf8("Entrez le nom de la nouvelle classe"), QLineEdit::Normal, QString(), &ok);
    if(ok)
    {
        ui->select_classe->addItem(nom);
    }
}

void EditerCreature::supprimerClasseActuelle()
{
    if(m_classeActuelle != -1)
    {
        QString nom = ui->select_classe->itemText(m_classeActuelle);
        if(QMessageBox::question(this, trUtf8("Supression d'une classe"), trUtf8("Voulez vous vraiment supprimer la classe ")+nom, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            m_classeActuelle = -1;
            emit s_supprimeClasse(nom);
            ui->select_classe->removeItem(ui->select_classe->currentIndex());
        }
    }
}

void EditerCreature::ajouterSort()
{
    if(m_classeActuelle != -1)
    {
        ui->tab_sorts->insertRow(m_nbrSorts);
        NumberButton *bout = new NumberButton("supprimer", m_nbrSorts);
        QComboBox *sorts = new QComboBox();
        sorts->addItems(m_lesRessources->sorts());
        ui->tab_sorts->setCellWidget(m_nbrSorts, 1, bout);
        ui->tab_sorts->setCellWidget(m_nbrSorts, 0, sorts);
        m_nbrSorts++;
        connect(bout, SIGNAL(clique(int)), this, SLOT(supprimerSort(int)));
    }
}

void EditerCreature::supprimerSort(int num)
{
    ui->tab_sorts->removeRow(num);
    m_nbrSorts--;
    NumberButton *bout = 0;
    for(int i = num; i < m_nbrSorts; i++)
    {
        bout = (NumberButton*) ui->tab_sorts->cellWidget(i,1);
        bout->moinsnum();
    }
}

void EditerCreature::clearClasse()
{
    ui->tab_sorts->setRowCount(0);
    m_nbrSorts = 0;
    ui->propx->setValue(0);
    ui->propy->setValue(0);
}

QString EditerCreature::classe_to_texte()
{
    QString texte = ui->select_classe->itemText(m_classeActuelle);
    texte += '/';
    texte += QString::number(ui->propx->value()) + '/' + QString::number(ui->propy->value());
    for(int i = 0; i < m_nbrSorts; i++)
    {
        QComboBox *sort = (QComboBox*) ui->tab_sorts->cellWidget(i,0);
        texte += '/' + sort->currentText();
    }
    return texte;
}

void EditerCreature::texte_to_classe(QString const& texte)
{
    QStringList liste = texte.split('/');
    liste.pop_front();//on enlève le nom
    ui->propx->setValue(liste[0].toDouble());
    liste.pop_front();
    ui->propy->setValue(liste[0].toDouble());
    liste.pop_front();
    liste.removeAll("");
    while(liste.size() > 0)
    {
        ajouterSort();
        QComboBox *sort = (QComboBox*) ui->tab_sorts->cellWidget(m_nbrSorts-1,0);
        sort->setCurrentIndex(sort->findText(liste[0]));
        liste.pop_front();
    }
}

void EditerCreature::chargeClasses(QStringList classes)
{
    ui->select_classe->addItems(classes);
}
