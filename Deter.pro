QT += core widgets gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera.cpp \
    function.cpp \
    main.cpp \
    music.cpp \
    video.cpp \
    window.cpp

HEADERS += \
    camera.h \
    function.h \
    music.h \
    video.h \
    window.h

FORMS += \
    window.ui

#INCLUDEPATH += /usr/local/include \
#               /usr/local/include/opencv2 \

#LIBS += -L/usr/local//lib -lopencv_imgcodecs -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio

INCLUDEPATH += /usr/local/include \
/usr/local/include/opencv2

LIBS += /usr/local/lib/libopencv_calib3d.so \
/usr/local/lib/libopencv_core.so \
/usr/local/lib/libopencv_features2d.so \
/usr/local/lib/libopencv_flann.so \
/usr/local/lib/libopencv_highgui.so \
/usr/local/lib/libopencv_imgcodecs.so \
/usr/local/lib/libopencv_imgproc.so \
/usr/local/lib/libopencv_ml.so \
/usr/local/lib/libopencv_objdetect.so \
/usr/local/lib/libopencv_photo.so \
/usr/local/lib/libopencv_stitching.so \
/usr/local/lib/libopencv_videoio.so \
/usr/local/lib/libopencv_video.so \



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
