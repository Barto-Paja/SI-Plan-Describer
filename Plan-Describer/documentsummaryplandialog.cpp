#include "documentsummaryplandialog.h"
#include "ui_documentsummaryplandialog.h"

#include <QPlainTextEdit>
#include <QDebug>

DocumentSummaryPlanDialog::DocumentSummaryPlanDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DocumentSummaryPlanDialog)
{
    ui->setupUi(this);
}

DocumentSummaryPlanDialog::~DocumentSummaryPlanDialog()
{
    delete ui;
}

void DocumentSummaryPlanDialog::on_pushButton_browse_clicked()
{
    _path = QDir(QFileDialog::getOpenFileName(this, tr("Choose catalog"), QDir::homePath()));

    ui->label_browse->setText(_path.path());
}

void DocumentSummaryPlanDialog::on_pushButton_load_clicked()
{
    QFile file(_path.path());

    documentCoreSave document;
    DocumentParser parser;

    if(parser.readXML(file,document))
    {
        ui->label_title->setText(QString("Plan ewaluacyjny za rok szkolny %1/%2").arg(document.dateStart.year()).arg(document.dateStart.year()+1));
        ui->label_studentName->setText(QString("Imię i nazwisko: %1").arg(document.studentName));
        ui->label_therapistName->setText(QString("Terapeuta prowadzący: %1").arg(document.therapistName));

        QVBoxLayout *vLayout = new QVBoxLayout;

        for(int i = 0; i < document.targets.count(); ++i)
        {
            QHBoxLayout *layout = new QHBoxLayout;
            layout->setSpacing(3);
            layout->setObjectName(QString("Target_%1").arg(i));
            QLabel *label = new QLabel;
            label->setText(document.targets[i]);
            layout->addWidget(label);
            label->setMinimumSize(200,200);
            layout->addWidget(new QPlainTextEdit());
            layout->addWidget(new QPlainTextEdit());
            vLayout->addItem(layout);
            label->setStyleSheet("QLabel { border: 1px solid black }");
        }

        ui->scrollArea->setLayout(vLayout);
        update();
    }


}
