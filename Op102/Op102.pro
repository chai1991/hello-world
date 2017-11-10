TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

INCLUDEPATH += /home/lagopus/data/OpenRGBD-Linux-x64-1.0.1/Include\
               /usr/local/include \
              /usr/local/include/opencv \
              /usr/local/include/opencv2
LIBS += /home/lagopus/data/OpenRGBD-Linux-x64-1.0.1/Redist/libOpenRGBD.so \
        /usr/lib/x86_64-linux-gnu/libGL.so\
        /usr/lib/x86_64-linux-gnu/libglut.so \
        /usr/lib/x86_64-linux-gnu/libGLU.so \
       /usr/local/lib/libopencv_highgui.so \
      /usr/local/lib/libopencv_core.so \
      /usr/local/lib/libopencv_imgproc.so\
       /usr/local/lib/libopencv_imgcodecs.so\
      /usr/local/lib/libopencv_ml.so \
      /usr/local/lib/libopencv_freetype.so \
      /usr/local/lib/libopencv_xfeatures2d.so \
      /usr/local/lib/libopencv_features2d.so \
       /usr/local/lib/libopencv_flann.so \
        /usr/local/lib/libopencv_calib3d.so \
        /usr/local/lib/libopencv_video.so \
        /usr/local/lib/libopencv_videoio.so \
# 　　　　/usr/local/lib/libopencv_objdetect.so
        /usr/local/lib/libopencv_tracking.so
