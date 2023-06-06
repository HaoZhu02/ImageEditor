#ifndef ADDTEXTTOOL_H
#define ADDTEXTTOOL_H

#include "imageedit.h"
#include "../imagefile.h"

class AddTextTool : public ImageEdit
{
private:
    Image& anImage;
    int topLeftX;
    int topLeftY;
    QString text;
    std::vector<Pixel>& pixelBuffer;
    std::vector<Pixel> backupPixelBuffer;
    QImage backupImage;

    // Text adding logic
    void addText();

public:
    // Constructor
    AddTextTool(Image& anImage, int topLeftX, int topLeftY, const QString& text);

    // General Commands
    void execute() override;
    void undo() override;
    void redo() override;
};

#endif // ADDTEXTTOOL_H
