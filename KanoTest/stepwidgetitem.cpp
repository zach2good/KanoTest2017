#include "stepwidgetitem.h"
#include "ui_stepwidgetitem.h"
#include <iostream>
#include <QDebug>

StepWidgetItem::StepWidgetItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StepWidgetItem)
{
    ui->setupUi(this);
}

StepWidgetItem::~StepWidgetItem()
{
    delete ui;
}

void StepWidgetItem::setStep(Challenge::Step* pStep)
{
    m_ptrStep = pStep;
    ui->label->setText(m_ptrStep->GetInstruction().c_str());
}

void StepWidgetItem::on_lineEdit_textChanged()
{
    ui->lineEdit->setStyleSheet("QLineEdit { background-color : white; color : black; }");
}

void StepWidgetItem::on_submitButton_clicked()
{
    auto content = ui->lineEdit->text();
    bool regex_match = m_ptrStep->Validate(content.toStdString());

    if (regex_match)
    {
        ui->lineEdit->setStyleSheet("QLineEdit { background-color : green; color : white; }");
        ui->lineEdit->setEnabled(false);
        ui->submitButton->setEnabled(false);
    }
    else
    {
        ui->lineEdit->setStyleSheet("QLineEdit { background-color : red; color : blue; }");
    }
}

void StepWidgetItem::on_lineEdit_returnPressed()
{
    on_submitButton_clicked();
}
