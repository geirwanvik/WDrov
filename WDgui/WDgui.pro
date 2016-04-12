#-------------------------------------------------
#
# Project created by QtCreator 2016-03-19T11:59:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WDgui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Video/configureipportdialog.cpp \
    Video/videoform.cpp \
    Client/clientsetupdialog.cpp \
    Client/tcpclient.cpp \
    Sensors/sensorsetupdialog.cpp \
    WD_Link/WDlink.cpp \
    RovWidgets/atttudeindicatorform.cpp \
    RovWidgets/compassform.cpp \
    RovWidgets/source/qcgaugewidget.cpp \
    Video/fontsizedialog.cpp \
    Video/overlaysettingsdialog.cpp \
    palette/styleone.cpp


HEADERS  += mainwindow.h \
    Video/configureipportdialog.h \
    Video/videoform.h \
    Client/clientsetupdialog.h \
    Client/tcpclient.h \
    Sensors/sensorsetupdialog.h \
    WD_Link/WDlink.h \
    RovWidgets/atttudeindicatorform.h \
    RovWidgets/compassform.h \
    RovWidgets/source/qcgaugewidget.h \
    Video/fontsizedialog.h \
    Video/overlaysettingsdialog.h \
    palette/styleone.h


FORMS    += mainwindow.ui \
    Video/configureipportdialog.ui \
    Video/videoform.ui \
    Client/clientsetupdialog.ui \
    Sensors/sensorsetupdialog.ui \
    RovWidgets/atttudeindicatorform.ui \
    RovWidgets/compassform.ui \
    Video/fontsizedialog.ui \
    Video/overlaysettingsdialog.ui


win32{

INCLUDEPATH +=C:\\OpenCV-3.1.0\\opencv\\build\\include

LIBS +=-LC:\\OpenCV-3.1.0\\mybuild\\lib\\Debug \
    -lopencv_core310d \
    -lopencv_features2d310d \
    -lopencv_flann310d \
    -lopencv_highgui310d \
    -lopencv_imgcodecs310d \
    -lopencv_imgproc310d \
    -lopencv_ml310d \
    -lopencv_objdetect310d \
    -lopencv_photo310d \
    -lopencv_shape310d \
    -lopencv_stitching310d \
    -lopencv_superres310d \
    -lopencv_ts310d \
    -lopencv_video310d \
    -lopencv_videoio310d \
    -lopencv_videostab310d \
    -lopencv_calib3d310d

}

android {

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

    INCLUDEPATH += C:\\opencv\\OpenCV-android-sdk\\sdk\\native\\jni\\include

    OPENCV3RDPARTYLIBS = C:\opencv\OpenCV-android-sdk\sdk\native\3rdparty\libs\armeabi-v7a

    OPENCVNATIVELIBS = C:\opencv\OpenCV-android-sdk\sdk\native\libs\armeabi-v7a


LIBS += $$OPENCV3RDPARTYLIBS/liblibtiff.a \
    $$OPENCV3RDPARTYLIBS/liblibjpeg.a \
    $$OPENCV3RDPARTYLIBS/liblibjasper.a \
    $$OPENCV3RDPARTYLIBS/liblibpng.a \
    $$OPENCV3RDPARTYLIBS/libtbb.a \
    $$OPENCV3RDPARTYLIBS/libIlmImf.a

LIBS += $$OPENCVNATIVELIBS/libopencv_core.a \
   # $$OPENCVNATIVELIBS/libopencv_androidcamera.a \
    $$OPENCVNATIVELIBS/libopencv_flann.a \
    $$OPENCVNATIVELIBS/libopencv_imgproc.a \
    $$OPENCVNATIVELIBS/libopencv_highgui.a \
    $$OPENCVNATIVELIBS/libopencv_features2d.a \
    $$OPENCVNATIVELIBS/libopencv_calib3d.a \
    $$OPENCVNATIVELIBS/libopencv_ml.a \
    $$OPENCVNATIVELIBS/libopencv_objdetect.a \
    $$OPENCVNATIVELIBS/libopencv_photo.a \
    $$OPENCVNATIVELIBS/libopencv_stitching.a \
    $$OPENCVNATIVELIBS/libopencv_superres.a \
    $$OPENCVNATIVELIBS/libopencv_ts.a \
    $$OPENCVNATIVELIBS/libopencv_video.a \
    $$OPENCVNATIVELIBS/libopencv_videostab.a \
    $$OPENCVNATIVELIBS/libopencv_java3.so \
    $$OPENCVNATIVELIBS/libopencv_imgcodecs.a \
    $$OPENCVNATIVELIBS/libopencv_ml.a \
    $$OPENCVNATIVELIBS/libopencv_shape.a \
    $$OPENCVNATIVELIBS/libopencv_videoio.a

   # $$OPENCVNATIVELIBS/libopencv_info.so




}

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

RESOURCES += \
    pictureresources.qrc

