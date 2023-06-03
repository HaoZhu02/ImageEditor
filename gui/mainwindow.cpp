#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>
#include <QList>
#include "inputdialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    pendingSaveModifications(false)
{
    ui->setupUi(this);
    ui->graphicsView->hide();
    ui->statusbar->hide();

    //disable action not used before Image upload

    ui->statusbar->addPermanentWidget(&imageName);
    ui->statusbar->addPermanentWidget(&imageSize);
    activeImage.reset();

    //geometric zoom list
    zoomList << 1.0 << 1.5 << 2.2 << 3.3 << 4.7 << 6.8;
    zoomList << 10 << 15 << 22 << 33 << 47 << 68;
    zoomList << 100 << 150 << 220 << 330 << 470 << 680;
    zoomList << 1000 << 1500 << 2200 << 3300 << 4700 << 6800;


}

MainWindow::~MainWindow()
{
    delete ui;
}

// Open-File Event-Handler
void MainWindow::on_actionOpen_triggered()
{
    QString imagePath = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

    if(!imagePath.isEmpty()){
        activeImage.reset(new Image(imagePath));

        if(activeImage->isValid()){

            qDebug() << activeImage->getFilename();

            scene.clear();
            pixmapItem = scene.addPixmap(QPixmap::fromImage(activeImage->getQImage()));
            scene.setSceneRect(0, 0, activeImage->getWidth(), activeImage->getHeight());
            ui->graphicsView->setScene(&scene);

            ui->graphicsView->show();

            //updateStatusBar();
            ui->statusbar->show();
            ui->graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);


            ui->menuEdit->setEnabled(true);

            pendingSaveModifications = false;
        }
        else {
            activeImage.reset();
            scene.clear();
            ui->graphicsView->hide();
            ui->statusbar->hide();


            ui->menuEdit->setEnabled(false);

            QMessageBox::critical(this, "APP_NAME",
                                  "The image is not Valid.",
                                  QMessageBox::Ok);
        }
    }
}


// Crop Event-Handler
void MainWindow::on_actionCrop_triggered()
{
    if(activeImage!=nullptr)
    {
        bool valid = false;
        QList<QString> fields = {"TopLeftX", "TopLeftY", "Width", "Height"};
        QList<int> input = InputDialog::getFields(this, fields, 0, 10000, 10, &valid);

        if(valid)
        {
            int x = input[0];
            int y = input[1];
            int w = input[2];
            int h = input[3];
            std::shared_ptr<ImageEdit> c4(new CropTool(*activeImage, x, y, w, h));
            editingManager.execute(c4);

            /*CropTool testHao(*activeImage, x, y, w, h);
            testHao.execute();
            QImage nozomi = testHao.getTemp();

            activeImage->setQImage(nozomi);*/

            activeImage->updateBuffer();
            pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));

            pendingSaveModifications = true;
        }
    }
}


// Save Event-Handler
void MainWindow::on_actionSave_triggered()
{
    if(activeImage!=nullptr)
    {
        activeImage->save(activeImage->getPath());
        ui->actionSave->setEnabled(false);
        pendingSaveModifications = false;
    }
}


// Brightness Event-Handler
void MainWindow::on_actionBrightness_triggered()
{
    if(activeImage!=nullptr)
    {
        bool valid = false;
        QList<QString> field = {"Brightness"};
        QList<int> input = InputDialog::getFields(this, field, -100, 100, 10, &valid);

        if(valid)
        {
            int inputValue = input[0];
            std::shared_ptr<ImageEdit> c1(new BrightnessTool(*activeImage, inputValue));
            editingManager.execute(c1);
            activeImage->updateBuffer();
            pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));

            pendingSaveModifications = true;
        }
    }
}


// Rotate-Clockwise Event-Handler
void MainWindow::on_actionRotate_Clockwise_triggered()
{
    if(activeImage!= nullptr) {
        std::shared_ptr<ImageEdit> c1(new RotateClockwiseTool(*activeImage));
        editingManager.execute(c1);

        //qDebug() << "rotate clockwise";

        activeImage->updateBuffer();
        pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));
        scene.setSceneRect(0, 0, activeImage->getWidth(), activeImage->getHeight());
        // test


        pendingSaveModifications = true;
    }
}


// Contrast Event-Handler
void MainWindow::on_actionContrast_triggered()
{
    if(activeImage!=nullptr)
    {
        bool valid = false;
        QList<QString> field = {"Contrast"};
        QList<int> input = InputDialog::getFields(this, field, -100, 100, 10, &valid);

        if(valid){
            int inputValue = input[0];
            std::shared_ptr<ImageEdit>c1(new ContrastTool(*activeImage, inputValue));
            editingManager.execute(c1);
            activeImage->updateBuffer();
            pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));

            pendingSaveModifications = true;
        }
    }
}


// UI Zooming Logic
void MainWindow::zoomTool(bool zoomStatus)
{
    if(activeImage!=nullptr)
    {
        double zoom = ui->graphicsView->transform().m11() * 100;

        if(zoomStatus)
        {
            for(double z: zoomList)
            {
                if((z - z / 10) > zoom)
                {
                    zoom = z;
                    break;
                }
            }
        }

        else{
            for(int i = zoomList.count()-1; i > 0; i--)
            {
                double zooming = zoomList[i];
                if((zooming + zooming / 10) < zoom)
                {
                    zoom = zooming;
                    break;
                }
            }
        }

        ui->graphicsView->setTransform(QTransform::fromScale(zoom / 100, zoom / 100));
    }
}


// Zoom-In Event-Handler
void MainWindow::on_actionZoom_In_triggered()
{
    if(activeImage!=nullptr)
    {
        zoomTool(true);
    }
}


// Zoom-Out Event-Handler
void MainWindow::on_actionZoom_Out_triggered()
{
    if(activeImage!=nullptr)
    {
        zoomTool(false);
    }
}



















