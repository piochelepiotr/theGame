#include "mainwindow.h"
#include <iostream>
#include <QGraphicsSceneMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTime temps;
    temps.start();
    m_au_moins_une_case_en_glisser = false;
    showMaximized();
    ui->setupUi(this);

    m_outil = Outil_objets;
    m_donnees_editeur = new Data(this->size().width(),this->size().height(),this->size().width(),this->size().height());
    m_jeu = new Jeu2d(this->size(), ui->texte,m_donnees_editeur);
    ui->carte->setScene(m_jeu);
    ui->carte->setMouseTracking(true);
    installEventFilter(this);
    m_jeu->installEventFilter(this);

    qDebug() << "premier appel " << temps.elapsed();

    m_tabbar = new BottomTab(this,m_jeu,m_donnees_editeur->resources);
    ui->barre_outil->addWidget(m_tabbar);
    chargeThemeObjet(0);

    m_appuyer = false;
    ui->carte->setSceneRect(0,0,200,200);

    ui->actionChanger_la_valeure_du_zoom->setShortcut(Qt::Key_Z);
    connect(ui->actionChanger_la_valeure_du_zoom, SIGNAL(triggered()), this, SLOT(changeZoom()));
    addAction(ui->actionChanger_la_valeure_du_zoom);
    ui->actionCalque_1->setShortcut(QKeySequence("1"));
    connect(ui->actionCalque_1, SIGNAL(triggered()), this, SLOT(calque1()));
    addAction(ui->actionCalque_1);
    ui->actionCalque_2->setShortcut(QKeySequence("2"));
    connect(ui->actionCalque_2, SIGNAL(triggered()), this, SLOT(calque2()));
    addAction(ui->actionCalque_2);
    ui->actionCalque_3->setShortcut(QKeySequence("3"));
    connect(ui->actionCalque_3, SIGNAL(triggered()), this, SLOT(calque3()));
    addAction(ui->actionCalque_3);
    ui->actionObjet->setShortcut(QKeySequence("O"));
    connect(ui->actionObjet, SIGNAL(triggered()), this, SLOT(outil_objets()));
    addAction(ui->actionObjet);
    ui->actionCase_marchable->setShortcut(QKeySequence("M"));
    connect(ui->actionCase_marchable, SIGNAL(triggered()), this, SLOT(outil_cases_marchables()));
    addAction(ui->actionCase_marchable);
    ui->actionTransporteur->setShortcut(QKeySequence("T"));
    connect(ui->actionTransporteur, SIGNAL(triggered()), this, SLOT(outil_transporteurs()));
    addAction(ui->actionTransporteur);
    ui->actionCase_fight->setShortcut(QKeySequence("C"));
    connect(ui->actionCase_fight, SIGNAL(triggered()), this, SLOT(outil_cases_fight()));
    addAction(ui->actionCase_fight);
    ui->actionCase_portee->setShortcut(QKeySequence("P"));
    connect(ui->actionCase_portee, SIGNAL(triggered()), this, SLOT(outil_cases_po()));
    addAction(ui->actionCase_portee);
    ui->actionEquipe_1->setShortcut(QKeySequence("Ctrl+1"));
    connect(ui->actionEquipe_1, SIGNAL(triggered()), this, SLOT(equipeUne()));
    addAction(ui->actionEquipe_1);
    ui->actionEquipe_2->setShortcut(QKeySequence("Ctrl+2"));
    connect(ui->actionEquipe_2, SIGNAL(triggered()), this, SLOT(equipeDeux()));
    addAction(ui->actionEquipe_2);
    ui->actionPetite->setShortcut(QKeySequence("7"));
    connect(ui->actionPetite, SIGNAL(triggered()), this, SLOT(petiteTaille()));
    addAction(ui->actionPetite);
    ui->actionMoyenne->setShortcut(QKeySequence("8"));
    connect(ui->actionMoyenne, SIGNAL(triggered()), this, SLOT(moyenneTaille()));
    addAction(ui->actionMoyenne);
    ui->actionGrande->setShortcut(QKeySequence("9"));
    connect(ui->actionGrande, SIGNAL(triggered()), this, SLOT(grandeTaille()));
    addAction(ui->actionGrande);
    ui->actionAnnuler->setShortcut(QKeySequence("Ctrl+z"));
    connect(ui->actionAnnuler, SIGNAL(triggered()), this, SLOT(annuler()));
    addAction(ui->actionAnnuler);
    ui->menu_fichier_enregistrer->setShortcut(QKeySequence("Ctrl+S"));
    connect(ui->menu_fichier_enregistrer, SIGNAL(triggered()), m_jeu, SLOT(enregistre()));
    addAction(ui->menu_fichier_enregistrer);
    ui->menu_fichier_charger->setShortcut(QKeySequence("Ctrl+C"));
    connect(ui->menu_fichier_charger, SIGNAL(triggered()), this, SLOT(chargeMap()));
    addAction(ui->menu_fichier_charger);
    ui->menu_fichier_nouvelle->setShortcut(QKeySequence("Ctrl+N"));
    connect(ui->menu_fichier_nouvelle, SIGNAL(triggered()), this, SLOT(nouvelle()));
    addAction(ui->menu_fichier_nouvelle);
    ui->menu_fichier_quitter->setShortcut(QKeySequence("Ctrl+Q"));
    connect(ui->menu_fichier_quitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    addAction(ui->menu_fichier_quitter);
    //m_jeu->dataMap()->setEnregistree(true);
}

