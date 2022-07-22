#ifndef BINARYVIEWSTATE_H
#define BINARYVIEWSTATE_H
#include <string>
#include <QFile>
#include <vector>

enum FileState {
    FileStateCanShow = 0,
    FileStateFileNotExist,
    FileStateFileSizeNotValid,
    FileStateUnknow
};

class BinaryViewState
{
    int height_ = 0;
    int width_ = 0;
    int elementSize_ = 0;
    int channel_ = 0;
    bool interleave_ = false;

    QFile fileHandler_;
    int fileSize_ = 0;

    bool isValid_ = false;

    FileState state_ = FileStateUnknow;

    void CheckValid();

    std::vector<uchar> dataVec_;

public:
    explicit BinaryViewState(std::string filePath, int height, int width, int elementSize, int channel, bool interleave = false);

    bool Valid() {
        return isValid_;
    }

    QImage GenerateQImage();
};

#endif // BINARYVIEWSTATE_H
