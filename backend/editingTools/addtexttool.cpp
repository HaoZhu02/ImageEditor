#include "addtexttool.h"
#include <QPainter>
#include <QDebug>

// Constructor
AddTextTool::AddTextTool(Image& anImage, int topLeftX, int topLeftY, const QString& text)
    : anImage(anImage),
    topLeftX(topLeftX),
    topLeftY(topLeftY),
    text(text),
    pixelBuffer(anImage.getPixelBuffer()),
    backupPixelBuffer(pixelBuffer),
    backupImage(anImage.getQImage())
{
}

// Text adding logic
void AddTextTool::addText()
{
    QImage image = backupImage;         // Create a new QImage based on the original image
    QPainter painter(&image);
    QFont font("Arial", 25);
    painter.setFont(font);
    painter.setPen(Qt::red);            // Set the text color

    // Calculate the bounding rectangle of the text
    QRect textRect = painter.boundingRect(QRect(topLeftX, topLeftY, image.width(), image.height()), Qt::AlignLeft, text);

    // Adjust the position of the text if it goes beyond the image boundaries
    int textX = qMax(0, textRect.left());
    int textY = qMax(0, textRect.top());

    // Draw the text
    painter.drawText(QPoint(textX, textY), text);
    qDebug() << "Drew Text";

    // Assign the modified image back to the original image
    Image fooImage(image);
    fooImage.setFilePath(anImage.getPath());

    anImage = fooImage;
}

// General Commands
void AddTextTool::execute()
{
    addText();
}

void AddTextTool::undo()
{
    pixelBuffer = backupPixelBuffer;
    anImage.setQImage(backupImage); // Restore the original image
}

void AddTextTool::redo()
{
    execute();
}
