#ifndef GRAYSCALETOOL_H
#define GRAYSCALETOOL_H


#include "imageedit.h"
#include "../imagefile.h"

class GrayScaleTool : public ImageEdit {
private:
    Image &anImage;
    std::vector<Pixel>& pixelBuffer;
    std::vector<Pixel> backupPixelBuffer;

    // GrayScale logic
    void grayScale();

public:

    // Explicit Constructor
    explicit GrayScaleTool(Image &anImage);


    // General Commands
    void execute() override;

    void undo() override;

    void redo() override;
};

#endif // GRAYSCALETOOL_H
