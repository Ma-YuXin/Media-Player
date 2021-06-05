#include "video.h"
bool Video::video_status = false;
//release memary and clear label
Video::~Video()
{
    std::cout << "VideoPlayer is deleted " << std::endl;
    slider->setSliderPosition(0);
    video->clear();
    mes->clear();
}
//play video
void Video::play(QString path)
{
    isStop = false;
    capture.open(path.toStdString());
    slider->setRange(0, capture.get(7));
}
//stop video (exit the video)
void Video::stop()
{
    isStop = true;
}
//pause video
void Video::pause()
{
    isPase = true;
}
//coninue to play video
void Video::start()
{
    isStop = false;
}
//play video at double speed
int Video::quicker()
{
    if(speed > 30)
    {
        return speed -= 15;
    }
    else
    {
        return 30;
    }
}
//play video at half speed
int Video::slower()
{
    if(speed < 200)
    {
        return speed += 20;
    }
    else
    {
        return 200;
    }
}
//play or start video
void Video::paseOrStart()
{
    isPase ? isPase = false : isPase = true;
}
void Video::setPostion(long position)
{
    this->pos = position;
}
//get current video paler position
double Video::getCurrentPostion()
{
    return (capture.get(0));
}
//show image in label
void Video::showImg(Mat m, QLabel *label)
{
    cv::cvtColor(m, m, cv::COLOR_BGR2RGB);
    QImage img = QImage((const unsigned char*)(m.data), m.cols, m.rows,
                        m.cols * m.channels(),
                        QImage::Format_RGB888).scaled(label->width(), label->height());
    label->clear();
    label->setPixmap(QPixmap::fromImage(img));
}
//thread to play video
void Video::run()
{
    //player's thread
    while(true)
    {
        //click silder to change position
        if(pos != -1)
        {
            capture.set(1, pos);
            pos = -1;
        }
        //pause to make chagne
        if (!isPase)
        {
            capture.read(frame);
            long i = capture.get(1);
            if(isStop)
            {
                break;
            }
            showImg(frame, video);
            QMetaObject::invokeMethod(slider, "setValue", Qt::QueuedConnection, Q_ARG(int, i));
            mes->setText(QString::number(getCurrentPostion()) + "/" + QString::number(capture.get(7) * 40));
            Sleep(speed);
        }
    }
}
