#ifndef FUNCTION_H
#define FUNCTION_H

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
#include <QDebug>
#include "const.h"
#include "ui_window.h"
#include <QTimer>

using namespace cv;
using namespace std;
QImage matToQImage(Mat& mat);//convert mat to qimage
Mat    QImageToMat(QImage& qim);// convert qimage to mat
void   Sleep(int msec);//to make process sleep msec/1000 second;
#endif // FUNCTION_H
