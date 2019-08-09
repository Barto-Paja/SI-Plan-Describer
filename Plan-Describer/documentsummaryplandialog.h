#ifndef DOCUMENTSUMMARYPLANDIALOG_H
#define DOCUMENTSUMMARYPLANDIALOG_H

#include <QDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>

#include <QLabel>
#include <QPlainTextEdit>
#include <QDebug>

#include "documentparser.hpp"

namespace Ui {
class DocumentSummaryPlanDialog;
}

class DocumentSummaryPlanDialog : public QDialog
{
    Q_OBJECT

    struct row {
        QLabel *_ptrColumn0 = nullptr;
        QPlainTextEdit *_ptrColumn1 = nullptr;
        QPlainTextEdit *_ptrColumn2 = nullptr;
    };

public:
    explicit DocumentSummaryPlanDialog(QWidget *parent = nullptr);
    ~DocumentSummaryPlanDialog();

private slots:
    void on_pushButton_browse_clicked();

    void on_pushButton_load_clicked();

    void on_pushButton_generateFile_clicked();

private:
    Ui::DocumentSummaryPlanDialog *ui;

    QDir _path;
    QList<DocumentSummaryPlanDialog::row> _records;
};

#endif // DOCUMENTSUMMARYPLANDIALOG_H
