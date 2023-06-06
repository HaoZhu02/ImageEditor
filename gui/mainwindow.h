#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMouseEvent>
#include <QApplication>
#include <QEvent>
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

//public slots:
    //void displayCursorPosition(const QPoint& pos);



private slots:
    void on_actionOpen_triggered();
    void on_actionCrop_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();
    void on_actionBrightness_triggered();
    void on_actionRotate_Clockwise_triggered();
    void on_actionRotate_Anti_triggered();
    void on_actionContrast_triggered();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionRedo_triggered();
    void on_actionUndo_triggered();
    void on_actionAspect_Ratio_triggered();
    void on_actionResize_triggered();
    void on_actionGray_Scale_triggered();
    void on_actionSharpen_triggered();
    void on_actionBlur_triggered();
    void on_actionWarming_triggered();
    void on_actionCooling_triggered();
    void on_actionThreshold_triggered();
    void on_actionAdd_Text_triggered();



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

    QPoint cursorPosition;
    QLabel cursorPositionLabel;
    //QGraphicsView* graphicsView;

protected:
    void closeEvent(QCloseEvent *event) override;
    void updateStatusBar();
    void mouseMoveEvent(QMouseEvent* event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;




};
#endif // MAINWINDOW_H
