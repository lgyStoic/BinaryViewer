#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QTextStream out(stdout);
    out << "test====" << endl;

    QString fileName = QFileDialog::getOpenFileName(this);
    if (fileName.isEmpty()) {
        return;
    }
    out << "open "<< fileName << endl;


}
