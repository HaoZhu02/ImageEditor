#include "brightnesstool.h"
#include "../utilities.h"

BrightnessTool::BrightnessTool(Image &anImage, int value) : anImage(anImage), value(value), pixelBuffer(anImage.getPixelBuffer())
{
    backupPixelBuffer = pixelBuffer;
}


// Brightness Logic
void BrightnessTool::brightnessAdjust()
{
    // Turn the value to rgb range
    double normalizedValue = limitm100_100(value) * 2.55;


    // Adjustment for RGB, A remains unchanged
    for(int i=0; i < anImage.getSize(); i++)
    {
        pixelBuffer[i].setPixel(pixelBuffer[i].getR() + normalizedValue,
                                pixelBuffer[i].getG() + normalizedValue,
                                pixelBuffer[i].getB() + normalizedValue,
                                pixelBuffer[i].getA());
    }
}


// General Commands
void BrightnessTool::execute()
{
    brightnessAdjust();
}

void BrightnessTool::undo()
{
    pixelBuffer = backupPixelBuffer;
}

void BrightnessTool::redo()
{
    execute();
}
