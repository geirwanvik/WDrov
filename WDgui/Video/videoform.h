#ifndef VIDEOFORM_H
#define VIDEOFORM_H

#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QColorDialog>
#include <QTime>
#include <QDateTime>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include <QTimer>

#include "Video/configureipportdialog.h"
#include "Video/fontsizedialog.h"
#include "trackbardialog.h"

using namespace cv;
using namespace std;

namespace Ui {
class VideoForm;
}

class VideoForm : public QWidget
{
    Q_OBJECT

public:
    explicit VideoForm(QWidget *parent = 0);
    ~VideoForm();
    void showColorDialog();
    void showFontDialog();
    trackBarDialog *mTrackerBarDialog;

private slots:
    void processFrameAndUpdateGUI();
    void on_pushButtonPlay_clicked();
    void on_pushButtonConfiguration_clicked();
    void on_pushButtonStop_clicked();
    void colorSelected(const QColor &color);
    void on_pushButtonRecord_clicked();
    void fontSizeChanged(float fontSize, float fontBold);


    void on_pushButtonTakePicture_clicked();

public slots:
    void sensorData(QString cmd, QString value);


private:
    Ui::VideoForm *ui;
    cv::VideoCapture capWebcam;             // Capture object to use with webcam
    QTimer* qtimer;                 // timer for processFrameAndUpdateGUI()
    QImage convertOpenCVMatToQtQImage(cv::Mat mat);       // function prototype
    void exitProgram();                    // function prototype
    ConfigureIpPortDialog *mCmdIpandPort;
    QString GetTime();


    //sensor variabels
    float Roll;
    float Pitch;
    float Heading;

    //Font Colors on video overlay:
    quint8 red;
    quint8 green;
    quint8 blue;
    QColorDialog *mColorDialog;
    float font_Size;
    float font_Bold;
    FontSizeDialog *mFontDialog;


    const int MIN_OBJECT_AREA = 20*20;

    const string windowName = "Original Image";
    //Matrix to store each frame of the webcam feed
    Mat cameraFeed;
    //matrix storage for HSV image
    Mat HSV;
    //matrix storage for binary threshold image
    Mat threshold;
    //x and y values for the location of the object
    int x=0, y=0;

    int H_MIN = 0;
    int H_MAX = 256;
    int S_MIN = 0;
    int S_MAX = 256;
    int V_MIN = 0;
    int V_MAX = 256;

    void morphOps(Mat &thresh);
    void trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed);
    void drawObject(int x, int y,Mat &frame);
    string intToString(int number);
    const int MAX_NUM_OBJECTS=50;
    const int FRAME_WIDTH = 640;
    const int FRAME_HEIGHT = 480;
    const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;

    bool calibrationMode;//used for showing debugging windows, trackbars etc.

    bool mouseIsDragging;//used for showing a rectangle on screen as user clicks and drags mouse
    bool mouseMove;
    bool rectangleSelected;
    cv::Point initialClickPoint, currentMousePoint; //keep track of initial point clicked and current position of mouse
    cv::Rect rectangleROI; //this is the ROI that the user has selected
    vector<int> H_ROI, S_ROI, V_ROI;// HSV values from the click/drag ROI region stored in separate vectors so that we can sort them easily

   void clickAndDrag_Rectangle(int event, int x, int y, int flags, void* param);
    void recordHSV_Values(cv::Mat frame, cv::Mat hsv_frame);
=======
protected:
     void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

>>>>>>> origin/master
};

#endif // VIDEOFORM_H
