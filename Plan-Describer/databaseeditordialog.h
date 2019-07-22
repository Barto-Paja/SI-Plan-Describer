#ifndef DATABASEEDITORDIALOG_H
#define DATABASEEDITORDIALOG_H

#include <QDialog>

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
};

#endif // DATABASEEDITORDIALOG_H
