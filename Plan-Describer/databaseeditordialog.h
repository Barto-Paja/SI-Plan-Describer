#ifndef DATABASEEDITORDIALOG_H
#define DATABASEEDITORDIALOG_H

#include <QDialog>
#include <QDateTime>
#include <QTableWidgetItem>
#include <QTableView>
#include <QMessageBox>
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

private slots:

    void itemClicked(QTableWidgetItem *item);
    void cellChanged(QTableWidgetItem *item);

    void on_pushButton_addNewTarget_clicked();

    void on_pushButton_addNewMethod_clicked();

private:
    Ui::DataBaseEditorDialog *ui;

    bool initDataBase();
    void fillViewData();
    void loadTargets();
    void loadMethods();


    QString translateBoolToWordValue(bool value);
    bool fromWordToBool(QString text);

    DocumentTablesAggregate *_dbProxy = nullptr;

    QString _oldValue;

};

#endif // DATABASEEDITORDIALOG_H
