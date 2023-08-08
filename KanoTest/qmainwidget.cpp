#include "qmainwidget.h"
#include "ui_qmainwidget.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

QMainWidget::QMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMainWidget)
{
    ui->setupUi(this);
}

QMainWidget::~QMainWidget()
{
    delete ui;
}

void QMainWidget::on_loadButton_clicked()
{
    auto filenames = QFileDialog::getOpenFileNames(this,
        tr("Open File"), "", tr("All files (*.*)"));

    // Dialog cancelled...
    if (filenames.length() == 0)
    {
        return;
    }

    for (auto& filename : filenames)
    {
        QFile f(filename);
        f.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&f);
        auto content = in.readAll();
        f.close();

        try {
            auto m_ptrChallenge = std::make_shared<Challenge>(content.toStdString());
            m_vecChallenges.push_back(m_ptrChallenge);

            for (auto& step : *m_ptrChallenge.get())
            {
                QListWidgetItem *listWidgetItem = new QListWidgetItem(ui->listWidget);
                ui->listWidget->addItem (listWidgetItem);
                StepWidgetItem* stepWidgetItem = new StepWidgetItem;
                stepWidgetItem->setStep(&step);
                listWidgetItem->setSizeHint (stepWidgetItem->sizeHint ());
                ui->listWidget->setItemWidget (listWidgetItem, stepWidgetItem);
            }

        } catch (...) {
            QMessageBox messageBox;
            messageBox.critical(0,"Error", QString("An error has occured!\n%1\nCheck your JSON?").arg(filename));
            messageBox.setFixedSize(500,200);
        }
    }
}

void QMainWidget::on_quitButton_clicked()
{
    QApplication::quit();
}
