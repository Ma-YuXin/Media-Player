#include "camera.h"

Camera::Camera()
{
}

void Camera::openCamera(QLabel *lab_camera)
{
    // This label to play images that camera captured;
    lab_camera->clear();
    // Judging if the camera is opened;if not,open it;
    if (!capture.isOpened())
    {
        capture.open(0);
        videoStatues = true;
        std::cout << "Successfully open the camera" << std::endl;
    }
    // To store image;
    Mat cap;
    while (true)
    {
        if (videoStatues)
        {
            capture >> cap;
            if (!cap.empty())
            {
                // Converting the type of cap from mat to Qimage;
                QImage image = matToQImage(cap);
                // Set label can contain pixmap
                lab_camera->setPixmap(QPixmap::fromImage(image).scaled(lab_camera->size(), Qt::KeepAspectRatio));
                lab_camera->show();
                // Waiting for 0.1 Second,to decrease the workload
                Sleep(100);
            }
        }
        else
        {
            // release camera;
            capture.release();
            std::cout << "Successfully release camera in open camera" << std::endl;
            break;
        }
    }
}
void Camera::closeCamera(QLabel *lab_camera)

{
    videoStatues = false;
    lab_camera->clear();
}

void Camera::takingPictures(QLabel *lab_camera)
{
    videoStatues = false;
    capture.open(0);
    Mat picture;
    capture >> picture;
    //store image to picture in a mat class
    if (!picture.empty())
    {
        std::cout << "Taking picture successfully" << std::endl;
        //covet mat to qimage
        QImage  image = matToQImage(picture);
        lab_camera->setPixmap(QPixmap::fromImage(image).scaled(lab_camera->size(), Qt::IgnoreAspectRatio));
        //show image
        lab_camera->show();
    }
    else
    {
        std::cerr << "Taking picture failed , there are something wrong" << std::endl;
    }
    capture.release();
    //     release camera;
}
