#include "music.h"
//initalize music player
Music::Music(QListWidget*listWidget, QSlider *slider, QLabel*label)
{
    this->listWidget = listWidget;
    this->slider = slider;
    this->lab = label;
    playerList = new QMediaPlaylist;
    player = new QMediaPlayer;
    listWidget->addItem("            播放列表");
    //bind signal with player;
    connect(player, &QMediaPlayer::positionChanged, this, &Music::positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &Music::onDurationChanged);
}
//release memery and clear label
Music::~Music()
{
    delete player;
    delete playerList;
    listWidget->clear();
    lab->setText("0/0");
    slider->setSliderPosition(0);
    std::cout << "MusicPlayer is deleted " << std::endl;
}
//when player position changed ,to deal with it
void Music::positionChanged(qint64 position)
{
    if(isPlay)
    {
        //show current postion with label
        currentPosition = position;
        slider->setSliderPosition((position));
        lab->setText(QString::number(position / 1000 / 60) + ":" + QString::number((position / 1000) % 60) + " /  " + stringTotalTime );
    }
}
//when total time changed ,deal with it
void Music::onDurationChanged(qint64 duration)
{
    //change totaltime and slider max and totaltiome(string type)
    intTotalTime = duration;
    slider->setMaximum(duration);
    stringTotalTime = QString::number(duration / 1000 / 60) + ":" +
                      QString::number((duration / 1000) % 60);
}//set media paly's position
void Music::setPosition(qint64 postion)
{
    player->setPosition(slider->value());
    currentPosition = postion;
}
//add item in listwidget
void Music::addItem( QString s)
{
    listWidget->addItem(s);
}
// to stop music
void Music::stop()
{
    isStop = true;
    player->stop();
}
//go to next music
void Music::goNext()
{
    int count = playerList->mediaCount();
    if(playerList->currentIndex() < count - 1)
    {
        playerList->setCurrentIndex(++currentRow);
        listWidget->setCurrentRow(playerList->currentIndex() + 1);
        player->setPosition(0);
        slider->setSliderPosition(0);
    }
}
//go to previous music
void Music::goPre()
{
    if(playerList->currentIndex() > 0)
    {
        playerList->setCurrentIndex(--currentRow);
        listWidget->setCurrentRow(playerList->currentIndex() + 1);
        player->setPosition(0);
        slider->setSliderPosition(0);
    }
}
//play or pause the music
void Music::musicPlayOrStart()
{
    if(!isPlay)
    {
        isPlay = true;
        player->play();
    }
    else
    {
        isPlay = false;
        player->pause();
    }
}
//advance 30 second
void Music::quicker(qint64 postion)
{
    slider->setValue(postion + 30000);
    player->setPosition(slider->value());
    currentPosition = postion + 30000;
}
//back 30 second
void Music::slower(qint64 postion)
{
    slider->setValue(postion - 30000);
    player->setPosition(slider->value());
    currentPosition = postion - 30000;
}
