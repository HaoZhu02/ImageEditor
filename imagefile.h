/*********************************
 * Author(s): Emmitt Carter
 * Date: 05-22-2023
*********************************/
#ifndef IMAGEFILE
#define IMAGEFILE

#include <iostream>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/**
 *  Class for the image file selected
 *  by the user.
**/
class Image 
{
    private:
        QString file;
        string fileType;
        int pxLong;
        int pxWide;
        float bytes;
    public:
        // Constructor
        Image(QString);
        // Accessors
        QString get_file();
        string get_fileType();
        int get_pxLong();
        int get_pxWide();
        float get_bytes();
        // Mutators
        void set_file(QString);
        void set_fileType(string);
        void set_pxLong(int);
        void set_pxWide(int);
        void set_bytes(float);
        // Other
        void find_px_area();
        void find_file_size();
        void find_file_type();
};

#endif