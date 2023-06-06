#ifndef ROTATEANTI_H
#define ROTATEANTI_H


#include "imageedit.h"
#include "../imagefile.h"


class RotateAnti : public ImageEdit
{
private:
    Image &anImage;
    std::vector<Pixel>& pixelBuffer;
    std::vector<Pixel> backupPixelBuffer;

    void rotateAnti();

public:
    explicit RotateAnti(Image &image);

    void execute() override;

    void undo() override;

    void redo() override;
};

#endif // ROTATEANTI_H
