#include "editresources.h"
#include "ui_editresources.h"






EditerRessources::EditerRessources(QWidget *parent, Resources *resources) :
    QDialog(parent),
    ui(new Ui::EditerRessources)
{
    m_resources = resources;
    ui->setupUi(this);
    ui->select_resource->addItems(m_resources->resources());
    ui->spell->addItems(m_resources->spells());
    setWindowTitle(trUtf8("Editer les resources"));
    ui->image->setIconSize(QSize(150,150));
    connect(ui->select_resource, SIGNAL(currentIndexChanged(QString)), this, SLOT(nouvelle_selection(QString)));
    connect(this, SIGNAL(accepted()), this, SLOT(accepter()));
    connect(ui->ajouter, SIGNAL(clicked()), this, SLOT(ajoute()));
    connect(ui->supprimer, SIGNAL(clicked()), this, SLOT(supprime()));
    connect(ui->image, SIGNAL(clicked()), this, SLOT(nouvelleImage()));
    m_resourceActuelle = ui->select_resource->itemText(0);
    charge(m_resourceActuelle);
    this->exec();
}

EditerRessources::~EditerRessources()
{
    delete ui;
}

void EditerRessources::ajouteRessource(Resource *resource)
{
    m_resources->ajouteRessource(resource);
    QFile fichier("Ressources/resources.txt");
    if(fichier.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&fichier);
        stream << resource->nom() << "/" << resource->pods() << "/" << resource->description() << "/" << resource->niveau() << "/" << resource->categorie() << endl;
        fichier.close();
    }
    int endroit = 0;
    while(resource->nom().compare(ui->select_resource->itemText(endroit)) > 0)
        endroit++;
    ui->select_resource->insertItem(endroit, resource->nom());
}

void EditerRessources::ajouteEquipement(OutfitModel *equipement)
{
    ajouteRessource(equipement->getRessource());
    m_resources->ajouteEquipement(equipement);
    QFile fichier("Ressources/equipements.txt");
    if(fichier.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&fichier);
        stream << equipement->getRessource()->nom()  << "/" << equipement->getBonusForce(0) << "/" << equipement->getBonusForce(1) <<  "/" << equipement->getBonusVie(0) << "/" << equipement->getBonusVie(1) << "/" << equipement->getBonusPointsFight(0) << "/" << equipement->getBonusPointsFight(1) << endl;
        fichier.close();
    }
}

void EditerRessources::ajouteArme(WeaponModel *arme)
{
    ajouteEquipement(arme->getEquipement());
    m_resources->ajouteArme(arme);
    QFile fichier("Ressources/armes.txt");
    if(fichier.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&fichier);
        stream << arme->getEquipement()->getRessource()->nom() << '/' << arme->getSpell()->nom() << endl;
        fichier.close();
    }
}

void EditerRessources::supprimeRessource(QString const& nom)
{
    ui->select_resource->removeItem(ui->select_resource->findText(nom));
    m_resources->enleveRessource(nom);
    QFile fichier("Ressources/resources.txt");
    QFile fichier2("Ressources/resources2.txt");
    if(fichier.open(QIODevice::ReadOnly), fichier2.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&fichier);
        QTextStream stream2(&fichier2);

        QString ligne;

        while(!stream.atEnd())
        {
            ligne = stream.readLine();
            if(!ligne.isEmpty())
            {
                if(ligne.section('/', 0, 0) != nom)
                    stream2 << ligne << endl;
            }
        }

        fichier.close();
        fichier2.close();
        QFile::remove("Ressources/resources.txt");
        QFile::rename("Ressources/resources2.txt", "Ressources/resources.txt");
    }
    QFile::remove("Ressources/images/"+nom+".png");
}

void EditerRessources::supprimeEquipement(QString const& nom)
{
    m_resources->enleveEquipement(nom);
    QFile fichier("Ressources/equipements.txt");
    QFile fichier2("Ressources/equipements2.txt");
    if(fichier.open(QIODevice::ReadOnly), fichier2.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&fichier);
        QTextStream stream2(&fichier2);

        QString ligne;

        while(!stream.atEnd())
        {
            ligne = stream.readLine();
            if(!ligne.isEmpty())
            {
                if(ligne.section('/', 0, 0) != nom)
                    stream2 << ligne << endl;
            }
        }

        fichier.close();
        fichier2.close();
        QFile::remove("Ressources/equipements.txt");
        QFile::rename("Ressources/equipements2.txt", "Ressources/equipements.txt");
    }
    supprimeRessource(nom);
}