MainWindow::~MainWindow()
{
    //delete m_objets_2;
    delete ui;
    delete m_donnees_editeur;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == this && event->type() == QEvent::Resize)
    {
        QMainWindow::eventFilter(obj,event);
        m_jeu->resize(ui->carte->size());
        return true;
    }
    else if(obj == m_jeu && event->type() == QEvent::GraphicsSceneMouseMove)
    {
        QMainWindow::eventFilter(obj,event);
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
        QPoint poscase = m_jeu->dataMap()->ccase(mouseEvent->scenePos().x(), mouseEvent->scenePos().y(),m_jeu->getlmap(),m_jeu->gethmap(),m_jeu->getlcase(),m_jeu->gethcase(),m_jeu->zoom());
        if(m_appuyer)
        {
            if((poscase.x() != m_jeu->case_selectionnee().x() || poscase.y() != m_jeu->case_selectionnee().y()) && poscase.x() != -1)
            {
                m_jeu->changementSele(poscase);
                if(m_outil == Outil_case_marchables)
                {
                    m_au_moins_une_case_en_glisser = true;
                    m_jeu->remplitCaseIm(poscase.x(), poscase.y());
                }
                else if(m_outil == Outil_case_po)
                {
                    m_au_moins_une_case_en_glisser = true;
                    m_jeu->change_portee_case(poscase);
                }
                else if(m_outil == Outil_objets)
                {
                    m_au_moins_une_case_en_glisser = true;
                    m_jeu->case_prend_valeur(poscase);
                }
            }
        }
        else
        {
            m_jeu->souriBouge(poscase);
        }
        return true;
    }
    else if(obj == m_jeu && event->type() == QEvent::GraphicsSceneMousePress)
    {
        QMainWindow::eventFilter(obj,event);
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
        QPoint poscase = m_jeu->dataMap()->ccase(mouseEvent->scenePos().x(), mouseEvent->scenePos().y(),m_jeu->getlmap(),m_jeu->gethmap(),m_jeu->getlcase(),m_jeu->gethcase(),m_jeu->zoom());
        if(m_outil == Outil_transporteur)
        {
            if(caseExiste(poscase.x(), poscase.y()))
            {
                if(m_jeu->dataMap()->contientTranspo(poscase))
                {
                    ajouteUnTransporteur(poscase.x(), poscase.y(), true);
                    m_jeu->ajouteEvent();
                }
                else
                {
                    ajouteUnTransporteur(poscase.x(), poscase.y());
                    m_jeu->ajouteEvent();
                }

            }
        }
        else if(m_outil == Outil_case_fight)
        {
            if(caseExiste(poscase.x(), poscase.y()))
            {
                if(mouseEvent->button() == Qt::LeftButton)
                {
                    if(m_jeu->peutAjouterCasecbt(poscase.x(), poscase.y()))
                    {
                        m_jeu->ajouteCasecbt(poscase.x(), poscase.y());
                        m_jeu->ajouteEvent();
                    }
                }
                else
                {
                    m_jeu->supprimeCasecbt(poscase.x(), poscase.y());
                    m_jeu->ajouteEvent();
                }
            }
        }
        else
        {
            m_jeu->setEffaceIm(!(mouseEvent->button() == Qt::LeftButton));
            m_appuyer = true;
            if(poscase.x() != -1)
            {
                if(m_outil == Outil_case_marchables)
                {
                    m_jeu->remplitCaseIm(poscase.x(), poscase.y());
                    m_jeu->ajouteEvent();
                }
                else if(m_outil == Outil_case_po)
                {
                    m_jeu->change_portee_case(poscase);
                }
                else
                {
                    m_jeu->case_prend_valeur(poscase);
                    m_jeu->ajouteEvent();
                }
            }
        }
        return true;
    }
    else if(obj == m_jeu && event->type() == QEvent::GraphicsSceneMouseRelease)
    {
        if(m_au_moins_une_case_en_glisser)
        {
            m_jeu->ajouteEvent();
            m_au_moins_une_case_en_glisser = false;
        }
        m_appuyer = false;
        return QMainWindow::eventFilter(obj, event);
    }
    else if(obj == m_jeu && event->type() == QEvent::KeyRelease)
    {
       QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
       if(keyEvent->key() == Qt::Key_Up)
           deplaceMap(Haut);
       if(keyEvent->key() == Qt::Key_Down)
           deplaceMap(Bas);
       if(keyEvent->key() == Qt::Key_Right)
           deplaceMap(Droite);
       if(keyEvent->key() == Qt::Key_Left)
           deplaceMap(Gauche);
    }
    else
    {
        return QMainWindow::eventFilter(obj, event);
    }

    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::chargeMap()
{
    bool ok = false;
    int x = QInputDialog::getInt(this, "Chargement", trUtf8("Rentre les coordonées X de la map : "), m_jeu->dataMap()->x(), -100,100,1,&ok),y=0,z=0;
    if(ok)
        y = QInputDialog::getInt(this, "Chargement", trUtf8("Rentre les coordonées Y de la map : "), m_jeu->dataMap()->y(), -100,100,1,&ok);
    if(ok)
        z = QInputDialog::getInt(this, "Chargement", trUtf8("Rentre les coordonées Z de la map : "), m_jeu->dataMap()->z(), -100,100,1,&ok);
    if(ok)
        m_jeu->charge(x,y,z);
    else
        return;
}

