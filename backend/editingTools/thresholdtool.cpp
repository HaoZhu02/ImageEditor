#include "thresholdtool.h"


ThresholdTool::ThresholdTool(Image &anImage, int value) : anImage(anImage), value(value), pixelBuffer(anImage.getPixelBuffer()) {
    backupPixelBuffer = pixelBuffer;
}

// Threshold Logic
void ThresholdTool::threshold() {

    for (int y = 0; y < anImage.getHeight(); y++)
    {
        for (int x = 0; x < anImage.getWidth(); x++)
        {
            int intensity = (pixelBuffer[y * anImage.getWidth() + x].getR() +
                             pixelBuffer[y * anImage.getWidth() + x].getG() +
                             pixelBuffer[y * anImage.getWidth() + x].getB()) / 3;

            if (intensity > value)
            {
                pixelBuffer[y * anImage.getWidth() + x].setPixel(255, 255, 255, pixelBuffer[y * anImage.getWidth() + x].getA()); // Set pixel to white
            } else {
                pixelBuffer[y * anImage.getWidth() + x].setPixel(0, 0, 0, pixelBuffer[y * anImage.getWidth() + x].getA()); // Set pixel to black
            }
        }
    }

}


// General Commands
void ThresholdTool::execute() {
    threshold();
}

void ThresholdTool::undo() {
    pixelBuffer = backupPixelBuffer;
}

void ThresholdTool::redo() {
    execute();
}
