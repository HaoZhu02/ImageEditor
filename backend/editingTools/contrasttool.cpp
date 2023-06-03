#include "contrasttool.h"
#include "../utilities.h"

ContrastTool::ContrastTool(Image& anImage, int contrastValue) : anImage(anImage),
        contrastValue(contrastValue), pixelBuffer(anImage.getPixelBuffer())
{
    backupPixelBuffer = pixelBuffer;
}


// Contrast Logic
void ContrastTool::contrast()
{

    double normalizedContrast = limitm100_100(contrastValue) * 2.55;
    double factor = (259.0 * (normalizedContrast + 255)) / (255.0 * (259 - normalizedContrast));

    // Pixel adjustment by the factor
    for (int i = 0; i < anImage.getSize(); i++) {
        pixelBuffer[i].setPixel(factor * (pixelBuffer[i].getR() - 128) + 128,
                                factor * (pixelBuffer[i].getG() - 128) + 128,
                                factor * (pixelBuffer[i].getB() - 128) + 128,
                                pixelBuffer[i].getA());
    }
}


// General Commands
void ContrastTool::execute()
{
    contrast();
}

void ContrastTool::undo()
{
    pixelBuffer = backupPixelBuffer;
}

void ContrastTool::redo()
{
    execute();
}

