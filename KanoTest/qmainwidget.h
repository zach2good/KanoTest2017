#ifndef QMAINWIDGET_H
#define QMAINWIDGET_H

#include <memory>

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVector>

#include "stepwidgetitem.h"

#include "lib/Challenge.h"

namespace Ui {
class QMainWidget;
}

class QMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QMainWidget(QWidget *parent = 0);
    ~QMainWidget();

private:
    QVector<std::shared_ptr<Challenge>> m_vecChallenges;

private slots:
    void on_loadButton_clicked();
    void on_quitButton_clicked();

private:
    Ui::QMainWidget *ui;
};

#endif // QMAINWIDGET_H