void EditerRessources::supprimeArme(QString const& nom)
{
    m_resources->enleveArme(nom);
    QFile fichier("Ressources/armes.txt");
    QFile fichier2("Ressources/armes2.txt");
    if(fichier.open(QIODevice::ReadOnly), fichier2.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&fichier);
        QTextStream stream2(&fichier2);

        QString ligne;

        while(!stream.atEnd())
        {
            ligne = stream.readLine();
            if(!ligne.isEmpty())
            {
                if(ligne.section('/', 0, 0) != nom)
                    stream2 << ligne << endl;
            }
        }

        fichier.close();
        fichier2.close();
        QFile::remove("Ressources/armes.txt");
        QFile::rename("Ressources/armes2.txt", "Ressources/armes.txt");
    }
    supprimeEquipement(nom);
}

void EditerRessources::editeRessource(Resource *resource)
{
    QFile fichier("Ressources/resources.txt");
    QFile fichier2("Ressources/resources2.txt");
    if(fichier.open(QIODevice::ReadOnly), fichier2.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&fichier);
        QTextStream stream2(&fichier2);

        QString ligne;

        while(!stream.atEnd())
        {
            ligne = stream.readLine();
            if(!ligne.isEmpty())
            {
                if(ligne.section('/', 0, 0) == resource->nom())
                    stream2 << resource->nom() << "/" << resource->pods() << "/" << resource->description() << "/" << resource->niveau() << "/" << resource->categorie() << endl;
                else
                    stream2 << ligne << endl;
            }
        }

        fichier.close();
        fichier2.close();
        QFile::remove("Ressources/resources.txt");
        QFile::rename("Ressources/resources2.txt", "Ressources/resources.txt");
    }
}

void EditerRessources::editeEquipement(OutfitModel *equipement)
{
    QFile fichier("Ressources/equipements.txt");
    QFile fichier2("Ressources/equipements2.txt");
    if(fichier.open(QIODevice::ReadOnly), fichier2.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&fichier);
        QTextStream stream2(&fichier2);

        QString ligne;

        while(!stream.atEnd())
        {
            ligne = stream.readLine();
            if(!ligne.isEmpty())
            {
                if(ligne.section('/', 0, 0) == equipement->getRessource()->nom())
                    stream2 << equipement->getRessource()->nom()  << "/" << equipement->getBonusForce(0) << "/" << equipement->getBonusForce(1) <<  "/" << equipement->getBonusVie(0) << "/" << equipement->getBonusVie(1) << "/" << equipement->getBonusPointsFight(0) << "/" << equipement->getBonusPointsFight(1) << endl;
                else
                    stream2 << ligne << endl;
            }
        }

        fichier.close();
        fichier2.close();
        QFile::remove("Ressources/equipements.txt");
        QFile::rename("Ressources/equipements2.txt", "Ressources/equipements.txt");
    }
}

void EditerRessources::editeArme(WeaponModel *arme)
{
    QFile fichier("Ressources/armes.txt");
    QFile fichier2("Ressources/armes2.txt");
    if(fichier.open(QIODevice::ReadOnly), fichier2.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&fichier);
        QTextStream stream2(&fichier2);

        QString ligne;

        while(!stream.atEnd())
        {
            ligne = stream.readLine();
            if(!ligne.isEmpty())
            {
                if(ligne.section('/', 0, 0) == arme->getEquipement()->getRessource()->nom())
                    stream2 << arme->getEquipement()->getRessource()->nom() << '/' << arme->getSpell()->nom() << endl;
                else
                    stream2 << ligne << endl;
            }
        }

        fichier.close();
        fichier2.close();
        QFile::remove("Ressources/armes.txt");
        QFile::rename("Ressources/armes2.txt", "Ressources/armes.txt");
    }
}

void EditerRessources::nouvelle_selection(QString const& nom)
{
    enregistre(m_resourceActuelle);
    m_resourceActuelle = nom;
    charge(m_resourceActuelle);
}

