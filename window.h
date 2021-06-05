#ifndef WINDOW_H
#define WINDOW_H

#include <opencv2/opencv.hpp>
#include <QLabel>
#include <QtWidgets/QMainWindow>
#include <QMainWindow>
#include <QVideoWidget>
#include <QFileDialog>
#include <QPushButton>
#include <QMediaPlayer>
#include <QImage>
#include <QTime>
#include<QTableWidget>
#include <QDebug>
#include "const.h"
#include "ui_window.h"
#include <QTimer>
#include "function.h"
#include "video.h"
#include <QThread>
#include"camera.h"
#include <QMouseEvent>
#include"music.h"
using namespace cv;
using namespace std;
namespace Ui
{
    class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:

    explicit Window(QWidget *parent = nullptr);
    ~Window();

private:
    Ui::Window *ui;
    QLabel *lab_camera = nullptr;//to show video or camer image
    Video *player = nullptr;//initalize to play video
    Music *musicPlayer = nullptr;//initialize to play music
    VideoCapture capture;
    Camera camera;//initialize to open camera or taking  picture

private slots:
    void Slider_Moved(int positon);//sychonized show video or music
    void pauseorstart();//pause play music or video
    void openCamera();     // Open camera
    void closeCamera();    // Close camera
    void takingPictures(); // Take photos
    void openVideo();      // Open Video
    void close();    // Close video area
    void quick();//double paly video or advance music
    void slower();//half play video or back music
    void openMusic();//open music
    void PreMusic();//play previous music
    void NextMusic();//play next music

};
#endif // WINDOW_H
