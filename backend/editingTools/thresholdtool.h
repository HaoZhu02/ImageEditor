#ifndef THRESHOLDTOOL_H
#define THRESHOLDTOOL_H

#include "imageedit.h"
#include "../imagefile.h"


class ThresholdTool : public ImageEdit
{
private:
    Image &anImage;
    std::vector<Pixel>& pixelBuffer;
    std::vector<Pixel> backupPixelBuffer;
    int value;

    // Threshold logic
    void threshold();

public:

    // Explicit Constructor
    explicit ThresholdTool(Image &anImage, int value);


    // General Commands
    void execute() override;

    void undo() override;

    void redo() override;
};

#endif // THRESHOLDTOOL_H
