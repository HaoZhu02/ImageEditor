#include "grayscaletool.h"


GrayScaleTool::GrayScaleTool(Image &anImage) : anImage(anImage), pixelBuffer(anImage.getPixelBuffer()) {
    backupPixelBuffer = pixelBuffer;
}

// GrayScale Logic
void GrayScaleTool::grayScale() {

    for (int y = 0; y < anImage.getHeight(); y++) //rows
        for (int x = 0; x < anImage.getWidth(); x++) { //columns
            int gray =
                0.2126 * pixelBuffer[y *
                                         anImage.getWidth() + x].getR() + 0.7125 * pixelBuffer[y
                                           * anImage.getWidth() + x].getG() + 0.0722 *
                      pixelBuffer[y * anImage.getWidth() + x].getB();

            pixelBuffer[y * anImage.getWidth() +
                        x].setPixel(gray, gray, gray, pixelBuffer[y * anImage.getWidth() + x].getA());
        }

}

void GrayScaleTool::execute() {
    grayScale();
}

void GrayScaleTool::undo() {
    pixelBuffer = backupPixelBuffer;
}

void GrayScaleTool::redo() {
    execute();
}

