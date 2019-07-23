#include "databaseeditordialog.h"
#include "ui_databaseeditordialog.h"

DataBaseEditorDialog::DataBaseEditorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataBaseEditorDialog)
{
    ui->setupUi(this);
    _dbProxy = new DocumentTablesAggregate("database.db3");

    if(!initDataBase())
    {
        ui->label_error->setText("Załadowanie danych nie powiodło się");
    }
    else
    {
        fillViewData();
    }

}

DataBaseEditorDialog::~DataBaseEditorDialog()
{
    delete ui;
}

void DataBaseEditorDialog::itemClicked(QTableWidgetItem *item)
{
    int column = item->column();
    int row = item->row();


    if(column == 1)
    {
        if(fromWordToBool(item->text()))
        {

            QString name = ui->tableWidget_targets->item(row,0)->text();
            _tempOrders << QString("UPDATE target SET is_used = %1 WHERE name = %2").arg(0).arg(name);
            ui->plainTextEdit_log->appendHtml(QString("---- %1 ---- <br> Zmieniono stan używania z <b>'TAK'</b> na <b>'NIE'</b> dla rekordu <i>%2</i>")
                                            .arg(QDateTime::currentDateTime().toString())
                                            .arg(name));
            ui->tableWidget_targets->item(row,1)->setText("Nie");
            ui->tableWidget_targets->update();
            update();
        }
        else
        {
            QString name = ui->tableWidget_targets->item(row,0)->text();
            _tempOrders << QString("UPDATE target SET is_used = %1 WHERE name = %2").arg(1).arg(name);
            ui->plainTextEdit_log->appendHtml(QString("---- %1 ---- <br> Zmieniono stan używania z <b>'NIE'</b> na <b>'TAK'</b> dla rekordu <i>%2</i>")
                                            .arg(QDateTime::currentDateTime().toString())
                                            .arg(name));
            ui->tableWidget_targets->item(row,1)->setText("Tak");
            ui->tableWidget_targets->update();
            update();
        }
    }

    if(column == 0)
    {
        qDebug() << item->tableWidget()->objectName();
        qDebug() << item->text();
    }
}

bool DataBaseEditorDialog::initDataBase()
{
    return _dbProxy->loadData();
}

void DataBaseEditorDialog::fillViewData()
{
    loadTargets();
    loadMethods();
}

void DataBaseEditorDialog::loadTargets()
{
    QStringList headers;
    headers << tr("Nazwa Celu") << tr("Czy włączony?");

    auto data = _dbProxy->variants();

    ui->tableWidget_targets->setColumnCount(2);
    ui->tableWidget_targets->setHorizontalHeaderLabels(headers);
    ui->tableWidget_targets->horizontalHeader()->update();

    for(int i = 0; i < data.count(); ++i )
    {
        int row = ui->tableWidget_targets->rowCount();
        ui->tableWidget_targets->insertRow(row);
        ui->tableWidget_targets->setItem(row,0,new QTableWidgetItem(data[i].name));
        QTableWidgetItem *item = new QTableWidgetItem(translateBoolToWordValue(data[i].isUsing));
        auto flags = item->flags();
        item->setFlags(flags & (~Qt::ItemIsEditable));
        ui->tableWidget_targets->setItem(row,1,item);
    }

    connect(ui->tableWidget_targets,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(itemClicked(QTableWidgetItem*)));

    update();
}

void DataBaseEditorDialog::loadMethods(int target_index)
{
    QStringList headers;
    headers << tr("Nazwa Metody");

    auto data = _dbProxy->variants();

    ui->tableWidget_methods->setColumnCount(1);
    ui->tableWidget_methods->setHorizontalHeaderLabels(headers);
    ui->tableWidget_methods->horizontalHeader()->update();

    for(int i = 0; i < data[target_index].variants.count(); ++i )
    {
        int row = ui->tableWidget_methods->rowCount();
        ui->tableWidget_methods->insertRow(row);
        ui->tableWidget_methods->setItem(row,0,new QTableWidgetItem(data[target_index].variants[i]));
    }

    connect(ui->tableWidget_methods,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(itemClicked(QTableWidgetItem*)));

    update();
}

QString DataBaseEditorDialog::translateBoolToWordValue(bool value)
{
    if(value){ return "Tak"; } else { return "Nie"; }
}

bool DataBaseEditorDialog::fromWordToBool(QString text)
{
    if(QString::compare(text,QString("Tak"),Qt::CaseInsensitive))
    {
        return false;
    }

    return true;
}
