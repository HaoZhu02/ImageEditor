#include "sharpentool.h"
#include "convolutionfilter.h"

SharpenTool::SharpenTool(Image &anImage) : anImage(anImage), pixelBuffer(anImage.getPixelBuffer()) {
    backupPixelBuffer = pixelBuffer;
}


// Sharpening Logic
void SharpenTool::sharpen(){

    // Laplacian Kernel
    double sharpenConv[3][3] = {{0, -1, 0},
                               {-1, 5,  -1},
                               {0, -1, 0}};

    useConvolutionFilter(sharpenConv, anImage, pixelBuffer);

}


// General Commands
void SharpenTool::execute() {
    sharpen();
}

void SharpenTool::undo() {
    pixelBuffer = backupPixelBuffer;
}

void SharpenTool::redo() {
    execute();
}


