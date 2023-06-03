#ifndef CONTRASTTOOL_H
#define CONTRASTTOOL_H


#include "imageedit.h"
#include "../imagefile.h"

class ContrastTool : public ImageEdit {
private:

    // Data Members
    Image &anImage;
    std::vector<Pixel>& pixelBuffer;
    std::vector<Pixel> backupPixelBuffer;
    int contrastValue;

    // Contrast Logic
    void contrast();

public:
    explicit ContrastTool(Image &anImage, int contrast);

    // General Commands
    void execute() override;
    void undo() override;
    void redo() override;
};


#endif // CONTRASTTOOL_H
