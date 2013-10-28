INCLUDEPATH += C:/opencv/build/include/
INCLUDEPATH += C:/opencv/build/include/opencv/
INCLUDEPATH += C:/opencv/build/include/opencv2/

LIBS +=  C:/opencv/build/x64/vc11/lib/opencv_core244d.lib
LIBS +=  C:/opencv/build/x64/vc11/lib/opencv_highgui244d.lib
LIBS +=  C:/opencv/build/x64/vc11/lib/opencv_imgproc244d.lib

HEADERS += \
    videodisp.h

SOURCES += \
    videodisp.cpp \
    main.cpp

QT += widgets gui core

