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
