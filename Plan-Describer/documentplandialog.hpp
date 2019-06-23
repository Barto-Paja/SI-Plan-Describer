#ifndef DOCUMENTPLANDIALOG_HPP
#define DOCUMENTPLANDIALOG_HPP

#include <QDialog>
#include <QVBoxLayout>
#include <QCheckBox>
#include "documenttablesaggregate.hpp"

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

private slots:
    void on_comboBox_targetType_currentIndexChanged(int index);

private:
    Ui::DocumentPlanDialog *ui;

    QList<targetVariant> _variants;
};

#endif // DOCUMENTPLANDIALOG_HPP
