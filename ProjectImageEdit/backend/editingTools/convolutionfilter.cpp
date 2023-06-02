#include "convolutionfilter.h"

void useConvolutionFilter(double filter[3][3], Image& anImage, std::vector<Pixel>& pixelBuffer)
{
    // INITIALIZE needed values
    int sumR;
    int sumG;
    int sumB;
    int height = anImage.getHeight();
    int width = anImage.getWidth();
    std::vector<Pixel> tempPixelBuffer;

    // Create the tempPixelBuffer
    tempPixelBuffer.reserve((height+2) * (width+2));
    tempPixelBuffer.resize((height+2) * (width+2));

    // Copy the pixelBuffer into the temporary
    for(int x=1; x<height+1; x++)                // Rows
    {
        for(int y=1; y<width+1; y++)            // Columns
        {
            tempPixelBuffer[x * (width + 2) + y] = pixelBuffer[(x-1) * width + (y-1)];
        }
    }

    // Top Row (excluding first) to First Row - pixelBuffer to temp
    for(int i = 1; i < width + 1; i++)
    {
        tempPixelBuffer[0 * (width + 2) + i] = pixelBuffer[0 * width + (i - 1)];
    }

    // Bottom Row (excluding first) to Last Row - pixelBuffer to temp
    for(int i = 1; i < width + 1; i++)
    {
        tempPixelBuffer[(height + 1) * (width + 2) + i] = pixelBuffer[(height - 1) * width + (i - 1)];
    }

    // First Column (excluding first) to First Column - pixelBuffer to temp
    for(int i = 1; i < height + 1; i++)
    {
        tempPixelBuffer[i * (width + 2) + 0] = pixelBuffer[(i - 1) * width + 0];
    }

    // Last Column (excluding first) to Last Column - pixelBuffer to temp
    for(int i = 1; i < height + 1; i++)
    {
        tempPixelBuffer[i * (width + 2) + (width + 1)] = pixelBuffer[(i - 1) * width + (width - 1)];
    }

    // Top-Left Corner
    tempPixelBuffer[0 * (width + 2) + 0] = pixelBuffer[0 * width + 0];

    // Top-Right Corner
    tempPixelBuffer[0 * (width + 2) + (width + 1)] = pixelBuffer[0 * width + (width - 1)];

    // Bottom-Left Corner
    tempPixelBuffer[(height + 1) * (width + 2) + 0] = pixelBuffer[(height - 1) * width + 0];

    // Bottom-Right Corner
    tempPixelBuffer[(height + 1) * (width + 2) + (width + 1)] = pixelBuffer[(height - 1) * width + (width - 1)];


    // Application of Convolution Filter (kernel)

    for(int x=1; x<height+1; x++)           // Row
    {
        for(int y=1; y<width+1; y++)        // Column
        {
            sumR = 0;
            sumG = 0;
            sumB = 0;


            // Matrix Logic
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    sumR += tempPixelBuffer[(x + i - 1) * (width + 2) + (y + j - 1)].getR() * filter[i][j];

                    sumG += tempPixelBuffer[(x + i - 1) * (width + 2) + (y + j - 1)].getG() * filter[i][j];

                    sumB += tempPixelBuffer[(x + i - 1) * (width + 2) + (y + j - 1)].getB() * filter[i][j];
                }
            }

            // Apply -> pixelBuffer the new RGBA
            pixelBuffer[(x - 1) * width + (y - 1)].setPixel(sumR, sumG, sumB, pixelBuffer[(x - 1) * width + (y - 1)].getA());
        }
    }
}