void MainWindow::nouveauThemeObjet()
{
    bool ok;
    QString theme = QInputDialog::getText(this, "nouveau theme objet", trUtf8("Entrez le name du nouveau theme :"), QLineEdit::Normal, QString(), &ok);
    if(ok && !theme.isEmpty())
    {
        m_jeu->dataMap()->enregistre();
        ajouteUnTheme(theme);
        m_jeu->decors()->ajouteCategorie(theme);
        m_tabbar->m_widobjets->m_themesObjet->addItem(theme);
    }
}

void MainWindow::nouveauObjetPourTheme()
{
    /*QString chemin;

    chemin = "/home/piotr/Documents/jeu/";

    int num_ici = trouveNumero();
    int imdep = 0;
    QString texte;

    for(int i = imdep; i < 800000; i++)
    {
        if(QFile::exists(chemin+QString::number(i)+".png"))
        {
            qDebug() << i << "et num ici " << num_ici;
            Objet *objet = new Objet(num_ici, "", m_tabbar->m_widobjets->m_themesObjet->itemText(m_tabbar->m_widobjets->m_themesObjet->currentIndex()), 1, 1, m_jeu->getlcase(), m_jeu->gethcase());
            QPixmap image(chemin+QString::number(i)+".png");
            objet->setPropx((image.size().width())/ 90.0, m_jeu->getlcase(),m_jeu->gethcase());//avant c'etait 80
            objet->setPropy((image.size().height())/ 40.0, m_jeu->getlcase(),m_jeu->gethcase());//avant c'etait 42
            texte = texte + ajouteObjet2(objet, chemin+QString::number(i)+".png");
            num_ici = num_ici + 1;
        }
    }
    ajouteObjet3(texte);*/



    QString chemin;

    chemin = "";



    Object *objet = new Object(trouveNumero(), "", m_tabbar->m_widobjets->m_themesObjet->itemText(m_tabbar->m_widobjets->m_themesObjet->currentIndex()), 1, 1, m_jeu->getlcase(), m_jeu->gethcase());
    //QPixmap image(chemin+QString::number(i)+".png");
    //objet->setPropx((image.size().width())/ 80.0, m_jeu->getlcase(),m_jeu->gethcase());
    //objet->setPropy((image.size().height())/ 42.0, m_jeu->getlcase(),m_jeu->gethcase());

    bool ok;
    EditerUnObjet boite(this, &ok, objet, true,m_jeu->getlcase(), m_jeu->gethcase(), &chemin);
    if(ok)
    {
        m_jeu->dataMap()->enregistre();
        ajouteObjet(objet, chemin);
        m_jeu->decors()->ajouteObjet(objet);
        chargeThemeObjet(m_tabbar->m_widobjets->m_themesObjet->currentIndex());
        m_jeu->actualise();
    }
    else
    {
        delete objet;
    }

    /*QString chemin;

    bool ok = true;
    //test test

    chemin = "/home/piotr/Documents/jeu/";
    for(int i = 16589; i < 13371362; i++)
    {
        if(QFile::exists(chemin+QString::number(i)+".png"))
        {
            qDebug() << i;
            Objet *objet = new Objet(trouveNumero(), "", m_tabbar->m_widobjets->m_themesObjet->itemText(m_tabbar->m_widobjets->m_themesObjet->currentIndex()), 1, 1, m_jeu->getlcase(), m_jeu->gethcase());
            QPixmap image(chemin+QString::number(i)+".png");
            objet->setPropx((image.size().width())/ 80.0, m_jeu->getlcase(),m_jeu->gethcase());
            objet->setPropy((image.size().height())/ 42.0, m_jeu->getlcase(),m_jeu->gethcase());

            //EditerUnObjet boite(this, &ok, objet, true,m_jeu->getlcase(), m_jeu->gethcase(), &chemin);
            if(ok)
            {
                //m_jeu->enregistre();
                ajouteObjet(objet, chemin+QString::number(i)+".png");
                //m_jeu->decors()->ajouteObjet(objet);
                //chargeThemeObjet(m_tabbar->m_widobjets->m_themesObjet->currentIndex());
            }
            else
            {
                delete objet;
            }
        }
    }*/


}

