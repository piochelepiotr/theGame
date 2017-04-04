#include "sortmetier.h"
#include "ui_sortmetier.h"

EditerMetier::EditerMetier(QWidget *parent, Scenery *decors, Resources *ressources) :
    QDialog(parent), ui(new Ui::EditerMetier)
{
    m_ressources = ressources;
    m_decors = decors;
    m_lesobjets = decors->objets();
    m_objets = decors->objetsParNom();
    m_lesressources = ressources->ressources();
    ui->setupUi(this);
    m_metierActuel = -1;
    m_recetteActuel = -1;
    m_nbrRecettes = 0;
    m_nbrObjets = 0;
    m_nbrIngredients = 0;
    m_recettes = new QMap<QString,QString>;
    ui->machine->addItems(m_lesobjets);
    connect(ui->ajoute_ingredient, SIGNAL(clicked()), this, SLOT(ajouteIngredient()));
    connect(ui->ajoute_obj, SIGNAL(clicked()), this, SLOT(ajouteObjet()));
    connect(ui->ajoute_metier, SIGNAL(clicked()), this, SLOT(ajouteMetier()));
    connect(ui->select_metier, SIGNAL(currentIndexChanged(int)), this, SLOT(changeMetier(int)));
    connect(ui->select_recette, SIGNAL(currentIndexChanged(int)), this, SLOT(changeRecette(int)));
    connect(ui->supprime_metier, SIGNAL(clicked()), this, SLOT(supprimerMetier()));
    connect(ui->ajoute_recette, SIGNAL(clicked()), this, SLOT(ajouteRecette()));
    connect(ui->supprime_recette, SIGNAL(clicked()), this, SLOT(supprimeRecette()));
    connect(this, SIGNAL(accepted()), this, SLOT(accepter()));
    chargeMetiers();
    setWindowTitle(trUtf8("Editer les métiers"));
    this->exec();
}

EditerMetier::~EditerMetier()
{
    delete ui;
    delete m_recettes;
}

void EditerMetier::changeMetier(int nouveau)
{
    if(m_metierActuel != -1 && m_metierActuel != -2)
    {
        enregistreMetier(m_metierActuel);
    }
    if(m_metierActuel != -2)
        clearMetier();
    m_metierActuel = nouveau;
    if(m_metierActuel != -1)
    {
        chargeMetier();
    }
}

void EditerMetier::changeRecette(int nouveau)
{
    if(m_recetteActuel != -1)
    {
        enregistreRecette(m_recetteActuel);
    }
    clearRecette();
    m_recetteActuel = nouveau;
    if(m_recetteActuel != -1)
    {
        chargeRecette();
    }
}

void EditerMetier::enregistreRecette(int index)
{
    QString texte = ui->select_recette->itemText(index) + '/' + textRecette() + "FR/";
    (*m_recettes)[ui->select_recette->itemText(index)] = texte;
}

void EditerMetier::enregistreMetier(int index)
{
    bool existe = false;
    QString nom = ui->select_metier->itemText(index), ligne, texte;
    texte = nom + '/' + textMetier();
    QFile fichier(QString(DONNEES)+QString("metiers.txt"));
    QFile fichier2(QString(DONNEES)+QString("metiers2.txt"));
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

        QFile::remove(QString(DONNEES)+QString("metiers.txt"));
        QFile::rename(QString(DONNEES)+QString("metiers2.txt"), QString(DONNEES)+QString("metiers.txt"));
    }
}

void EditerMetier::ajouteMetier()//fini
{
    bool ok;
    QString nom = QInputDialog::getText(this, trUtf8("Nouveau métier"), trUtf8("Entrez le nom du nouveau métier"), QLineEdit::Normal, QString(), &ok);
    if(ok)
    {
        ui->select_metier->addItem(nom);
    }
}

void EditerMetier::ajouteIngredient()
{
    if(m_recetteActuel != -1)
    {
        ui->tableau_recettes->insertRow(m_nbrIngredients);
        QComboBox *ingredient = new QComboBox;
        ingredient->addItems(m_lesressources);
        QSpinBox *quantite = new QSpinBox;
        NumberButton *bout = new NumberButton("supprimer", m_nbrIngredients);
        ui->tableau_recettes->setCellWidget(m_nbrIngredients, 0, ingredient);
        ui->tableau_recettes->setCellWidget(m_nbrIngredients, 1, quantite);
        ui->tableau_recettes->setCellWidget(m_nbrIngredients, 2, bout);
        m_comboRessources.push_back(ingredient);
        m_spinQuantite.push_back(quantite);
        m_boutonsIngr.push_back(bout);
        m_nbrIngredients++;
        connect(bout, SIGNAL(clique(int)), this, SLOT(ingredientSupprimme(int)));
    }
}

