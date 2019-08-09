#include "documentsummaryplandialog.h"
#include "ui_documentsummaryplandialog.h"


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
        ui->label_title->setText(QString("<b>Ewaluacja planu zajęć integracji sensorycznej za rok szkolny %1/%2<b>").arg(document.dateStart.year()).arg(document.dateStart.year()+1));
        ui->label_studentName->setText(QString("<b>Imię i nazwisko:</b> %1").arg(document.studentName));
        ui->label_therapistName->setText(QString("<b>Terapeuta prowadzący:</b> %1").arg(document.therapistName));

        if(ui->scrollAreaWidgetContents->layout())
        {
            ui->scrollAreaWidgetContents->setLayout(nullptr);
        }

        QVBoxLayout *vLayout = new QVBoxLayout;

        QHBoxLayout *layout_header = new QHBoxLayout;
        layout_header->setSpacing(3);

        QLabel *label_header = new QLabel;
        label_header->setAlignment(Qt::AlignCenter);
        label_header->setText("<h2><b>Cel</b></h2>");
        label_header->setMinimumWidth(300);
//        label_header->setStyleSheet("QLabel { border: 1px solid black }");
        layout_header->addWidget(label_header);

        label_header = new QLabel;
        label_header->setAlignment(Qt::AlignCenter);
        label_header->setText("<h2><b>Zrealizowane umiejętności</b></h2>");
        label_header->setMinimumWidth(300);
//        label_header->setStyleSheet("QLabel { border: 1px solid black }");
        layout_header->addWidget(label_header);

        label_header = new QLabel;
        label_header->setAlignment(Qt::AlignCenter);
        label_header->setText("<h2><b>Uwagi</b></h2>");
        label_header->setMinimumWidth(300);
//        label_header->setStyleSheet("QLabel { border: 1px solid black }");
        layout_header->addWidget(label_header);

        vLayout->addItem(layout_header);

        for(int i = 0; i < document.targets.count(); ++i)
        {
            _records.append(row());

            QHBoxLayout *layout = new QHBoxLayout;
            layout->setSpacing(3);
            layout->setObjectName(QString("Record_%1").arg(i));

            _records.last()._ptrColumn0 = new QLabel();
            _records.last()._ptrColumn0->setObjectName(QString("Target_%1").arg(i));
            _records.last()._ptrColumn1 = new QPlainTextEdit();
            _records.last()._ptrColumn1->setObjectName(QString("Skills_%1").arg(i));
            _records.last()._ptrColumn2 = new QPlainTextEdit();
            _records.last()._ptrColumn2->setObjectName(QString("Notes_%1").arg(i));

            QLabel *label = _records.last()._ptrColumn0;
            label->setAlignment(Qt::AlignCenter);
            label->setText(document.targets[i]);
            label->setMinimumWidth(300);
            layout->addWidget(label);

            layout->addWidget(_records.last()._ptrColumn1);
            layout->addWidget(_records.last()._ptrColumn2);
            vLayout->addItem(layout);

            label->setStyleSheet("QLabel { border: 1px solid black }");
        }

        ui->scrollAreaWidgetContents->setLayout(vLayout);
       // ui->scrollArea->setLayout(vLayout);
        update();
    }


}

void DocumentSummaryPlanDialog::on_pushButton_generateFile_clicked()
{
    for(int i = 0; i < _records.count(); ++i)
    {
        qDebug() << _records.at(i)._ptrColumn0->objectName();
        _records.at(i)._ptrColumn1->appendHtml(QString("%1").arg(_records.at(i)._ptrColumn1->objectName()));
        _records.at(i)._ptrColumn2->appendHtml(QString("%1").arg(_records.at(i)._ptrColumn2->objectName()));
    }

    DocumentPrinter printer;
    documentTemplate _document;

    _document.title = ui->label_title->text();
    _document.studentName = ui->label_studentName->text();
    _document.therapistName = ui->label_therapistName->text();

}
