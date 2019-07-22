#include "databaseeditordialog.h"
#include "ui_databaseeditordialog.h"

DataBaseEditorDialog::DataBaseEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataBaseEditorDialog)
{
    ui->setupUi(this);
}

DataBaseEditorDialog::~DataBaseEditorDialog()
{
    delete ui;
}