void EditerMetier::ajouteObjet()
{
    if(m_metierActuel != -1)
    {
        ui->tableau_objets->insertRow(m_nbrObjets);
        QComboBox *ressource_obtenue = new QComboBox;
        ressource_obtenue->addItems(m_lesressources);
        QComboBox *objet = new QComboBox;
        objet->addItems(m_lesobjets);
        QComboBox *souche = new QComboBox;
        souche->addItems(m_lesobjets);
        QSpinBox *niveau = new QSpinBox;
        NumberButton *bout = new NumberButton("supprimer", m_nbrObjets);
        ui->tableau_objets->setCellWidget(m_nbrObjets, 0, ressource_obtenue);
        ui->tableau_objets->setCellWidget(m_nbrObjets, 1, objet);
        ui->tableau_objets->setCellWidget(m_nbrObjets, 2, souche);
        ui->tableau_objets->setCellWidget(m_nbrObjets, 3, niveau);
        ui->tableau_objets->setCellWidget(m_nbrObjets, 4, bout);
        m_comboRessources_obtenues.push_back(ressource_obtenue);
        m_comboObjets.push_back(objet);
        m_comboSouches.push_back(souche);
        m_spinNiveaux.push_back(niveau);
        m_boutonsObj.push_back(bout);
        m_nbrObjets++;
        connect(bout, SIGNAL(clique(int)), this, SLOT(objetSupprime(int)));
    }
}

void EditerMetier::ajouteRecette()
{
    if(m_metierActuel != -1)
    {
        bool ok;
        QString nom = QInputDialog::getItem(this, trUtf8("Nouvelle recette"), trUtf8("Entrez le nom de la nouvelle recette"), m_lesressources, 0, false, &ok);
        if(ok)
        {
            ui->select_recette->addItem(nom);
            m_nbrRecettes++;
            ui->select_recette->setCurrentIndex(m_nbrRecettes-1);
        }
    }
}

QString EditerMetier::textMetier()
{
    QString texte;
    texte += QString::number((int) m_objets[ui->machine->currentText()]->numero())+'/';
    texte += ui->verbe_recette->text()+'/';
    texte += ui->rac->text()+'/';
    texte += ui->arme->text()+'/';
    texte += ui->verbe->text()+'/';
    for(int i = 0; i < m_nbrObjets; i++)
    {
        texte += m_comboRessources_obtenues[i]->currentText();
        texte += '/';
        texte += QString::number((int) m_objets[m_comboObjets[i]->currentText()]->numero());
        texte += '/';
        texte += QString::number((int) m_objets[m_comboSouches[i]->currentText()]->numero());
        texte += '/';
        texte += QString::number(m_spinNiveaux[i]->value());
        texte += '/';
    }
    if(m_recetteActuel != -1)
        enregistreRecette(ui->select_recette->currentIndex());
    texte += "RECETTES/";
    for(QMap<QString,QString>::iterator i = m_recettes->begin(); i != m_recettes->end(); i++)
    {
        texte += i.value();
    }
    texte += "FINRECETTES/";
    return texte;
}

QString EditerMetier::textRecette()
{
    QString texte;
    for(int i = 0; i < m_nbrIngredients; i++)
    {
        texte += m_comboRessources[i]->currentText() + '/' + QString::number(m_spinQuantite[i]->value()) + '/';
    }
    return texte;
}

void EditerMetier::supprimerMetier()
{
    if(m_metierActuel != -1)
    {
        QString nom = ui->select_metier->itemText(m_metierActuel), ligne;
        if(QMessageBox::question(this, trUtf8("Supression d'un métier"), trUtf8("Voulez vous vraiment supprimer le métier ")+nom, QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            enregistreMetier(m_metierActuel);
            m_metierActuel = -1;
            ui->select_metier->removeItem(ui->select_metier->currentIndex());
            clearMetier();
            QFile fichier(QString(DONNEES)+QString("metiers.txt"));
            QFile fichier2(QString(DONNEES)+QString("metiers2.txt"));
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

                QFile::remove(QString(DONNEES)+QString("metiers.txt"));
                QFile::rename(QString(DONNEES)+QString("metiers2.txt"), QString(DONNEES)+QString("metiers.txt"));
            }
        }
    }
}

void EditerMetier::supprimeRecette()
{
    if(m_recetteActuel != -1)
    {
        m_recettes->remove(ui->select_recette->currentText());
        clearRecette();
        m_nbrRecettes--;
        m_recetteActuel = -1;
        ui->select_recette->removeItem(ui->select_recette->currentIndex());
    }
}

void EditerMetier::objetSupprime(int obj)
{
    ui->tableau_objets->removeRow(obj);
    m_comboRessources_obtenues.remove(obj);
    m_comboObjets.remove(obj);
    m_comboSouches.remove(obj);
    m_spinNiveaux.remove(obj);
    m_boutonsObj.remove(obj);
    m_nbrObjets--;
    for(int i = obj; i < m_nbrObjets; i++)
    {
        m_boutonsObj[i]->moinsnum();
    }
}

