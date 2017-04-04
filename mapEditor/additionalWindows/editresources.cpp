#include "editresources.h"
#include "ui_editresources.h"






EditerRessources::EditerRessources(QWidget *parent, Resources *ressources) :
    QDialog(parent),
    ui(new Ui::EditerRessources)
{
    m_ressources = ressources;
    ui->setupUi(this);
    ui->select_ressource->addItems(m_ressources->ressources());
    ui->sort->addItems(m_ressources->sorts());
    setWindowTitle(trUtf8("Editer les ressources"));
    ui->image->setIconSize(QSize(150,150));
    connect(ui->select_ressource, SIGNAL(currentIndexChanged(QString)), this, SLOT(nouvelle_selection(QString)));
    connect(this, SIGNAL(accepted()), this, SLOT(accepter()));
    connect(ui->ajouter, SIGNAL(clicked()), this, SLOT(ajoute()));
    connect(ui->supprimer, SIGNAL(clicked()), this, SLOT(supprime()));
    connect(ui->image, SIGNAL(clicked()), this, SLOT(nouvelleImage()));
    m_ressourceActuelle = ui->select_ressource->itemText(0);
    charge(m_ressourceActuelle);
    this->exec();
}

EditerRessources::~EditerRessources()
{
    delete ui;
}

void EditerRessources::ajouteRessource(Resource *ressource)
{
    m_ressources->ajouteRessource(ressource);
    QFile fichier("Ressources/ressources.txt");
    if(fichier.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&fichier);
        stream << ressource->nom() << "/" << ressource->pods() << "/" << ressource->description() << "/" << ressource->niveau() << "/" << ressource->categorie() << endl;
        fichier.close();
    }
    int endroit = 0;
    while(ressource->nom().compare(ui->select_ressource->itemText(endroit)) > 0)
        endroit++;
    ui->select_ressource->insertItem(endroit, ressource->nom());
}

void EditerRessources::ajouteEquipement(OutfitModel *equipement)
{
    ajouteRessource(equipement->getRessource());
    m_ressources->ajouteEquipement(equipement);
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
    m_ressources->ajouteArme(arme);
    QFile fichier("Ressources/armes.txt");
    if(fichier.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream stream(&fichier);
        stream << arme->getEquipement()->getRessource()->nom() << '/' << arme->getSort()->nom() << endl;
        fichier.close();
    }
}

void EditerRessources::supprimeRessource(QString const& nom)
{
    ui->select_ressource->removeItem(ui->select_ressource->findText(nom));
    m_ressources->enleveRessource(nom);
    QFile fichier("Ressources/ressources.txt");
    QFile fichier2("Ressources/ressources2.txt");
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
        QFile::remove("Ressources/ressources.txt");
        QFile::rename("Ressources/ressources2.txt", "Ressources/ressources.txt");
    }
    QFile::remove("Ressources/images/"+nom+".png");
}

void EditerRessources::supprimeEquipement(QString const& nom)
{
    m_ressources->enleveEquipement(nom);
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
    m_ressources->enleveArme(nom);
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

void EditerRessources::editeRessource(Resource *ressource)
{
    QFile fichier("Ressources/ressources.txt");
    QFile fichier2("Ressources/ressources2.txt");
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
                if(ligne.section('/', 0, 0) == ressource->nom())
                    stream2 << ressource->nom() << "/" << ressource->pods() << "/" << ressource->description() << "/" << ressource->niveau() << "/" << ressource->categorie() << endl;
                else
                    stream2 << ligne << endl;
            }
        }

        fichier.close();
        fichier2.close();
        QFile::remove("Ressources/ressources.txt");
        QFile::rename("Ressources/ressources2.txt", "Ressources/ressources.txt");
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
                    stream2 << arme->getEquipement()->getRessource()->nom() << '/' << arme->getSort()->nom() << endl;
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
    enregistre(m_ressourceActuelle);
    m_ressourceActuelle = nom;
    charge(m_ressourceActuelle);
}

void EditerRessources::charge(QString const& nom)
{
    clear();
    Resource *ressource = m_ressources->getRessource(nom);
    OutfitModel *equipement = m_ressources->getEquipement(nom);
    WeaponModel *arme = m_ressources->getArme(nom);
    if(ressource)
    {
        ui->categorie->setText(ressource->categorie());
        ui->niveau->setValue(ressource->niveau());
        ui->pods->setValue(ressource->pods());
        ui->description->setPlainText(ressource->description());
        ui->image->setIcon(QIcon(ressource->imageg()));
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
        ui->sort->setCurrentIndex(ui->sort->findText(arme->getSort()->nom()));
        ui->sort->setEnabled(true);
    }
}

void EditerRessources::enregistre(QString const& nom)
{
    Resource *ressource = m_ressources->getRessource(nom);
    if(ressource)
    {
        ressource->setCategorie(ui->categorie->text());
        ressource->setPods(ui->pods->value());
        ressource->setNiveau(ui->niveau->value());
        ressource->setDescription(ui->description->toPlainText());
        editeRessource(ressource);

        OutfitModel *equipement = m_ressources->getEquipement(nom);
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

        WeaponModel *arme = m_ressources->getArme(nom);
        if(arme)
        {
            arme->setSort(m_ressources->getSort(ui->sort->currentText()));
        }
    }
}

void EditerRessources::clear()
{
    ui->sort->setCurrentIndex(ui->sort->findText(SORT_DEFAUT));
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
    ui->sort->setEnabled(false);
    ui->partie_equipement->setEnabled(false);
}

void EditerRessources::accepter()
{
    enregistre(m_ressourceActuelle);
}

void EditerRessources::ajoute()
{
    QString action, nom, chemin;
    QStringList actions;
    actions.push_back("nouvelle ressource");
    actions.push_back("nouvel equipement");
    actions.push_back("nouvelle arme");
    bool ok;
    action = QInputDialog::getItem(this, "Nouvelle ressource", "selectionnez le type de la ressource", actions, 0, false, &ok);
    if(ok)
    {
        nom = QInputDialog::getText(this, "Nom", "Entrez le nom de la/du "+action, QLineEdit::Normal, "", &ok);
        chemin = QFileDialog::getOpenFileName(this, "Selectionnez l'image", QString(), "Images (*.png)");
        if(ok)
        {
            if(action == "nouvelle ressource")
            {
                ajouteRessource(Resource::nouvelle(nom, chemin));
            }
            else if(action == "nouvel equipement")
            {
                ajouteEquipement(OutfitModel::nouvel(nom, chemin));
            }
            else if(action == "nouvelle arme")
            {
                ajouteArme(WeaponModel::nouvelle(nom,chemin, m_ressources));
            }
        }
    }
}

void EditerRessources::supprime()
{
    QString nom = ui->select_ressource->currentText();
    WeaponModel *arme = m_ressources->getArme(nom);
    OutfitModel *equipement = m_ressources->getEquipement(nom);
    Resource *ressource = m_ressources->getRessource(nom);
    if(arme)
    {
        supprimeArme(nom);
    }
    else if(equipement)
    {
        supprimeEquipement(nom);
    }
    else if(ressource)
    {
        supprimeRessource(nom);
    }
}

void EditerRessources::nouvelleImage()
{
    QString chemin = QFileDialog::getOpenFileName(this, "Selectionnez l'image", QString(), "Images (*.png)");
    Resource *ressource = m_ressources->getRessource(m_ressourceActuelle);
    if(ressource && QFile::exists(chemin))
    {
        ressource->setImage(chemin);
        ui->image->setIcon(QIcon(ressource->imageg()));
    }
}