void EditerRessources::charge(QString const& nom)
{
    clear();
    Resource *resource = m_resources->getRessource(nom);
    OutfitModel *equipement = m_resources->getEquipement(nom);
    WeaponModel *arme = m_resources->getArme(nom);
    if(resource)
    {
        ui->categorie->setText(resource->categorie());
        ui->niveau->setValue(resource->niveau());
        ui->pods->setValue(resource->pods());
        ui->description->setPlainText(resource->description());
        ui->image->setIcon(QIcon(resource->imageg()));
    }
    if(equipement)
    {
        ui->force_min->setValue(equipement->getBonusForce(0));
        ui->force_max->setValue(equipement->getBonusForce(1));
        ui->vie_min->setValue(equipement->getBonusVie(0));
        ui->vie_max->setValue(equipement->getBonusVie(1));
        ui->PC_min->setValue(equipement->getBonusPointsFight(0));
        ui->PC_max->setValue(equipement->getBonusPointsFight(1));
        ui->partie_equipement->setEnabled(true);
    }
    if(arme)
    {
        ui->spell->setCurrentIndex(ui->spell->findText(arme->getSpell()->nom()));
        ui->spell->setEnabled(true);
    }
}

void EditerRessources::enregistre(QString const& nom)
{
    Resource *resource = m_resources->getRessource(nom);
    if(resource)
    {
        resource->setCategorie(ui->categorie->text());
        resource->setPods(ui->pods->value());
        resource->setNiveau(ui->niveau->value());
        resource->setDescription(ui->description->toPlainText());
        editeRessource(resource);

        OutfitModel *equipement = m_resources->getEquipement(nom);
        if(equipement)
        {
            equipement->setBonusForce(0, ui->force_min->value());
            equipement->setBonusForce(1, ui->force_max->value());
            equipement->setBonusVie(0, ui->vie_min->value());
            equipement->setBonusVie(1, ui->vie_max->value());
            equipement->setBonusPointFight(0, ui->PC_min->value());
            equipement->setBonusPointFight(1, ui->PC_max->value());
            editeEquipement(equipement);
        }

        WeaponModel *arme = m_resources->getArme(nom);
        if(arme)
        {
            arme->setSpell(m_resources->getSpell(ui->spell->currentText()));
        }
    }
}

void EditerRessources::clear()
{
    ui->spell->setCurrentIndex(ui->spell->findText(SORT_DEFAUT));
    ui->categorie->setText("");
    ui->niveau->setValue(0);
    ui->pods->setValue(0);
    ui->description->setPlainText("");
    ui->force_min->setValue(0);
    ui->force_max->setValue(0);
    ui->vie_min->setValue(0);
    ui->vie_max->setValue(0);
    ui->PC_min->setValue(0);
    ui->PC_max->setValue(0);
    ui->image->setIcon(QIcon());
    ui->spell->setEnabled(false);
    ui->partie_equipement->setEnabled(false);
}

void EditerRessources::accepter()
{
    enregistre(m_resourceActuelle);
}

void EditerRessources::ajoute()
{
    QString action, nom, chemin;
    QStringList actions;
    actions.push_back("nouvelle resource");
    actions.push_back("nouvel equipement");
    actions.push_back("nouvelle arme");
    bool ok;
    action = QInputDialog::getItem(this, "Nouvelle resource", "selectionnez le type de la resource", actions, 0, false, &ok);
    if(ok)
    {
        nom = QInputDialog::getText(this, "Nom", "Entrez le nom de la/du "+action, QLineEdit::Normal, "", &ok);
        chemin = QFileDialog::getOpenFileName(this, "Selectionnez l'image", QString(), "Images (*.png)");
        if(ok)
        {
            if(action == "nouvelle resource")
            {
                ajouteRessource(Resource::nouvelle(nom, chemin));
            }
            else if(action == "nouvel equipement")
            {
                ajouteEquipement(OutfitModel::nouvel(nom, chemin));
            }
            else if(action == "nouvelle arme")
            {
                ajouteArme(WeaponModel::nouvelle(nom,chemin, m_resources));
            }
        }
    }
}

void EditerRessources::supprime()
{
    QString nom = ui->select_resource->currentText();
    WeaponModel *arme = m_resources->getArme(nom);
    OutfitModel *equipement = m_resources->getEquipement(nom);
    Resource *resource = m_resources->getRessource(nom);
    if(arme)
    {
        supprimeArme(nom);
    }
    else if(equipement)
    {
        supprimeEquipement(nom);
    }
    else if(resource)
    {
        supprimeRessource(nom);
    }
}

void EditerRessources::nouvelleImage()
{
    QString chemin = QFileDialog::getOpenFileName(this, "Selectionnez l'image", QString(), "Images (*.png)");
    Resource *resource = m_resources->getRessource(m_resourceActuelle);
    if(resource && QFile::exists(chemin))
    {
        resource->setImage(chemin);
        ui->image->setIcon(QIcon(resource->imageg()));
    }
}
