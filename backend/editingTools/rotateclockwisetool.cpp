#include "rotateclockwisetool.h"

RotateClockwiseTool::RotateClockwiseTool(Image &anImage) : anImage(anImage), pixelBuffer(anImage.getPixelBuffer())
{
    backupPixelBuffer = pixelBuffer;
}


// Rotate Clockwise Logic
void RotateClockwiseTool::rotateClockwise()
{
    std::vector<Pixel> tempPixelBuffer = pixelBuffer;
    for (int i = 0; i < anImage.getWidth(); i++)
        for (int j = 0; j < anImage.getHeight(); j++)
            pixelBuffer[i * anImage.getHeight() + j] = tempPixelBuffer[(anImage.getHeight() - j - 1) * anImage.getWidth() + i];

    anImage.swapDimension();
}


// General Commands
void RotateClockwiseTool::execute()
{
    rotateClockwise();
}

void RotateClockwiseTool::undo()
{
    pixelBuffer = backupPixelBuffer;
    anImage.swapDimension();
}

void RotateClockwiseTool::redo()
{
    execute();
}

