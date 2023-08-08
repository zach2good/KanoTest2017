#ifndef STEPWIDGETITEM_H
#define STEPWIDGETITEM_H

#include <memory>

#include <QWidget>
#include <QLineEdit>
#include <QLabel>

#include "lib/Challenge.h"

namespace Ui {
class StepWidgetItem;
}

class StepWidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit StepWidgetItem(QWidget *parent = 0);
    ~StepWidgetItem();

    void setStep(Challenge::Step* pStep);

private:
    Challenge::Step* m_ptrStep;

private slots:
    void on_lineEdit_textChanged();
    void on_submitButton_clicked();

    void on_lineEdit_returnPressed();

private:
    Ui::StepWidgetItem *ui;
};

#endif // STEPWIDGETITEM_H
