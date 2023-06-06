#ifndef COOLINGTOOL_H
#define COOLINGTOOL_H


#include "imageedit.h"
#include "../imagefile.h"


class CoolingTool : public ImageEdit
{
private:
    Image &anImage;
    std::vector<Pixel>& pixelBuffer;
    std::vector<Pixel> backupPixelBuffer;

    // Cooling logic
    void cooling();

public:

    // Explicit Constructor
    explicit CoolingTool(Image &anImage);


    // General Commands
    void execute() override;

    void undo() override;

    void redo() override;
};

#endif // COOLINGTOOL_H
