#include "editnpcs.h"
#include "ui_editnpcs.h"

Bouton2::Bouton2(const QString &texte, qint16 num) : QPushButton(texte)
{
    m_num = num;
    connect(this, SIGNAL(clicked()), this, SLOT(clique()));
}

void Bouton2::clique()
{
    emit clique(m_num);
}


EditerPnjs::EditerPnjs(QWidget *parent, Scenery *decors) :
    QDialog(parent),
    ui(new Ui::EditerPnjs)
{
    ui->setupUi(this);
    m_decors = decors;
    this->setWindowTitle(trUtf8("Editer les personnages non-joueurs"));
    chargepnjs();
    connect(ui->ajouter, SIGNAL(clicked()), this, SLOT(ajouterNouveau()));
    this->exec();
}

EditerPnjs::~EditerPnjs()
{
    delete ui;
}

void EditerPnjs::chargepnjs()
{
    QFile fichier(QString(DONNEES)+QString("pnj.txt"));
    if(fichier.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fichier);
        QString ligne;

        while(!stream.atEnd())
        {
            ligne = stream.readLine();
            if(!ligne.isEmpty())
            {
                ajouterNouveau((qint16) ligne.section('/', 0, 0).toInt());
            }
        }

        fichier.close();
    }
}

void EditerPnjs::ajouterNouveau(qint16 num)
{
    Object *objet = 0;
    bool ok = true;
    if(!num)
    {
        CreerPnj boite(this, &num, &ok, true);
        if(ok)
        {
            QString chemin;
            objet = new Object(num, "", "pnj", 1, 1, m_decors->lcase(), m_decors->hcase());
            EditerUnObjet boite(this, &ok, objet, true,m_decors->lcase(), m_decors->hcase(), &chemin);
            ajouteObjet(objet, chemin);
            m_decors->ajouteObjet(objet);
            ok = true;
        }
    }
    else
    {
        objet = m_decors->objet(num);
    }
    if(ok)
    {
        int ligne = ui->tableau->rowCount();
        ui->tableau->insertRow(ligne);

        Bouton2 *boutEditerObjet = new Bouton2(trUtf8("éditer"),num);
        Bouton2 *boutEditerDialogues = new Bouton2(trUtf8("éditer"),num);

        connect(boutEditerObjet, SIGNAL(clique(qint16)), this, SLOT(modifierpnj_objet(qint16)));
        connect(boutEditerDialogues, SIGNAL(clique(qint16)), this, SLOT(modifierpnj_dialogues(qint16)));

        bouts_spell_objet.push_back(boutEditerObjet);
        bouts_spell_dialogues.push_back(boutEditerDialogues);

        ui->tableau->setItem(ligne, 0, new QTableWidgetItem(objet->name()));
        ui->tableau->item(ligne, 0)->setFlags(Qt::NoItemFlags);
        ui->tableau->setCellWidget(ligne, 1, boutEditerObjet);
        ui->tableau->setCellWidget(ligne, 2, boutEditerDialogues);
        m_names[objet->numero()] = ui->tableau->item(ligne, 0);
    }
}

void EditerPnjs::modifierpnj_objet(qint16 num)
{
    bool ok = false, supprimer = false;
    Object *objet = m_decors->objet(num);
    EditerUnObjet boite(this, &ok, objet, false,m_decors->lcase(), m_decors->hcase(), 0, &supprimer);
    if(ok)
    {
        editObject(objet);
        m_names[num]->setText(objet->name());
    }
    else if(supprimer)
    {
        CreerPnj::supprimerPnj(objet->numero());
        supprimerObjet(m_decors, objet);
        ui->tableau->removeRow(ui->tableau->row(m_names[num]));
        //delete m_names[num];
        m_names.remove(num);
    }
}

void EditerPnjs::modifierpnj_dialogues(qint16 num)
{
    bool ok;
    CreerPnj boite(this, &num, &ok, false);
}
