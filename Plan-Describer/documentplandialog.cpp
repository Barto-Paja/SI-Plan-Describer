#include "documentplandialog.hpp"
#include "ui_documentplandialog.h"

DocumentPlanDialog::DocumentPlanDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DocumentPlanDialog)
{
    ui->setupUi(this);
}

DocumentPlanDialog::~DocumentPlanDialog()
{
    delete ui;
}

bool DocumentPlanDialog::loadData()
{
    DocumentTablesAggregate doc("database.db3");
    doc.loadData();

    _variants = doc.variants();

    for (int i =0;i < _variants.count();++i) {


        QVBoxLayout *layout = new QVBoxLayout;
        layout->setObjectName(QString("VBox_%1").arg(i));
        for (int j = 0;j < _variants[i].variants.count(); ++j) {
            qDebug() << _variants[i].variants[j];
            layout->addWidget(new QCheckBox(_variants[i].variants[j]));
        }

        QWidget *widget = new QWidget;
        widget->setObjectName(QString("Widget_%1").arg(i));
        ui->stackedWidget_targetContentView->addWidget(widget);
        ui->stackedWidget_targetContentView->widget(i)->setLayout(layout);

        ui->comboBox_targetType->addItem(_variants[i].name,i);
    }

    ui->stackedWidget_targetContentView->setCurrentIndex(0);




}

void DocumentPlanDialog::on_comboBox_targetType_currentIndexChanged(int index)
{
    ui->stackedWidget_targetContentView->setCurrentIndex(index);
}
