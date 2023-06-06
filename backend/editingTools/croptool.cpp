#include "croptool.h"

// Explicit Constructor
CropTool::CropTool(Image &originalImage, int topLeftX, int topLeftY, int width, int height)
    : originalImage(originalImage), topLeftX(topLeftX), topLeftY(topLeftY),
    width(width), height(height), pixelBuffer(originalImage.getPixelBuffer()), backupImage(nullptr)
{
    backupPixelBuffer = pixelBuffer;
    backupImage = originalImage;
}

// Cropping Logic
void CropTool::crop()
{
    // Limit the crop inputs
    cropLimit();


    // Crops at points
    tempImage = originalImage.getQImage().copy(topLeftX, topLeftY, width, height);
    Image fooImage(tempImage);
    fooImage.setFilePath(originalImage.getPath());

    originalImage = fooImage;

    // Sets the QImage and Buffer
    //originalImage.setQImage(fooImage.getQImage());
    //originalImage.updateBuffer();
    //pixelBuffer = fooImage.getPixelBuffer();
}


// Helper function to limit/border Crop inputs
void CropTool::cropLimit()
{
    if(topLeftX < 0)
    {
        topLeftX = 0;
    }

    if(topLeftX > originalImage.getWidth())
    {
        topLeftX = originalImage.getWidth();
    }

    if(topLeftY < 0)
    {
        topLeftY = 0;
    }

    if(topLeftY > originalImage.getHeight())
    {
        topLeftY = originalImage.getHeight();
    }

    if(width <= 0)
    {
        width = 1;
    }

    if(width > originalImage.getWidth() - topLeftX)
    {
        width = originalImage.getWidth() - topLeftX;
    }

    if(height <= 0)
    {
        height = 1;
    }

    if(height > originalImage.getHeight() - topLeftY)
    {
        height = originalImage.getHeight() - topLeftY;
    }
}






// General Commands
void CropTool::execute()
{
    crop();
}

void CropTool::undo()
{
    originalImage = backupImage;

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




