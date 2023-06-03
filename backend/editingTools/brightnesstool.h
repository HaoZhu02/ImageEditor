#ifndef BRIGHTNESSTOOL_H
#define BRIGHTNESSTOOL_H

#include "imageedit.h"
#include "../imagefile.h"

class BrightnessTool : public ImageEdit
{

private:
    Image& anImage;
    std::vector<Pixel>& pixelBuffer;
    std::vector<Pixel> backupPixelBuffer;
    int value;

    void brightnessAdjust();

public:
    explicit BrightnessTool(Image& anImage, int value);

    void execute() override;

    void undo() override;

    void redo() override;

};

#endif // BRIGHTNESSTOOL_H
