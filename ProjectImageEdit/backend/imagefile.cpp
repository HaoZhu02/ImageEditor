#include "imagefile.h"
#include "pixel.h"
#include "QFileInfo"
#include <algorithm>
#include <cmath>
#include <QErrorMessage>
#include <QColor>

using namespace std;

// Explicit Constructor
Image::Image(const QString &filePath) : imageRaw(filePath), filePath(filePath), imageValid(true)
{
    if(imageRaw.isNull())
    {
        this->imageValid = false;
    }
    imageRaw = imageRaw.convertToFormat(QImage::Format_ARGB32); // Auto Conversion for 32bit depth support
    this->width = imageRaw.width();
    this->height = imageRaw.height();

    pixelBuffer.reserve(getSize());
    initPixelBuffer();
    pureFileName();
}

Image::Image(QImage &anImage) : imageRaw(nullptr), filePath(""), imageValid(true)
{
    this->imageRaw = anImage;
    imageRaw = imageRaw.convertToFormat(QImage::Format_ARGB32);
    this->width = imageRaw.width();
    this->height = imageRaw.height();

    pixelBuffer.reserve(getSize());
    initPixelBuffer();
    pureFileName();
}

/*
Image::Image(const Image& anImage) : imageRaw(nullptr), filePath(""), imageValid(true)
{
    *this = anImage;
}*/


// Private Helpers
void Image::pureFileName()
{
    QFileInfo qFilename(filePath);
    fileName = qFilename.fileName();
}

void Image::initPixelBuffer()
{
    for(int y = 0; y < height; y++)         // Rows
    {
        for(int x = 0; x < width; x++)      // Columns
        {
            pixelBuffer.emplace_back(Pixel::fromQColor(imageRaw.pixelColor(x, y)));
        }
    }
}


// Getters

QString Image::getPath() const
{
    return this->filePath;
}

QString Image::getFilename() const
{
    return this->fileName;
}

int Image::getWidth() const
{
    return this->width;
}

int Image::getHeight() const
{
    return this->height;
}

size_t Image::getSize() const
{
    return width * height;
}

std::vector<Pixel>& Image::getPixelBuffer()
{
    return this->pixelBuffer;
}

QImage& Image::getQImage()
{
    return this->imageRaw;
}



// Setters

void Image::setFilePath(QString filePath)
{
    this->filePath = filePath;
    pureFileName();
}

void Image::setWidth(int width)
{
    this->width = width;
}

void Image::setHeight(int height)
{
    this->height = height;
}

void Image::setQImage(QImage &newImage)
{
    this->imageRaw = newImage;
}

void Image::setBuffer(std::vector<Pixel>& pixelBuffer)
{
    this->pixelBuffer = pixelBuffer;
}

void Image::setSize(size_t aSize)
{
    this->bytes = aSize;
}



// Other

bool Image::save(const QString &outPath, int quality)
{
    updateBuffer();

    // Saves the Image on Disk
    return imageRaw.save(outPath, nullptr, quality);
}

void Image::updateBuffer()
{
    imageRaw = QImage(width, height, QImage::Format_ARGB32);

    for(int y = 0; y < height; y++)         // Rows
    {
        for(int x = 0; x < width; x++)      // Columns
        {
            imageRaw.setPixelColor(x, y, Pixel::toQColor(pixelBuffer[y * width + x]));
        }
    }
}

bool Image::isValid() const
{
    return this->imageValid;
}



Image& Image::operator= (Image& anImage)
{
    if(this == &anImage)
    {
        return *this;
    }

    setFilePath(anImage.filePath);
    setWidth(anImage.width);
    setHeight(anImage.height);
    setQImage(anImage.imageRaw);
    setBuffer(anImage.pixelBuffer);




    return *this;

}





