#include "utilities.h"
#include "mainwindow.h"
#include "QApplication"


int main(int argc, char *argv[])
{
    //qDebug("Hello World");
    //QString src = "C:/Users/zhu02/OneDrive/Desktop/common_events.jpg";
    //QString src1 = "C:/Users/zhu02/OneDrive/Desktop/GUI.jpg";

    //Image img(src);
    //Image pic(src1);





    //CropTool cropTest(img, 0, 0, 120, 120);
    //cropTest.execute();

    //QImage haoTest = cropTest.getImage().getQImage();

    //img.setQImage(haoTest);




    //pic = cropTest.get_originalImage();


    //QString src2 = "";

    //src2 = pic.getPath();




    QApplication a(argc, argv);
    MainWindow w;

    //QLabel label(&w);

    //QPixmap pixmap(src);

    //label.setPixmap(QPixmap::fromImage(img.getQImage()));

    //w.setCentralWidget(&label);



    w.show();




    //qDebug() << "Path: " << img.getPath();
    //qDebug() << "File Type: " << img.getFilename();
    //qDebug() << "Width: " << img.getWidth();
    //qDebug() << "Height: " << img.getHeight();
    //qDebug() << "File Size: " << img.getSize();
    return a.exec();
};