void EditerMetier::ingredientSupprimme(int ingred)
{
    ui->tableau_recettes->removeRow(ingred);
    m_comboRessources.remove(ingred);
    m_spinQuantite.remove(ingred);
    m_boutonsIngr.remove(ingred);
    m_nbrIngredients--;
    for(int i = ingred; i < m_nbrIngredients; i++)
    {
        m_boutonsIngr[i]->moinsnum();
    }
}

void EditerMetier::chargeRecette()
{
    QString nom = ui->select_recette->currentText();
    if(m_recettes->contains(nom))
    {
        QString texte = (*m_recettes)[nom];
        QStringList mots = texte.split('/');
        mots.pop_front();
        while(mots[0] != "FR")
        {
            ajouteIngredient();
            m_comboRessources[m_nbrIngredients-1]->setCurrentIndex(m_comboRessources[m_nbrIngredients-1]->findText(mots[0]));
            mots.pop_front();
            m_spinQuantite[m_nbrIngredients-1]->setValue(mots[0].toInt());
            mots.pop_front();
        }
    }
}

void EditerMetier::chargeMetier()
{
    QString nom = ui->select_metier->itemText(m_metierActuel), ligne;
    QFile fichier(QString(DONNEES)+QString("metiers.txt"));
    if(fichier.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fichier);
        while(!(ligne = stream.readLine()).isNull())
        {
            if(ligne.section('/', 0,0) == nom)
            {
                texte_to_metier(ligne);
            }
        }
        fichier.close();
    }
}

void EditerMetier::clearMetier()
{
    ui->rac->setText("");
    ui->verbe->setText("");
    ui->verbe_recette->setText("");
    ui->arme->setText("");
    ui->tableau_objets->setRowCount(0);
    ui->select_recette->clear();
    m_nbrObjets = 0;
    m_recetteActuel = -1;
    m_nbrRecettes = 0;
    m_recettes->clear();
    clearRecette();
    m_comboRessources_obtenues.clear();
    m_comboObjets.clear();
    m_comboSouches.clear();
    m_spinNiveaux.clear();
    m_boutonsObj.clear();
}

void EditerMetier::clearRecette()
{
    ui->tableau_recettes->setRowCount(0);
    m_nbrIngredients = 0;
    m_comboRessources.clear();
    m_spinQuantite.clear();
    m_boutonsIngr.clear();
}

void EditerMetier::accepter()
{
    enregistreMetier(ui->select_metier->currentIndex());
}

void EditerMetier::chargeMetiers()
{
    QString ligne;
    QFile fichier(QString(DONNEES)+QString("metiers.txt"));
    if(fichier.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fichier);
        m_metierActuel = -2;
        while(!(ligne = stream.readLine()).isNull())
        {
            if(!ligne.isEmpty())
            {
                ui->select_metier->addItem(ligne.section('/', 0, 0));
            }
        }
        if(m_metierActuel == -2)
        {
            m_metierActuel = -1;
        }
        fichier.close();
    }
}

void EditerMetier::texte_to_metier(QString const& texte)
{
    QStringList liste = texte.split('/');
    liste.pop_front();
    ui->machine->setCurrentIndex(ui->machine->findText(m_decors->objet((qint16) liste[0].toInt())->nom()));
    liste.pop_front();
    ui->verbe_recette->setText(liste[0]);
    liste.pop_front();
    ui->rac->setText(liste[0]);
    liste.pop_front();
    ui->arme->setText(liste[0]);
    liste.pop_front();
    ui->verbe->setText(liste[0]);
    liste.pop_front();
    while(liste[0] != "RECETTES")
    {
        ajouteObjet();
        m_comboRessources_obtenues[m_nbrObjets-1]->setCurrentIndex(m_comboRessources_obtenues[m_nbrObjets-1]->findText(liste[0]));
        liste.pop_front();
        m_comboObjets[m_nbrObjets-1]->setCurrentIndex(m_comboObjets[m_nbrObjets-1]->findText(m_decors->objet((qint16) liste[0].toInt())->nom()));
        liste.pop_front();
        m_comboSouches[m_nbrObjets-1]->setCurrentIndex(m_comboSouches[m_nbrObjets-1]->findText(m_decors->objet((qint16) liste[0].toInt())->nom()));
        liste.pop_front();
        m_spinNiveaux[m_nbrObjets-1]->setValue(liste[0].toInt());
        liste.pop_front();
    }
    liste.pop_front();
    QString texte2 = liste.join("/");
    QStringList recettes = texte2.split("FR/");
    QStringList nomrecettes;
    while(recettes[0] != "FINRECETTES/")
    {
        texte2 = recettes[0].section('/', 0,0);
        nomrecettes << texte2;
        (*m_recettes)[texte2] = recettes[0] + "FR/";
        recettes.pop_front();
    }
    if(nomrecettes.size())
    {
        ui->select_recette->addItems(nomrecettes);
    }
}
