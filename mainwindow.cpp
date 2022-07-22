#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include "binaryviewstate.h"
#include <QDebug>
#include <qmessagebox.h>
#include <QPixmap>
#include <QSizePolicy>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_SelectFile_clicked()
{
    QTextStream out(stdout);
    out << "test====" << endl;

    QString fileName = QFileDialog::getOpenFileName(this);
    if (fileName.isEmpty()) {
        return;
    }
    out << "open "<< fileName << endl;
    updateImagePathLabel(fileName);
}


// selected file label
void MainWindow::updateImagePathLabel(QString &fileName) {
    ui->PathLabel->setText(fileName);
    ui->PathLabel->setWordWrap(true);
    ui->PathLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

}

static int convertChannelTextToInt(QString channelText) {
    if(channelText.compare("Y channel") == 0) {
        return 1;
    }
    if(channelText.compare("RGB planar") == 0) {
        return 3;
    }
    if(channelText.compare("RGB packed") == 0) {
        return 3;
    }
    return 3;
}

static int convertTypeToElementSize(QString elementText) {
   if(elementText.compare("UINT8") == 0) {
       return 1;
   }
   if(elementText.compare("UINT16") == 0 || elementText.compare("INT16") == 0) {
       return 2;
   }
   if(elementText.compare("UINT32") == 0 || elementText.compare("INT32") == 0) {
       return 4;
   }
   qDebug() << "not support element size";
   return  0;
}

// confirm
void MainWindow::on_confirmButton_clicked() {
    auto width = ui->WidthEdit->text();
    auto height = ui->HeightEdit->text();
    auto filePath = ui->PathLabel->text();
    auto channel = convertChannelTextToInt(ui->ChannelType->currentText());
    auto elementSz = convertTypeToElementSize(ui->ElementType->currentText());

    BinaryViewState binaryViewState(filePath.toStdString(), height.toInt(), width.toInt(), elementSz, channel);

    qDebug() << "binary view is valid :" << binaryViewState.Valid();

    if(!binaryViewState.Valid()) {
        QMessageBox msgBox;
        msgBox.setText("Binary image not Valid!!!");
        msgBox.exec();
        return;
    }
    auto img = binaryViewState.GenerateQImage();
    ui->ImageLabel->setPixmap(QPixmap::fromImage(img));
    ui->ImageLabel->adjustSize();
}
