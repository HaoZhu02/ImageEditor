#ifndef BLURTOOL_H
#define BLURTOOL_H


#include "imageedit.h"
#include "../imagefile.h"

class BlurTool : public ImageEdit
{
private:

    // Data members
    Image &anImage;
    std::vector<Pixel>& pixelBuffer;
    std::vector<Pixel> backupPixelBuffer;

    // Blurring Logic
    void blur();

public:

    // Explicit Constructor
    explicit BlurTool(Image &anImage);


    // General Commands
    void execute() override;

    void undo() override;

    void redo() override;
};

#endif // BLURTOOL_H
