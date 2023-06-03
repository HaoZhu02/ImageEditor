#ifndef ROTATECLOCKWISETOOL_H
#define ROTATECLOCKWISETOOL_H

#include "imageedit.h"
#include "../imagefile.h"


class RotateClockwiseTool : public ImageEdit
{
private:
    Image &anImage;
    std::vector<Pixel>& pixelBuffer;
    std::vector<Pixel> backupPixelBuffer;

    void rotateClockwise();

public:
    explicit RotateClockwiseTool(Image &image);

    void execute() override;

    void undo() override;

    void redo() override;
};

#endif // ROTATECLOCKWISETOOL_H
