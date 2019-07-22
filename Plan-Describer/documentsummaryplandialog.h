#ifndef DOCUMENTSUMMARYPLANDIALOG_H
#define DOCUMENTSUMMARYPLANDIALOG_H

#include <QDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include "documentparser.hpp"

namespace Ui {
class DocumentSummaryPlanDialog;
}

class DocumentSummaryPlanDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DocumentSummaryPlanDialog(QWidget *parent = nullptr);
    ~DocumentSummaryPlanDialog();

private slots:
    void on_pushButton_browse_clicked();

    void on_pushButton_load_clicked();

private:
    Ui::DocumentSummaryPlanDialog *ui;

    QDir _path;
};

#endif // DOCUMENTSUMMARYPLANDIALOG_H
