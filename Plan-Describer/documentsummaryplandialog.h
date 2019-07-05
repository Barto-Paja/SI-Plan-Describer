#ifndef DOCUMENTSUMMARYPLANDIALOG_H
#define DOCUMENTSUMMARYPLANDIALOG_H

#include <QDialog>

namespace Ui {
class DocumentSummaryPlanDialog;
}

class DocumentSummaryPlanDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DocumentSummaryPlanDialog(QWidget *parent = nullptr);
    ~DocumentSummaryPlanDialog();

private:
    Ui::DocumentSummaryPlanDialog *ui;
};

#endif // DOCUMENTSUMMARYPLANDIALOG_H
