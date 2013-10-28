#ifndef VIDEODISP_H
#define VIDEODISP_H

#include <QWidget>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QCloseEvent>
#include <QAction>
#include <QMenu>
#include <QPoint>
#include <QString>
#include <QFileDialog>
#include "cv.h"
#include "highgui.h"

class videoDisp : public QWidget
{
    Q_OBJECT
public:
    explicit videoDisp(QWidget *parent = 0);
    void openTheCamera();

signals:

public slots:
    void showImg();
    void start_pause_change();
    void closeCamera();
    void showFuncMenu(QPoint);
    void openPic();
    void openVid();
    void openCam();
    void savePic();

protected:
    void closeEvent(QCloseEvent *event);

private:
    QAction* savePicture;
    QAction* openVideo;
    QAction* openCamera;
    QAction* openPicture;
    QMenu* funcMenu;

    cv::VideoCapture* camera;
    cv::Mat* srcFrame;
    QImage* frame;
    QLabel* frameRect;
    QPushButton* start_pause;
    QPushButton* stop;
    QTimer* timer;
    bool cameraRunState;
    bool cameraOpenState;
};

#endif // VIDEODISP_H
