#include "resizetool.h"
#include <cmath>

ResizeTool::ResizeTool(Image &anImage, int x, int y) : anImage(anImage), x(x), y(y), pixelBuffer(anImage.getPixelBuffer()) {
    backupPixelBuffer = pixelBuffer;
}


// Scaling Logic
void ResizeTool::resize() {

    // Stay Within bounds
    if(x < 1)
    {
        x = 1;
    }

    if(y < 1)
    {
        y = 1;
    }

    if(x>10000)
    {
        x=10000;
    }

    if(y>10000)
    {
        y=10000;
    }

    // Resizing with ratios
    std::vector<Pixel> newPixelBuffer;
    newPixelBuffer.resize(y*x);
    double x_ratio = anImage.getWidth() / (double) x;
    double y_ratio = anImage.getHeight() / (double) y;
    double x1;
    double y1;
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            x1 = floor(j * x_ratio);
            y1 = floor(i * y_ratio);
            newPixelBuffer[i * x + j] = pixelBuffer[(int) ((y1 * anImage.getWidth()) + x1)];
        }
    }

    // Set the New
    backupW = anImage.getWidth();
    anImage.setWidth(x);
    backupH = anImage.getHeight();
    anImage.setHeight(y);
    pixelBuffer = newPixelBuffer;
}


// General Commands
void ResizeTool::execute() {
    resize();
}

void ResizeTool::undo() {
    pixelBuffer = backupPixelBuffer;
    anImage.setWidth(backupW);
    anImage.setHeight(backupH);
}

void ResizeTool::redo() {
    execute();
}

