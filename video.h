#ifndef VIDEO_PLAY_H
#define VIDEO_PLAY_H
#include<QSlider>
#include<QLabel>
#include<opencv2/opencv.hpp>
#include <QThreadPool>
#include<QString>
#include"function.h"

using namespace cv;
class Video: public QRunnable
{
public:
    Video() = default;
    //show mes about current frame and total frame show video image captured;
    Video(QSlider *slider, QLabel *video, QLabel *message): slider(slider), video(video), mes(message) {};
    ~Video();
    void play(QString s);//play video
    void stop();//stop video (exit the video)
    void pause();//pause video
    void start();//coninue to play video
    void run();//thread to play video
    int quicker();//play video at double speed
    int slower();//play video at half speed
    void setPostion(long position);//set video paly position
    double getCurrentPostion();//get current video paler position
    void paseOrStart();//play or start video
    VideoCapture capture;
    void showImg(Mat m, QLabel*label );//show image in label
private:
    static bool video_status;
    QString videoPath;//video dir
    QSlider *slider;
    QLabel *video;//show video image captured;
    QLabel *mes;//show mes about current frame and total frame
    bool isStop = false;//is stop status?
    bool isPase = false;//is pause status?
    int speed = 100;//the speed of video
    int pos = -1;//current postion
    Mat frame;

};

#endif // VIDEO_PLAY_H
