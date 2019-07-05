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
