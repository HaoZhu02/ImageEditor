#ifndef SHARPENTOOL_H
#define SHARPENTOOL_H


#include "imageedit.h"
#include "../imagefile.h"

class SharpenTool : public ImageEdit {
private:

    // Data members
    Image &anImage;
    std::vector<Pixel>& pixelBuffer;
    std::vector<Pixel> backupPixelBuffer;

    // Sharpening Logic
    void sharpen();

public:

    // Explicit Constructor
    explicit SharpenTool(Image &anImage);


    // General Commands
    void execute() override;

    void undo() override;

    void redo() override;
};

#endif // SHARPENTOOL_H
