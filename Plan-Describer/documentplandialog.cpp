#include "documentplandialog.hpp"
#include "ui_documentplandialog.h"

#include <QCheckBox>

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
    if(doc.loadData())
    {
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
        return true;
    }
    else
    {
        ui->label_CurrentTarget->setText("Błąd kolekcjonowania danych.");
        return false;
    }
}

void DocumentPlanDialog::on_comboBox_targetType_currentIndexChanged(int index)
{
    ui->stackedWidget_targetContentView->setCurrentIndex(index);
}

void DocumentPlanDialog::on_pushButton_generateFile_clicked()
{
    documentTemplate theme;
    theme.title = QString("%1 %2%3").arg(ui->label_headerTitle->text()).arg(ui->dateEdit_dateStart->date().year()).arg(ui->label_dateEnd->text());
    theme.studentName = ui->lineEdit_studentName->text();
    theme.therapistName = ui->lineEdit_therapistName->text();

    QLayout * layout = ui->stackedWidget_targetContentView->currentWidget()->layout();

    for (int i = 0; i < layout->count(); ++i)
    {
        QCheckBox * checkbox = qobject_cast<QCheckBox*>(layout->itemAt(i)->widget());

    }

    DocumentPrinter printer;
    printer.printFile(ui->lineEdit_studentName->text(),theme);

}
