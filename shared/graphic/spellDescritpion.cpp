#include "graphic/spellDescription.h"
#include "ui_spellDescription.h"

Description_sort::Description_sort(UnSort *sort) :
    ui(new Ui::Description_sort)
{
    ui->setupUi(this);
    ui->textEdit_1->setReadOnly(true);
    ui->textEdit_2->setReadOnly(true);
    ui->textEdit_3->setReadOnly(true);
    ui->textEdit_4->setReadOnly(true);
    ui->textEdit_5->setReadOnly(true);
    ui->textEdit_6->setReadOnly(true);
    ui->textEdit_7->setReadOnly(true);
    ui->textEdit_8->setReadOnly(true);
    ui->textEdit_9->setReadOnly(true);
    ui->textEdit_10->setReadOnly(true);
    if(sort)
        setSort(sort);
}

void Description_sort::setSort(UnSort *sort)
{
    if(!sort)
    {
        ui->textEdit_1->setText("");
        ui->textEdit_2->setText("");
        ui->textEdit_3->setText("");
        ui->textEdit_4->setText("");
        ui->textEdit_5->setText("");
        ui->textEdit_6->setText("");
        ui->textEdit_7->setText("");
        ui->textEdit_8->setText("");
        ui->textEdit_9->setText("");
        ui->textEdit_10->setText("");
        ui->niveau->setText("");
        ui->nom_sort->setText("");
    }
    else
    {
        ui->textEdit_1->setText(Sort::decrit(sort->sortNiveau(0)));
        ui->textEdit_2->setText(Sort::decrit(sort->sortNiveau(1)));
        ui->textEdit_3->setText(Sort::decrit(sort->sortNiveau(2)));
        ui->textEdit_4->setText(Sort::decrit(sort->sortNiveau(3)));
        ui->textEdit_5->setText(Sort::decrit(sort->sortNiveau(4)));
        ui->textEdit_6->setText(Sort::decrit(sort->sortNiveau(5)));
        ui->textEdit_7->setText(Sort::decrit(sort->sortNiveau(6)));
        ui->textEdit_8->setText(Sort::decrit(sort->sortNiveau(7)));
        ui->textEdit_9->setText(Sort::decrit(sort->sortNiveau(8)));
        ui->textEdit_10->setText(Sort::decrit(sort->sortNiveau(9)));
        ui->nom_sort->setText(sort->nom());
    }
}

Description_sort::~Description_sort()
{
    delete ui;
}
