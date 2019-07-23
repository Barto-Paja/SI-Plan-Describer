#ifndef DATABASEEDITORDIALOG_H
#define DATABASEEDITORDIALOG_H

#include <QDialog>

#include "documenttablesaggregate.hpp"

namespace Ui {
class DataBaseEditorDialog;
}

class DataBaseEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataBaseEditorDialog(QWidget *parent = nullptr);
    ~DataBaseEditorDialog();

private:
    Ui::DataBaseEditorDialog *ui;

    bool initDataBase();

    DocumentTablesAggregate *_dbProxy = nullptr;

};

#endif // DATABASEEDITORDIALOG_H
