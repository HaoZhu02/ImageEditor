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

    ui->actionRedo->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    ui->menuEdit->setEnabled(false);
    ui->menuView->setEnabled(false);
    ui->menuFilters->setEnabled(false);
    ui->actionSave->setEnabled(false);


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
            ui->actionRedo->setEnabled(false);
            ui->actionUndo->setEnabled(false);
            ui->actionSave->setEnabled(false);
            ui->menuView->setEnabled(true);
            ui->menuFilters->setEnabled(true);



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

            on_actionAspect_Ratio_triggered();

            pendingSaveModifications = true;
            ui->actionSave->setEnabled(true);
            ui->actionUndo->setEnabled(true);
            ui->actionRedo->setEnabled(false);
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
            ui->actionSave->setEnabled(true);
            ui->actionUndo->setEnabled(true);
            ui->actionRedo->setEnabled(false);
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
        ui->actionSave->setEnabled(true);
        ui->actionUndo->setEnabled(true);
        ui->actionRedo->setEnabled(false);
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
            ui->actionSave->setEnabled(true);
            ui->actionUndo->setEnabled(true);
            ui->actionRedo->setEnabled(false);
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

// Aspect Ratio Event-Handler
void MainWindow::on_actionAspect_Ratio_triggered()
{
    if(activeImage!=nullptr)
    {
        ui->graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);
    }
}


// Undo Event-Handler
void MainWindow::on_actionUndo_triggered()
{
    if(activeImage!= nullptr && !editingManager.isUndoStackEmpty())
    {
        editingManager.undo();
        activeImage->updateBuffer();
        pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));

        scene.setSceneRect(0, 0, activeImage->getWidth(), activeImage->getHeight());
        on_actionAspect_Ratio_triggered();

        // Set the stack
        pendingSaveModifications = true;
        ui->actionRedo->setEnabled(true);
        pendingSaveModifications = true;
        ui->actionSave->setEnabled(true);

        // If empty no longer allow click
        if(editingManager.isUndoStackEmpty())
        {
            ui->actionUndo->setEnabled(false);
        }
    }
}


// Redo Event-Handler
void MainWindow::on_actionRedo_triggered()
{
    if(activeImage!= nullptr && !editingManager.isRedoStackEmpty())
    {
        editingManager.redo();
        activeImage->updateBuffer();
        pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));

        scene.setSceneRect(0, 0, activeImage->getWidth(), activeImage->getHeight());
        on_actionAspect_Ratio_triggered();

        // Set the Stack
        pendingSaveModifications = true;
        ui->actionUndo->setEnabled(true);
        pendingSaveModifications = true;
        ui->actionSave->setEnabled(true);

        // If empty no longer allow click
        if(editingManager.isRedoStackEmpty())
        {
            ui->actionRedo->setEnabled(false);
        }
    }
}



// Resize Event-Handler
void MainWindow::on_actionResize_triggered()
{
    if(activeImage!=nullptr)
    {
        bool valid = false;
        QList<QString> fields = {"Width", "Height"};
        QList<int> values = InputDialog::getFields(this, fields, 1, 10000, 100, &valid);


        if(valid)
        {
            int w = values[0];
            int h = values[1];

            // execute the resize
            std::shared_ptr<ImageEdit> c(new ResizeTool(*activeImage, w, h));
            editingManager.execute(c);
            activeImage->updateBuffer();

            // Display
            pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));
            scene.setSceneRect(0, 0, activeImage->getWidth(), activeImage->getHeight());
            on_actionAspect_Ratio_triggered();

            // Set Stack
            pendingSaveModifications = true;
            ui->actionSave->setEnabled(true);
            ui->actionUndo->setEnabled(true);
            ui->actionRedo->setEnabled(false);
        }
    }
}


// Gray Scale Event Handler
void MainWindow::on_actionGray_Scale_triggered()
{
    if(activeImage!= nullptr)
    {
        // Execute GrayScale
        std::shared_ptr<ImageEdit> c1(new GrayScaleTool(*activeImage));
        editingManager.execute(c1);
        activeImage->updateBuffer();

        // Display
        pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));

        // Set Stack
        pendingSaveModifications = true;
        ui->actionSave->setEnabled(true);
        ui->actionUndo->setEnabled(true);
        ui->actionRedo->setEnabled(false);
    }
}

// Sharpen Event Handler
void MainWindow::on_actionSharpen_triggered()
{
    if(activeImage!= nullptr) {

        // Execute Sharpen
        std::shared_ptr<ImageEdit> c1(new SharpenTool(*activeImage));
        editingManager.execute(c1);
        activeImage->updateBuffer();

        pixmapItem->setPixmap(QPixmap::fromImage(activeImage->getQImage()));

        // Set Stack
        pendingSaveModifications = true;
        ui->actionSave->setEnabled(true);
        ui->actionUndo->setEnabled(true);
        ui->actionRedo->setEnabled(false);
    }
}