void MainWindow::chargeThemeObjet(int num)
{
    qDebug()<<"appelle charge";
    QString theme = m_tabbar->m_widobjets->m_themesObjet->itemText(num);
    for(int i = 0; i < m_tabbar->m_widobjets->m_imagesObjets.size(); i++)
    {
        m_tabbar->m_widobjets->m_lay_imagesObjets->removeWidget(m_tabbar->m_widobjets->m_imagesObjets[i]);
    }
    for(int i = 0; i < m_tabbar->m_widobjets->m_imagesObjets.size(); i++)
    {
        delete m_tabbar->m_widobjets->m_imagesObjets[i];
    }

    m_tabbar->m_widobjets->m_imagesObjets.clear();

    if(!theme.isEmpty())
    {
        QMap<qint16, Object*>objets = m_jeu->decors()->categorie(theme)->objets();
        BoutonImg *bout;
        for(QMap<qint16, Object*>::iterator it = objets.begin(); it != objets.end(); it++)
        {

            bout = new BoutonImg(it.value());
            connect(bout, SIGNAL(clique(qint16)), this, SLOT(selectionNouveauObjet(qint16)));
            m_tabbar->m_widobjets->m_imagesObjets.push_back(bout);
            m_tabbar->m_widobjets->m_lay_imagesObjets->addWidget(bout);
        }
    }

    qDebug() << "fin charge";
}


void MainWindow::selectionNouveauObjet(qint16 numero)
{
    m_jeu->setObjetActuel(m_jeu->decors()->objet(numero));
}

void MainWindow::spellObjet()
{
    if(m_jeu->getObjActuel()->numero())
    {
        bool ok = false, supprimer = false;
        Object *objet = m_jeu->getObjActuel();
        EditerUnObjet boite(this, &ok, objet, false,m_jeu->getlcase(), m_jeu->gethcase(), 0, &supprimer);
        if(ok)
        {
            m_jeu->dataMap()->enregistre();
            spellUnObjet(objet);
            m_jeu->charge();
            chargeThemeObjet(m_tabbar->m_widobjets->m_themesObjet->currentIndex());
        }
        else if(supprimer)
        {
            m_jeu->dataMap()->enregistre();
            m_jeu->setObjetActuel(m_jeu->decors()->objet(0));
            supprimerObjet(m_jeu->decors(), objet);
            chargeThemeObjet(m_tabbar->m_widobjets->m_themesObjet->currentIndex());
            m_jeu->charge();
        }
        m_jeu->actualise();
    }
}

