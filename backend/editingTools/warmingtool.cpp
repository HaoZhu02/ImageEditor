#include "warmingtool.h"


WarmingTool::WarmingTool(Image &anImage) : anImage(anImage), pixelBuffer(anImage.getPixelBuffer()) {
    backupPixelBuffer = pixelBuffer;
}

// Warming Logic
void WarmingTool::warming() {

    for (int y = 0; y < anImage.getHeight(); y++)      // Rows
    {
        for (int x = 0; x < anImage.getWidth(); x++)   // Columns
        {
            int red = pixelBuffer[y * anImage.getWidth() + x].getR();
            int green = pixelBuffer[y * anImage.getWidth() + x].getG();
            int blue = pixelBuffer[y * anImage.getWidth() + x].getB();

            // Increase red and green channels, reduce blue channel
            red = std::min(255, red + 50);          // Increase red channel by 50
            green = std::min(255, green + 30);      // Increase green channel by 30
            blue = std::max(0, blue - 20);          // Reduce blue channel by 20

            pixelBuffer[y * anImage.getWidth() + x].setPixel(red, green, blue, pixelBuffer[y * anImage.getWidth() + x].getA());
        }
    }

}


// General Commands
void WarmingTool::execute() {
    warming();
}

void WarmingTool::undo() {
    pixelBuffer = backupPixelBuffer;
}

void WarmingTool::redo() {
    execute();
}
