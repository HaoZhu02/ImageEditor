#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QCloseEvent>
#include "../backend/imagefile.h"
#include "../backend/editingTools/edits.h"


namespace Ui
{
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_actionOpen_triggered();
    void on_actionCrop_triggered();
    void on_actionSave_triggered();
    void on_actionBrightness_triggered();
    void on_actionRotate_Clockwise_triggered();
    void on_actionContrast_triggered();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();

protected slots:
    void zoomTool(bool zoomStatus);

private:
    Ui::MainWindow *ui;
    QGraphicsPixmapItem* pixmapItem;
    QGraphicsScene scene;

    std::unique_ptr<Image> activeImage;
    EditingManager editingManager;

    bool pendingSaveModifications;

    QList<double> zoomList;

    QLabel imageName;
    QLabel imageSize;


protected:


};
#endif // MAINWINDOW_H
