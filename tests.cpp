/*********************************
 * Author(s): Emmitt Carter
 * Date: 05-22-2023
*********************************/

#include "imagefile.h"

int main() {
    
    /**  Test 1  **/
    QString src = "/Users/emmittcarter/Downloads/test_image1.jpeg";
    Image img(src);

    cout << "Path: " << img.get_file().toStdString() << endl;
    cout << "File Type: " << img.get_fileType() << endl;
    cout << "Length: " << img.get_pxLong() << endl;
    cout << "Width: " << img.get_pxWide() << endl;
    cout << "File Size: " << img.get_bytes() << endl;

    return 0;
}