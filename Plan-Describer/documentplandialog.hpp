#ifndef DOCUMENTPLANDIALOG_HPP
#define DOCUMENTPLANDIALOG_HPP

#include <QDialog>
#include <QVBoxLayout>
#include <QCheckBox>
#include "documenttablesaggregate.hpp"
#include "documentprinter.hpp"

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
    void on_pushButton_generateFile_clicked();
    void on_dateEdit_dateStart_userDateChanged(const QDate &date);

private:
    Ui::DocumentPlanDialog *ui;
    void prepareDocumentTemplate(documentTemplate &document);
};

#endif // DOCUMENTPLANDIALOG_HPP
