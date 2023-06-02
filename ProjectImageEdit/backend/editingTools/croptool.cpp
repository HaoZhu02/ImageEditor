#include "croptool.h"

// Explicit Constructor
CropTool::CropTool(Image &originalImage, int topLeftX, int topLeftY, int width, int height)
    : originalImage(originalImage), topLeftX(topLeftX), topLeftY(topLeftY),
        width(width), height(height), pixelBuffer(originalImage.getPixelBuffer())
{
    backupPixelBuffer = pixelBuffer;
}

// Cropping Logic
void CropTool::crop()
{

    // Crops at points
    tempImage = originalImage.getQImage().copy(topLeftX, topLeftY, width, height);
    Image fooImage(tempImage);
    fooImage.setFilePath(originalImage.getPath());

    originalImage = fooImage;

    // Sets the QImage and Buffer
    //originalImage.setQImage(fooImage.getQImage());
    //originalImage.updateBuffer();
    pixelBuffer = fooImage.getPixelBuffer();
}



// General Commands
void CropTool::execute()
{
    crop();
}

void CropTool::undo()
{
    pixelBuffer = backupPixelBuffer;
}

void CropTool::redo()
{
    execute();
}


// Test Command
Image& CropTool::getImage()
{
    return this->originalImage;
}

QImage& CropTool::getTemp()
{
    return this->tempImage;
}




