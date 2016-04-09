#include "videoform.h"
#include "ui_videoform.h"

VideoForm::VideoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoForm)
{
    ui->setupUi(this);

    qtimer = new QTimer(this);                          // instantiate timer
    connect(qtimer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));     // associate timer to processFrameAndUpdateGUI

    mCmdIpandPort = new ConfigureIpPortDialog(this);

    mColorDialog = new QColorDialog(this);
    connect(mColorDialog, SIGNAL(colorSelected(QColor)), this, SLOT(colorSelected(QColor)));

    mFontDialog = new FontSizeDialog(this);
    connect(mFontDialog, SIGNAL(fontChanged(float,float)), this, SLOT(fontSizeChanged(float,float)));
    font_Size = mFontDialog->getFontSize();
    font_Bold = mFontDialog->getFontBold();



}

VideoForm::~VideoForm()
{
    delete ui;
}

void VideoForm::showColorDialog()
{
    mColorDialog->setModal(true);
    mColorDialog->show();
}

void VideoForm::showFontDialog()
{
    mFontDialog->setModal(true);
    mFontDialog->show();
}

void VideoForm::processFrameAndUpdateGUI()
{
    cv::Mat imgOriginal;

    bool blnFrameReadSuccessfully = capWebcam.read(imgOriginal);


    //
    if (!blnFrameReadSuccessfully || imgOriginal.empty()) {                            // if we did not get a frame
        QMessageBox::information(this, "", "Unable to read from webcam \n\n This is probably not a video Stream!\n");        // show error via message box
        exitProgram();                                                              // and exit program
        return;                                                                     //
    }


    QString dataShow = tr("Time: %1").arg(GetTime());
    QString roll = tr("Roll: %1").arg(Roll);
    QString pitch = tr("Pitch: %1").arg(Pitch);
    QString heading = tr("Heading: %1").arg(Heading);

    cv::putText(imgOriginal, "WD Gui", cv::Point(10,40), cv::FONT_HERSHEY_SIMPLEX, font_Size, cv::Scalar(blue,green,red), font_Bold);
    cv::putText(imgOriginal, dataShow.toLocal8Bit().constData(), cv::Point(10,80), cv::FONT_HERSHEY_SIMPLEX, font_Size, cv::Scalar(blue,green,red), font_Bold);
    cv::putText(imgOriginal, roll.toLocal8Bit().constData(), cv::Point(10,120),cv::FONT_HERSHEY_SIMPLEX, font_Size, cv::Scalar(blue,green,red), font_Bold);
    cv::putText(imgOriginal, pitch.toLocal8Bit().constData(), cv::Point(10,160),cv::FONT_HERSHEY_SIMPLEX, font_Size, cv::Scalar(blue,green,red), font_Bold);
    cv::putText(imgOriginal, heading.toLocal8Bit().constData(), cv::Point(10,200),cv::FONT_HERSHEY_SIMPLEX, font_Size, cv::Scalar(blue,green,red), font_Bold);

  //  auto angleRad = (Heading*CV_PI)/180;


  //  auto length = 50;
  //  auto direction =  cv::Point(length * cos(angleRad), length *sin(angleRad));

  //  qDebug() << imgOriginal.rows << imgOriginal.cols;

  //  cv::arrowedLine(imgOriginal, cv::Point(700,220),center +  direction, CV_RGB(255, 0, 0), 1, 8, 0, 0.1);

    QImage qimgOriginal = convertOpenCVMatToQtQImage(imgOriginal);

    ui->labelVideo->setPixmap(QPixmap::fromImage(qimgOriginal));


}

QImage VideoForm::convertOpenCVMatToQtQImage(cv::Mat mat)
{
    if(mat.channels() == 1) {                                   // if 1 channel (grayscale or black and white) image
            return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);     // return QImage
        } else if(mat.channels() == 3) {                            // if 3 channel color image
            cv::cvtColor(mat, mat, CV_BGR2RGB);                     // flip colors
            return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);       // return QImage
        } else {
            qDebug() << "in convertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
        }
        return QImage();        // return a blank QImage if the above did not work
}

void VideoForm::exitProgram()
{
    if(qtimer->isActive()) qtimer->stop();          // if timer is running, stop timer
    return;
}

QString VideoForm::GetTime()
{
    QTime time = QTime::currentTime();
    QString timeString = time.toString();
    return timeString;
}

void VideoForm::on_pushButtonPlay_clicked()
{

    QString CameraStreamUrl;
    QString streamType;
    streamType = mCmdIpandPort->getTypeStream();



    if(streamType == "HTTP Stream")
    {
        CameraStreamUrl = mCmdIpandPort->getHttpAdress();
        capWebcam.open(CameraStreamUrl.toLocal8Bit().constData());

        qtimer->start(25); //update rate for stream
    }
    else if(streamType == "IP Stream")
    {
        QMessageBox::information(this, "WD GUI", "This Type Of Stream Is Not Supported!");
        return;
    }
    else if(streamType == "WEB Camera")
    {
        if(mCmdIpandPort->getWebCameraNumber() > 3)
        {
            QMessageBox::information(this, "WD GUI", "The Web Camera number is bigger then 3!\n\nAre you sure you have so many cameras??");
        }
        capWebcam.open(mCmdIpandPort->getWebCameraNumber());
        qtimer->start(0);
    }
    else
    {
        QMessageBox::critical(this, "WD GUI", "No Stream type is selected!\n\nOpening Configuration Dialog");
        mCmdIpandPort->setModal(true);
        mCmdIpandPort->show();
    }


   qDebug() << "Stream setup: " << streamType << mCmdIpandPort->getHttpAdress() << mCmdIpandPort->getIpAdress() << mCmdIpandPort->getPort();

}



void VideoForm::on_pushButtonConfiguration_clicked()
{
    mCmdIpandPort->setModal(true);
    mCmdIpandPort->show();
}

void VideoForm::on_pushButtonStop_clicked()
{
    qtimer->stop();
    capWebcam.release();
}

void VideoForm::colorSelected(const QColor &color)
{
    red = color.red();
    green = color.green();
    blue = color.blue();
}

void VideoForm::sensorData(QString cmd, QString value)
{


    if(cmd.contains("ROLL"))
    {
        Roll = value.toFloat();
    }
    else if(cmd == "PITCH")
    {
        Pitch = value.toFloat();
    }
    else if(cmd == "HEADING")
    {
        Heading = value.toFloat() + 180;
    }
    else
    {
        return;
    }

    //qDebug() << "Roll" << Roll << "Pitch: " << Pitch << "Heading: " << Heading;
}

void VideoForm::on_pushButtonRecord_clicked()
{

}

void VideoForm::fontSizeChanged(float fontSize, float fontBold)
{
    font_Size = fontSize;
    font_Bold = fontBold;
}



void VideoForm::on_pushButtonTakePicture_clicked()
{
    cv::Mat imgOriginal;

    bool blnFrameReadSuccessfully = capWebcam.read(imgOriginal);

    if(blnFrameReadSuccessfully == true)
    {
        QImage qimgOriginal = convertOpenCVMatToQtQImage(imgOriginal);
        bool success = qimgOriginal.save("C:\Users\EmirD\Pictures\ROV\Rov1.png", "PNG", -1);

        qDebug() << success;

    }
    else
    {
        qDebug() << "We fucked up!";
    }
}
