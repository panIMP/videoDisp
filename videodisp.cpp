#include "videodisp.h"

videoDisp::videoDisp(QWidget *parent) :QWidget(parent)
{
    frameRect = new QLabel;
    frameRect->setMinimumSize(600,400);
    frameRect->setBackgroundRole(QPalette::Light);
    start_pause = new QPushButton("Start/Pause");
    stop = new QPushButton("Stop");
    timer = new QTimer;
    cameraRunState = false;
    cameraOpenState = false;

    funcMenu = new QMenu("Mode select");
    openPicture = new QAction("open a picture", this);
    connect(openPicture, SIGNAL(triggered()), this, SLOT(openPic()));
    openVideo = new QAction("open a video", this);
    connect(openVideo, SIGNAL(triggered()), this, SLOT(openVid()));
    openCamera = new QAction("open the camera", this);
    connect(openCamera, SIGNAL(triggered()), this, SLOT(openCam()));
    savePicture = new QAction("save this picture", this);
    savePicture->setDisabled(true);
    connect(savePicture, SIGNAL(triggered()), this, SLOT(savePic()));
    funcMenu->addAction(openPicture);
    funcMenu->addAction(openVideo);
    funcMenu->addAction(openCamera);
    funcMenu->addSeparator();
    funcMenu->addAction(savePicture);
    frameRect->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(frameRect, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showFuncMenu(QPoint)));

    QVBoxLayout* vLay = new QVBoxLayout;
    vLay->addWidget(frameRect);
    vLay->setAlignment(frameRect, Qt::AlignCenter);
    QHBoxLayout* hLay = new QHBoxLayout;
    hLay->addStretch();
    hLay->addWidget(start_pause);
    hLay->addStretch();
    hLay->addWidget(stop);
    hLay->addStretch();
    vLay->addLayout(hLay);
    setLayout(vLay);
    setWindowTitle("camera live video -- stopped");

    connect(start_pause, SIGNAL(clicked()), this, SLOT(start_pause_change()));
    connect(timer, SIGNAL(timeout()), this , SLOT(showImg()));

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    connect(stop, SIGNAL(clicked()), this, SLOT(closeCamera()));
}

void videoDisp::closeEvent(QCloseEvent* event){
    closeCamera();
    event->accept();
}

void videoDisp::showFuncMenu(QPoint){
    funcMenu->exec(QCursor::pos());
}

void videoDisp::showImg(){
    *camera >> *srcFrame;
    cv::cvtColor(*srcFrame, *srcFrame, CV_BGR2GRAY);
    cv::GaussianBlur(*srcFrame, *srcFrame, cv::Size(7,7), 1.5, 1.5);
    cv::Canny(*srcFrame, *srcFrame, 0, 30);
    frame = new QImage((uchar*)srcFrame->data, srcFrame->cols, srcFrame->rows, QImage::Format_Indexed8);
    frameRect->setPixmap(QPixmap::fromImage(*frame));
    delete frame;
}

void videoDisp::start_pause_change(){
    if(cameraRunState == true){
        cameraRunState = false;
        timer->stop();
        setWindowTitle("camera live video -- paused");
    }else if(cameraRunState == false){
        if(cameraOpenState == false){
            openTheCamera();
            cameraOpenState = true;
        }
        cameraRunState = true;
        timer->start(3);
        setWindowTitle("camera live video -- running");
    }
}

void videoDisp::closeCamera(){
    if(cameraOpenState == true){
        timer->stop();
        delete camera;
        delete srcFrame;
        cameraRunState = false;
        cameraOpenState = false;
        frame = new QImage;
        frameRect->setPixmap(QPixmap::fromImage(*frame));
        setWindowTitle("camera live video -- stopped");
        savePicture->setDisabled(true);
    }
}

void videoDisp::openTheCamera(){
    camera = new cv::VideoCapture(0);
    if(!camera->isOpened())
        exit(2);
    srcFrame = new cv::Mat;
    savePicture->setEnabled(true);
}

void videoDisp::openPic(){

}

void videoDisp::openVid(){

}

void videoDisp::openCam(){

}

void videoDisp::savePic(){
    QString fileName = QFileDialog::getSaveFileName(this, "save as","C:/Users/nopend/Desktop",("(*.png);;(*.jpg);;(*.bmp)"));
    cv::imwrite(fileName.toLocal8Bit().constData(), *srcFrame);
}
