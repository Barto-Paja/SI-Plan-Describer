#include "databaseeditordialog.h"
#include "ui_databaseeditordialog.h"

DataBaseEditorDialog::DataBaseEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataBaseEditorDialog)
{
    ui->setupUi(this);
    _dbProxy = new DocumentTablesAggregate("database.db3");

    if(!initDataBase()) { ui->label_error->setText("Załadowanie danych nie powiodło się"); }

}

DataBaseEditorDialog::~DataBaseEditorDialog()
{
    delete ui;
}

bool DataBaseEditorDialog::initDataBase()
{
   return _dbProxy->loadData();
}
