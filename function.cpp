#include "function.h"

// To convert QImage into Mat
Mat QImageToMat(QImage& qim)
{
    Mat mat = Mat(qim.height(), qim.width(),
                  CV_8UC3, (void *)qim.constBits(), qim.bytesPerLine());

    return mat;
}

// To convert Mat into QImage
QImage matToQImage(Mat& mat)
{
    cvtColor(mat, mat, COLOR_BGR2RGB);
    QImage qim((const unsigned char *)mat.data, mat.cols, mat.rows, mat.step,
               QImage::Format_RGB888);

    return qim;
}

// Wait function;
void Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);

    while (QTime::currentTime() < dieTime) QCoreApplication::processEvents(
            QEventLoop::AllEvents,
            100);
}

