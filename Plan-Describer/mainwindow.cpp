#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_newDocument_clicked()
{
    DocumentPlanDialog dialog;
    dialog.setWindowTitle("Utwórz plan zajęć integrcji sensorycznej");
    dialog.loadData();
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::on_pushButton_exit_clicked()
{
    exit(0);
}

void MainWindow::on_pushButton_newSummaryPlan_clicked()
{
    DocumentSummaryPlanDialog dialog;
    dialog.setModal(true);
    dialog.exec();
}