void MainWindow::ajouteUnTransporteur(int x, int y, bool spell)
{
    bool ok, suppr;
    Gate transpo;
    if(spell)
    {
        transpo = m_jeu->dataMap()->getTranspo(QPoint(x,y));
    }
    EditerTransporteur boite(this, &transpo, &ok, &suppr);

    if(spell && suppr)
    {
        m_jeu->supprimeTranspo(QPoint(x,y));
        return;
    }

    if(ok)
    {
        m_jeu->ajouteTranspo(QPoint(x,y), transpo);
    }
}

void MainWindow::chargefond()
{
    QDir dir(QFileDialog::getOpenFileName(this, trUtf8("Ouvrir un fichier"), "lesfonds/", "Images (*.png *.gif *.jpg *.jpeg)"));
    m_jeu->fondEgal(dir.dirName());
}

void MainWindow::deplaceMap(Cote cote)
{
    int cx = 0, cy = 0;
    if(cote == Droite)
    {
        if(m_jeu->dataMap()->x() < NBR_DE_MAPS_X-1)
            cx = 1;
    }
    else if(cote == Gauche)
    {
        if(m_jeu->dataMap()->x() > 0)
            cx = -1;
    }
    else if(cote == Bas)
    {
        if(m_jeu->dataMap()->y() < NBR_DE_MAPS_Y-1)
            cy = 1;
    }
    else
    {
        if(m_jeu->dataMap()->y() > 0)
            cy = -1;
    }

    m_jeu->dataMap()->enregistre();
    m_jeu->charge(m_jeu->dataMap()->x()+cx,m_jeu->dataMap()->y()+cy, m_jeu->dataMap()->z());
}

void MainWindow::outil_objets()
{
    QTime temps;
    temps.start();
    ui->carte->setCursor(QCursor());
    if(m_outil == Outil_case_marchables)
        m_jeu->masque_casesMarchable();
    else if(m_outil == Outil_case_fight)
        m_jeu->masque_casesFight();
    else if(m_outil == Outil_case_po)
        m_jeu->masque_casesPO();
    m_outil = Outil_objets;
    m_tabbar->m_widdivers->m_outil_objets->setChecked(true);
    qDebug() << "premier appel " << temps.elapsed();
    m_tabbar->setCurrentIndex(2);
    qDebug() << "2 appel " << temps.elapsed();
}

void MainWindow::outil_transporteurs()
{
    ui->carte->setCursor(QCursor());
    if(m_outil == Outil_case_marchables)
        m_jeu->masque_casesMarchable();
    else if(m_outil == Outil_case_fight)
        m_jeu->masque_casesFight();
    else if(m_outil == Outil_case_po)
        m_jeu->masque_casesPO();
    calque3();
    m_jeu->setObjetActuel(m_jeu->decors()->objet(0));
    m_outil = Outil_transporteur;
    m_tabbar->m_widdivers->m_outil_transporteurs->setChecked(true);
}

void MainWindow::outil_cases_marchables()
{
    ui->carte->setCursor(QCursor());
    if(m_outil == Outil_case_fight)
        m_jeu->masque_casesFight();
    else if(m_outil == Outil_case_po)
        m_jeu->masque_casesPO();
    m_jeu->affiche_casesMarchable();
    calque3();
    m_jeu->setObjetActuel(m_jeu->decors()->objet(0));
    m_outil = Outil_case_marchables;
    m_tabbar->m_widdivers->m_outil_cases_marchables->setChecked(true);
    m_tabbar->setCurrentIndex(3);
}

void MainWindow::outil_cases_po()
{
    ui->carte->setCursor(QCursor());
    if(m_outil == Outil_case_fight)
        m_jeu->masque_casesFight();
    m_jeu->affiche_casesPO();
    calque3();
    m_jeu->setObjetActuel(m_jeu->decors()->objet(0));
    m_outil = Outil_case_po;
    m_tabbar->m_widdivers->m_outil_casespo->setChecked(true);
    m_tabbar->setCurrentIndex(3);
}

