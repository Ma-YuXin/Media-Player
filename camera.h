#ifndef CAMERA_OPEN_H
#define CAMERA_OPEN_H
#include<opencv2/opencv.hpp>
#include<QLabel>
#include"function.h"
using namespace cv;
using namespace std;
class Camera
{
public:
    VideoCapture capture;
    Camera() ;
    void openCamera(QLabel*lab_camera);     // Open camera
    void closeCamera(QLabel *lab_camera);    // Close camera
    void takingPictures(QLabel *lab_camera); // Take photos
private:
    bool videoStatues = 0;// Set video playing area status; 0 represents free ,1 represents busy;
};

#endif // CAMERA_OPEN_H
