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
            QHBoxLayout *layout = new QHBoxLayout;
            layout->setSpacing(3);
            layout->setObjectName(QString("Target_%1").arg(i));
            QLabel *label = new QLabel;
            label->setAlignment(Qt::AlignCenter);
            label->setText(document.targets[i]);
            label->setMinimumWidth(300);
            layout->addWidget(label);
            layout->addWidget(new QPlainTextEdit(QString("Skills_%1").arg(i)));
            layout->addWidget(new QPlainTextEdit(QString("Notes_%1").arg(i)));
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

}
