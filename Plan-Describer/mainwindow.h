#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "documentplandialog.hpp"
#include "documentsummaryplandialog.h"
#include "databaseeditordialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_newDocument_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_newSummaryPlan_clicked();

    void on_action_manageDictionaries_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
