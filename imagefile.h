#ifndef IMAGEFILE_H
#define IMAGEFILE_H

#include "pixel.h"
#include <QString>
#include <QImage>
#include <vector>

using namespace std;

class Image
{

private:
    // Image
    QImage imageRaw;
    QString filePath;
    QString fileName;

    // Image Measurables
    int width;
    int height;
    size_t bytes;

    bool imageValid;

    std::vector<Pixel> pixelBuffer;
    void initPixelBuffer();
    void pureFileName();


public:
    // Constructor
    Image(const QString &path);
    Image(QImage &anImage);
    Image(const Image& anImage);

    // Getters
    QString getPath() const;
    QString getFilename() const;
    int getWidth() const;
    int getHeight() const;
    size_t getSize() const;
    QImage& getQImage();
    std::vector<Pixel>& getPixelBuffer();

    // Setters
    void setWidth(int width);
    void setHeight(int height);
    void setFilePath(QString filePath);
    void setQImage(QImage &newImage);
    void setBuffer(std::vector<Pixel>& pixelBuffer);
    void setSize(size_t aSize);

    // Other
    bool save(const QString &outPath, int quality = -1);   //-1 is auto comporssion while 0-100 is quality range
    //Image(Image &aImage) = delete;
    void swapDimension();
    void updateBuffer();
    bool isValid() const;

    Image& operator= (Image& anImage);


};

#endif
