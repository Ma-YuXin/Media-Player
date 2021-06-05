#ifndef MUSIC_PLAY_H
#define MUSIC_PLAY_H
#include<QLabel>
#include<QMediaPlaylist>
#include<QMediaPlayer>
#include<QListWidget>
#include<QDir>
#include<QTextCodec>
#include"function.h"
class Music: public QObject
{
public:
    Music() = default;
    Music(QListWidget*listWidget, QSlider *slider, QLabel*lab);
    ~Music();
    void addItem(QString s);//add item in listwidget
    QMediaPlaylist *playerList = nullptr;//initlize qmediaplayer list to store music list
    QMediaPlayer *player = nullptr;// a player to play or pause music
    void stop();// to stop music
    void goNext();//go to next music
    void goPre();//go to previous music
    void musicPlayOrStart();//play or pause the music
    void quicker(qint64 postion);//advance 30 second
    void slower(qint64 postion);//back 30 second
    void setPosition(qint64 postion);//set media paly's position
    int currentRow = 0;//current media list row;
    bool isPlay = false;//paly status;
private:
    QListWidget* listWidget = nullptr;//play list
    QSlider *slider;//slider
    QLabel *lab = nullptr;//show current time and totaltime
    bool isStop = false;//stop player
    int currentPosition;//current player position
    int intTotalTime = 0;//music total time
    QString stringTotalTime;//music totaltime in string,to show in lab conveniently
private slots:
    void positionChanged(qint64 positionTime);//when player position changed ,to deal with it
    void  onDurationChanged(qint64 duration);//when total time changed ,deal with it
};

#endif // MUSIC_PLAY_H
