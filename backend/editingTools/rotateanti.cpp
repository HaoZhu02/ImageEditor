#include "rotateanti.h"

RotateAnti::RotateAnti(Image &anImage) : anImage(anImage), pixelBuffer(anImage.getPixelBuffer())
{
    backupPixelBuffer = pixelBuffer;
}


// Rotate Clockwise Logic
void RotateAnti::rotateAnti()
{
    std::vector<Pixel> tempPixelBuffer = pixelBuffer;
    for (int i = 0; i < anImage.getWidth(); i++)      //Row
    {
        for (int j = 0; j < anImage.getHeight(); j++) //Columns
        {
            pixelBuffer[(anImage.getWidth() - i - 1) * anImage.getHeight() + j] = tempPixelBuffer[j * anImage.getWidth() + i];
        }
    }
    anImage.swapDimension();
}


// General Commands
void RotateAnti::execute()
{
    rotateAnti();
}

void RotateAnti::undo()
{
    pixelBuffer = backupPixelBuffer;
    anImage.swapDimension();
}

void RotateAnti::redo()
{
    execute();
}