void MainWindow::outil_cases_fight()
{
    ui->carte->setCursor(QCursor(QPixmap("../data/cursor_fight.png"), 0, 0));
    if(m_outil == Outil_case_marchables)
        m_jeu->masque_casesMarchable();
    m_jeu->affiche_casesFight();
    calque3();
    m_jeu->setObjetActuel(m_jeu->decors()->objet(0));
    m_outil = Outil_case_fight;
    m_tabbar->m_widdivers->m_outil_casescbt->setChecked(true);
    m_tabbar->setCurrentIndex(4);
}

void MainWindow::calque1()
{
    m_jeu->calc1();
    m_tabbar->m_widobjets->m_calc1->setChecked(true);
}

void MainWindow::calque2()
{
    m_jeu->calc2();
    m_tabbar->m_widobjets->m_calc2->setChecked(true);
}

void MainWindow::calque3()
{
    m_jeu->calc3();
    m_tabbar->m_widobjets->m_calc3->setChecked(true);
}

void MainWindow::petiteTaille()
{
    m_jeu->tailleun();
    m_tabbar->m_widCasesMarchables->m_un->setChecked(true);
}

void MainWindow::moyenneTaille()
{
    m_jeu->tailletrois();
    m_tabbar->m_widCasesMarchables->m_trois->setChecked(true);
}

void MainWindow::grandeTaille()
{
    m_jeu->taillecinq();
    m_tabbar->m_widCasesMarchables->m_cinq->setChecked(true);
}

void MainWindow::charger_contours()
{
    m_jeu->chargeContours();
}

void MainWindow::equipeUne()
{
    m_jeu->equipe1();
    m_tabbar->m_widCasesFight->m_equipe_une->setChecked(true);
}

void MainWindow::equipeDeux()
{
    m_jeu->equipe2();
    m_tabbar->m_widCasesFight->m_equipe_deux->setChecked(true);
}

void MainWindow::changeZoom()
{
    m_jeu->changeValeurZoom();
    if(m_tabbar->m_widdivers->m_vue_large->isChecked())
        m_tabbar->m_widdivers->m_vue_reduite->setChecked(true);
    else
        m_tabbar->m_widdivers->m_vue_large->setChecked(true);
}

void MainWindow::monstresDeLaMap()
{
    EditerMonstreDeLaMap boite(this, m_jeu->dataMap()->getMonstresMap(),m_donnees_editeur->resources->monstres().keys());
}

void MainWindow::musiques()
{
    EditerMusiques boite(this, m_jeu->dataMap()->getMusiques());
}

void MainWindow::nouvelle()
{
    bool ok = false;
    int x = 0,y = 0,z = 0;
    x = QInputDialog::getInt (this, "Nouvelle", trUtf8("Rentre les coordonées X de la map : "), m_jeu->dataMap()->x(), -100,100,1,&ok);
    if(ok)
        y = QInputDialog::getInt (this, "Nouvelle", trUtf8("Rentre les coordonées Y de la map : "), m_jeu->dataMap()->y(), -100,100,1,&ok);
    if(ok)
        z = QInputDialog::getInt (this, "Nouvelle", trUtf8("Rentre les coordonées Z de la map : "), m_jeu->dataMap()->z(), -100,100,1,&ok);
    if(ok)
    {
        if(Map::exist(x,y,z))
        {
             if(QMessageBox::question(this, trUtf8("Attention !"), trUtf8("Attention ! La map en question existe déjà, voulez-vous l'écraser ?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
             {
                 m_jeu->charge(x,y,z);
             }
        }
        else
        {
            m_jeu->charge(x,y,z);
        }
    }
}

void MainWindow::annuler()
{
    m_jeu->undo();
    switch(m_outil)
    {
        case Outil_transporteur:
            outil_transporteurs();
            break;
        case Outil_case_marchables:
            outil_cases_marchables();
            break;
        case Outil_case_fight:
            outil_cases_fight();
            break;
        case Outil_case_po:
            outil_cases_po();
            break;
        default:
            break;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!m_jeu->dataMap()->estEnregistree())
    {
        int reponse = QMessageBox::question(this, trUtf8("Fermetture !"), trUtf8("Voulez-vous enregistrer les modifications apportées à la map ?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(reponse == QMessageBox::Yes)
            m_jeu->dataMap()->enregistre();
        else if(reponse == QMessageBox::Cancel)
            event->ignore();
    }
}


