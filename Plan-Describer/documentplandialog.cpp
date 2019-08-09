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
        QList<target> variants = doc.variants();

        for (int i =0;i < variants.count();++i) {


            QVBoxLayout *layout = new QVBoxLayout;
            layout->setObjectName(QString("VBox_%1").arg(i));
            for (int j = 0;j < variants[i].methods.count(); ++j) {

                layout->addWidget(new QCheckBox(variants[i].methods[j].name));
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
    printer.printFile(document,ui->lineEdit_studentName->text());

    DocumentParser parser;
    documentCoreSave documentSave;
    prepareDocumentCoreSave(documentSave);
    QFile file(QString("%1.xml").arg(ui->lineEdit_studentName->text()));
    file.open(QIODevice::WriteOnly);
    file.write(parser.generateXML(documentSave));
    file.close();
}

void DocumentPlanDialog::prepareDocumentTemplate(documentTemplate &document)
{
    document.title = QString("%1 %2%3").arg(ui->label_headerTitle->text()).arg(ui->dateEdit_dateStart->date().year()).arg(ui->label_dateEnd->text());
    document.studentName = ui->lineEdit_studentName->text();
    document.therapistName = ui->lineEdit_therapistName->text();
    document.therapistSignature = ui->lineEdit_therapistSignature->text();
    document.note = plan_core_target;
    document.headers.append("Cel");
    document.headers.append("Metody i środki realizacji");

    for(int i = 0; i < ui->stackedWidget_targetContentView->count(); ++i)
    {
        QLayout * layout = ui->stackedWidget_targetContentView->widget(i)->layout();
        QList<QString> records;


        if(layout)
        {
            for(int j = 0; j < layout->count(); ++j)
            {
                QCheckBox * checkbox = qobject_cast<QCheckBox*>(layout->itemAt(j)->widget());
                if(checkbox->isChecked())
                {
                    records.append(checkbox->text());
                }
            }
        }

        if(records.count() > 0 )
        {
            QList<QString> row;
            row.append(ui->stackedWidget_targetContentView->widget(i)->objectName());
            row.append(compressListtoHTMLCell(records));
            document.rows.append(row);
        }
    }


}

void DocumentPlanDialog::prepareDocumentCoreSave(documentCoreSave &document)
{
    document.dateStart = ui->dateEdit_dateStart->date();
    document.studentName = ui->lineEdit_studentName->text();
    document.therapistName = ui->lineEdit_therapistName->text();

    for(int i = 0; i < ui->stackedWidget_targetContentView->count(); ++i)
    {
        QLayout * layout = ui->stackedWidget_targetContentView->widget(i)->layout();
        QString columnTargetCell = ui->stackedWidget_targetContentView->widget(i)->objectName();
        int count = 0;
        if(layout)
        {
            for (int j = 0; j < layout->count(); ++j)
            {
                QCheckBox * checkbox = qobject_cast<QCheckBox*>(layout->itemAt(j)->widget());
                if(checkbox->isChecked())
                {
                    count++;
                }
            }
        }

        if(count>0)
        {
            document.targets.append(columnTargetCell);
        }
    }
}

QString DocumentPlanDialog::compressListtoHTMLCell(QList<QString> list)
{
    QString content;

    for(int i = 0; i < list.count(); ++i)
    {
        if(i>0)
        {
           content.append(QString("<br>- %1").arg(list[i]));
        }
        else
        {
           content.append(QString("- %1").arg(list[i]));
        }
    }

    return content;
}

void DocumentPlanDialog::on_dateEdit_dateStart_userDateChanged(const QDate &date)
{
    ui->label_dateEnd->setText(QString("/%1").arg(ui->dateEdit_dateStart->date().year()+1));
}
