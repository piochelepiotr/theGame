#include "graphic/spellDescription.h"
#include "ui_spellDescription.h"

SpellDescription::SpellDescription(SpellModel *spell) :
    ui(new Ui::SpellDescription)
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
    if(spell)
        setSpell(spell);
}

void SpellDescription::setSpell(SpellModel *spell)
{
    if(!spell)
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
        ui->nom_spell->setText("");
    }
    else
    {
        ui->textEdit_1->setText(Spell::decrit(spell->spellNiveau(0)));
        ui->textEdit_2->setText(Spell::decrit(spell->spellNiveau(1)));
        ui->textEdit_3->setText(Spell::decrit(spell->spellNiveau(2)));
        ui->textEdit_4->setText(Spell::decrit(spell->spellNiveau(3)));
        ui->textEdit_5->setText(Spell::decrit(spell->spellNiveau(4)));
        ui->textEdit_6->setText(Spell::decrit(spell->spellNiveau(5)));
        ui->textEdit_7->setText(Spell::decrit(spell->spellNiveau(6)));
        ui->textEdit_8->setText(Spell::decrit(spell->spellNiveau(7)));
        ui->textEdit_9->setText(Spell::decrit(spell->spellNiveau(8)));
        ui->textEdit_10->setText(Spell::decrit(spell->spellNiveau(9)));
        ui->nom_spell->setText(spell->nom());
    }
}

SpellDescription::~SpellDescription()
{
    delete ui;
}
