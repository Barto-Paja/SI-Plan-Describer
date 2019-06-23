#ifndef DOCUMENTPLANDIALOG_HPP
#define DOCUMENTPLANDIALOG_HPP

#include <QDialog>

namespace Ui {
class DocumentPlanDialog;
}

class DocumentPlanDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DocumentPlanDialog(QWidget *parent = nullptr);
    ~DocumentPlanDialog();

    bool loadData();

private:
    Ui::DocumentPlanDialog *ui;
};

#endif // DOCUMENTPLANDIALOG_HPP
