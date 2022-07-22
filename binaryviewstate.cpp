#include "binaryviewstate.h"
#include <QtCore>
#include <QImage>
#include <QFile>

BinaryViewState::BinaryViewState(std::string filePath, int height, int width, int elementSize, int channel, bool interleave):
    height_(height),
    width_(width),
    elementSize_(elementSize),
    channel_(channel),
    interleave_(interleave)
{
    const QString qFilePath = QString::fromStdString(filePath);
    fileHandler_.setFileName(qFilePath);
    if(!fileHandler_.exists()) {
        state_ = FileStateFileNotExist;
        qDebug() << "file path " << qFilePath << "not exixst";
        return;
    }
    fileSize_ = fileHandler_.size();
    qDebug() << "current file size" << fileSize_;
    CheckValid();
    if(isValid_) {
        dataVec_.resize(fileSize_);
        fileHandler_.open(QIODevice::ReadOnly);
        QDataStream out(&fileHandler_);
        out.readRawData((char*)(dataVec_.data()), fileSize_);
    }
}

void BinaryViewState::CheckValid() {
    if(fileSize_ != height_ * width_ * channel_ * elementSize_) {
        qDebug() << "file size not match !!";
        state_ = FileStateFileSizeNotValid;
        isValid_ = false;
        return;
    }
    isValid_ = true;
    state_ = FileStateCanShow;
}

QImage BinaryViewState::GenerateQImage() {
    QImage showImg(height_, width_, QImage::Format_Invalid);
    if(!isValid_) {
        return  showImg;
    }
    if(channel_ == 3) {
        if(elementSize_ == 1) {
            showImg = showImg.convertToFormat(QImage::Format_RGB888);
        }
    }
    if(channel_ == 1) {
        if(elementSize_ == 1) {
            showImg = QImage(dataVec_.data(), width_, height_, QImage::Format_Grayscale8);
        } else {
            showImg = QImage(dataVec_.data(), width_, height_, QImage::Format_Grayscale16);
        }
    }

    return showImg;
}

