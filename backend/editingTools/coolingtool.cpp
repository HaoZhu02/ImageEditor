#include "coolingtool.h"


CoolingTool::CoolingTool(Image &anImage) : anImage(anImage), pixelBuffer(anImage.getPixelBuffer()) {
    backupPixelBuffer = pixelBuffer;
}

// Cooling Logic
void CoolingTool::cooling() {

    for (int y = 0; y < anImage.getHeight(); y++)           // Rows
    {
        for (int x = 0; x < anImage.getWidth(); x++)        // Columns
        {
            int red = pixelBuffer[y * anImage.getWidth() + x].getR();
            int green = pixelBuffer[y * anImage.getWidth() + x].getG();
            int blue = pixelBuffer[y * anImage.getWidth() + x].getB();

            // Reduce red and green channels, increase blue channel
            red = std::max(0, red - 20);                    // Reduce red channel by 20
            green = std::max(0, green - 30);                // Reduce green channel by 30
            blue = std::min(255, blue + 50);                // Increase blue channel by 50

            pixelBuffer[y * anImage.getWidth() + x].setPixel(red, green, blue, pixelBuffer[y * anImage.getWidth() + x].getA());
        }
    }

}


// General Commands
void CoolingTool::execute() {
    cooling();
}

void CoolingTool::undo() {
    pixelBuffer = backupPixelBuffer;
}

void CoolingTool::redo() {
    execute();
}
