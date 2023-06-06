#include "blurtool.h"
#include "convolutionfilter.h"

BlurTool::BlurTool(Image &anImage) : anImage(anImage), pixelBuffer(anImage.getPixelBuffer()) {
    backupPixelBuffer = pixelBuffer;
}


// Blurring Logic
void BlurTool::blur(){

    // Blurring Kernel
    double blurConv[3][3] = {{1.0/9.0, 1.0/9.0, 1.0/9.0},
                                {1.0/9.0, 1.0/9.0,  1.0/9.0},
                                {1.0/9.0, 1.0/9.0, 1.0/9.0}};

    useConvolutionFilter(blurConv, anImage, pixelBuffer);

}


// General Commands
void BlurTool::execute() {
    blur();
}

void BlurTool::undo() {
    pixelBuffer = backupPixelBuffer;
}

void BlurTool::redo() {
    execute();
}
