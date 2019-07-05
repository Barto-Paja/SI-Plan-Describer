#include "documentplandialog.hpp"
#include "ui_documentplandialog.h"

#include <QCheckBox>

DocumentPlanDialog::DocumentPlanDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DocumentPlanDialog)
{
    ui->setupUi(this);
    ui->dateEdit_dateStart->setDate(QDate::currentDate());
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
        QList<targetVariant> variants = doc.variants();

        for (int i =0;i < variants.count();++i) {


            QVBoxLayout *layout = new QVBoxLayout;
            layout->setObjectName(QString("VBox_%1").arg(i));
            for (int j = 0;j < variants[i].variants.count(); ++j) {
                qDebug() << variants[i].variants[j];
                layout->addWidget(new QCheckBox(variants[i].variants[j]));
            }

            QWidget *widget = new QWidget;
            widget->setObjectName(QString("%1").arg(doc.variants().at(i).name));
            ui->stackedWidget_targetContentView->addWidget(widget);
            ui->stackedWidget_targetContentView->widget(i)->setLayout(layout);

            ui->comboBox_targetType->addItem(variants[i].name,i);
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

    DocumentPrinter printer;
    documentTemplate document;
    prepareDocumentTemplate(document);
    printer.setDocument(document);
    printer.printFile(ui->lineEdit_studentName->text());

}

void DocumentPlanDialog::prepareDocumentTemplate(documentTemplate &document)
{
    document.title = QString("%1 %2%3").arg(ui->label_headerTitle->text()).arg(ui->dateEdit_dateStart->date().year()).arg(ui->label_dateEnd->text());
    document.studentName = ui->lineEdit_studentName->text();
    document.therapistName = ui->lineEdit_therapistName->text();
    document.therapistSignature = ui->lineEdit_therapistSignature->text();

    for(int i = 0; i < ui->stackedWidget_targetContentView->count(); ++i)
    {
        QLayout * layout = ui->stackedWidget_targetContentView->widget(i)->layout();
        table record;
        record.columnTarget = ui->stackedWidget_targetContentView->widget(i)->objectName();
        if(layout)
        {
            int count = 0;
            for (int j = 0; j < layout->count(); ++j)
            {
                QCheckBox * checkbox = qobject_cast<QCheckBox*>(layout->itemAt(j)->widget());
                if(checkbox->isChecked())
                {
                    record.columnMethods.append(checkbox->text());
                    count++;
                }
            }
        }

        if(record.columnMethods.count()>0)
        {
            document.table.append(record);
        }
    }

}

void DocumentPlanDialog::on_dateEdit_dateStart_userDateChanged(const QDate &date)
{
    ui->label_dateEnd->setText(QString("/%1").arg(ui->dateEdit_dateStart->date().year()+1));
}
