#ifndef WARMINGTOOL_H
#define WARMINGTOOL_H

#include "imageedit.h"
#include "../imagefile.h"


class WarmingTool : public ImageEdit
{
private:
    Image &anImage;
    std::vector<Pixel>& pixelBuffer;
    std::vector<Pixel> backupPixelBuffer;

    // Warming logic
    void warming();

public:

    // Explicit Constructor
    explicit WarmingTool(Image &anImage);


    // General Commands
    void execute() override;

    void undo() override;

    void redo() override;
};

#endif // WARMINGTOOL_H
