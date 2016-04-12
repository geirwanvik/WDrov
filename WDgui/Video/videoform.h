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

protected:
     void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

};

#endif // VIDEOFORM_H
