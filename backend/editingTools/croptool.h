#ifndef CROPTOOL_H
#define CROPTOOL_H

#include "imageedit.h"
#include "../imagefile.h"

/* Cropping Logic */
class CropTool : public ImageEdit
{

private:

    // Reference and Backup
    Image& originalImage;
    Image backupImage;
    std::vector<Pixel>& pixelBuffer;
    std::vector<Pixel> backupPixelBuffer;
    QImage tempImage;
    int topLeftX;
    int topLeftY;
    int width;
    int height;

    // Cropping
    void crop();
    void cropLimit();

public:
    // Constructor
    explicit CropTool(Image &originalImage, int topLeftX, int topLeftY, int width, int height);

    // General Commands
    void execute() override;

    void undo() override;

    void redo() override;


    Image& getImage();
    QImage& getTemp();
};


#endif
