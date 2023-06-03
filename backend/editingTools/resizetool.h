#ifndef RESIZETOOL_H
#define RESIZETOOL_H


#include "imageedit.h"
#include "../imagefile.h"

class ResizeTool : public ImageEdit {
private:
    Image &anImage;
    std::vector<Pixel>& pixelBuffer;
    std::vector<Pixel> backupPixelBuffer;
    int backupW;
    int backupH;
    int x;
    int y;

    // Scaling Logic
    void resize();

public:


    ResizeTool(Image &anImage, int x, int y);


    // General Commands
    void execute() override;
    void undo() override;
    void redo() override;

};

#endif // RESIZETOOL_H
