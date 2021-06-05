#include "window.h"
#include "ui_window.h"
#include <iostream>

using namespace cv;

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    ui->Button_Open_Camera->setEnabled(true);
    ui->Button_Close_Camera->setEnabled(false);
    this->setFixedSize(this->size());
    lab_camera = new QLabel(ui->widget_video);
    lab_camera->setGeometry(0, 0, ui->widget_video->width(),
                            ui->widget_video->height());
    lab_camera->setScaledContents(true);
    // Bind a function to open camera;
    connect(ui->Button_Open_Camera,
            &QPushButton::clicked,
            this,
            &Window::openCamera);
    // Bind a function to take Photo;
    connect(ui->Button_TakePic,
            &QPushButton::clicked,
            this,
            &Window::takingPictures);
    // Bind a function to close camera
    connect(ui->Button_Close_Camera,
            &QPushButton::clicked,
            this,
            &Window::closeCamera);
    // Bind a function to open a video
    connect(ui->file_Action_OpenVideo,
            &QAction::triggered,
            this,
            &Window::openVideo);
    connect(ui->file_Action_OpenMusic, &QAction::triggered, this, &Window::openMusic);
    // Bind a function to close video
    connect(ui->Button_ClearArea,
            &QPushButton::clicked,
            this,
            &Window::close);
    // Pause the video or play it
    connect(ui->Button_Pause,
            &QPushButton::clicked,
            this,
            &Window::pauseorstart
           );
    //bind a function to double paly video or advance music
    connect(ui->Button_Quicker,
            &QPushButton::clicked,
            this,
            &Window::quick
           );
    //bind a function to half play video or back music
    connect(ui->Button_Slower,
            &QPushButton::clicked,
            this,
            &Window::slower
           );
    //sychonized show video or music
    connect(ui->Video_Slider, &QSlider::sliderMoved, this, &Window::Slider_Moved);
    //play previous music
    connect(ui->Button_Pre, &QPushButton::clicked, this, &Window::PreMusic);
    //play next music
    connect(ui->Button_Next, &QPushButton::clicked, this, &Window::NextMusic);
}
Window::~Window()
{
    delete ui;
}
//sychonized show video or music
void Window::Slider_Moved(int positon)
{
    //judge to change which player
    if(player)
    {
        player->setPostion(ui->Video_Slider->value());
    }
    else if(musicPlayer)
    {
        musicPlayer->setPosition(ui->Video_Slider->value());
    }
}
//open music
void Window::openMusic()
{
    //s store the dir of music
    QString s = QFileDialog::getOpenFileName(
                    this,
                    "Open",
                    "/",
                    "音乐(*.mp3)");
    /*******************************/
    //close video player or camera
    if (player)
    {
        player->stop();
        player = nullptr;
    }
    camera.closeCamera(lab_camera);
    ui->Button_Open_Camera->setEnabled(true);
    ui->Button_Close_Camera->setEnabled(false);
    /******************************************/
    if(!musicPlayer)
    {
        //initialized musicplayer
        musicPlayer = new Music(ui->listWidget, ui->Video_Slider, ui->label);
        //add  music to music listwidget
        QFileInfo fileInfo(s);
        musicPlayer->addItem(fileInfo.fileName());
        //add  music to music player list
        musicPlayer->playerList->addMedia(QUrl::fromLocalFile(s));
        //to player opened music
        musicPlayer->playerList->setCurrentIndex(0);
        musicPlayer->player->setPlaylist(musicPlayer->playerList);
        //player music
        musicPlayer->player->play();
        musicPlayer->isPlay = true;
        //show current music
        ui->listWidget->setCurrentRow(musicPlayer->playerList->currentIndex() + 1);
    }
    else
    {
        QFileInfo fileInfo(s);
        //if there is music played add it to player list and listwidget
        musicPlayer->addItem(fileInfo.fileName());
        musicPlayer->playerList->addMedia(QUrl::fromLocalFile(s));
    }
}
// Open Video;
void Window::openVideo()
{

    /**********************************************/
    // Assign s the path of its plaction
    QString s = QFileDialog::getOpenFileName(
                    this,
                    "Open",
                    "/",
                    "视频文件(*.mp4)");
    // Clear the Area of video area; and close music or camera
    close();
//    if (camera.capture.isOpened())
//    {
//        camera.capture.release();
//    }
    // Clear the Area of video area;
    QFile file(s);
    //judge if it is read only
    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }
    else
    {
        if (!player)
        {
            //if there isn't player that play video
            player = new Video(ui->Video_Slider, lab_camera, ui->label);
            player->play(s);
            std::cout << "successfully play video" << std::endl;
            //start thread
            QThreadPool::globalInstance()->start(player);
        }
        else
        {
            //there is player that play video
            //stop it and play opened video
            player->stop();
            player->play(s);
        }
    }
}

//play previous music
void Window::PreMusic()
{
    if(musicPlayer)
    {
        musicPlayer->goPre();
    }
}
//play next music
void Window::NextMusic()
{
    if(musicPlayer)
    {
        musicPlayer->goNext();
    }
}

//pause play music or video
void Window::pauseorstart()
{
    if(player)
    {
        player->paseOrStart();
    }
    else if(musicPlayer)
    {
        musicPlayer->musicPlayOrStart();
    }
    QString s = ui->Button_Pause->text();
    s == "Pause" ? ui->Button_Pause->setText("Start") : ui->Button_Pause->setText("Pause");
}

// Open camera
void Window::openCamera()
{
    if (player)
    {
        player->stop();
    }
    ui->Button_Close_Camera->setEnabled(true);
    ui->Button_Open_Camera->setEnabled(false);
    camera.openCamera(lab_camera);
}

// Takeing photos
void Window::takingPictures()
{
    if (player)
    {
        player->stop();
    }
    camera.takingPictures(lab_camera);
}

// Close camera;
void Window::closeCamera()
{
    ui->Button_Close_Camera->setEnabled(false);
    ui->Button_Open_Camera->setEnabled(true);
    camera.closeCamera(lab_camera);
}


// Close the video area
void Window::close()
{
    camera.closeCamera(lab_camera);
    if (player)
    {
        player->stop();
        // delete player;
        player = nullptr;
    }
    if(musicPlayer)
    {
        delete musicPlayer;
        musicPlayer = nullptr;
    }
//    lab_camera->clear();
    ui->Button_Open_Camera->setEnabled(true);
    ui->Button_Close_Camera->setEnabled(false);
}
//double paly video or advance music
void Window::quick()
{
    if(player)
    {
        player->quicker();
    }
    else if(musicPlayer)
    {
        musicPlayer->quicker(ui->Video_Slider->value());
    }
}
//half play video or back music
void Window::slower()
{
    if(player)
    {
        player->slower();
    }
    else if(musicPlayer)
    {
        musicPlayer->slower(ui->Video_Slider->value());
    }
}



