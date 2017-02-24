#include "videoform.h"
#include "ui_videoform.h"


VideoForm::VideoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoForm)
{
    ui->setupUi(this);

    mTrackerBarDialog = new trackBarDialog(this);

    qtimer = new QTimer(this);                          // instantiate timer
    connect(qtimer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));     // associate timer to processFrameAndUpdateGUI

    mCmdIpandPort = new ConfigureIpPortDialog(this);

    mColorDialog = new QColorDialog(this);
    connect(mColorDialog, SIGNAL(colorSelected(QColor)), this, SLOT(colorSelected(QColor)));

    mFontDialog = new FontSizeDialog(this);
    connect(mFontDialog, SIGNAL(fontChanged(float,float)), this, SLOT(fontSizeChanged(float,float)));
    font_Size = mFontDialog->getFontSize();
    font_Bold = mFontDialog->getFontBold();

    calibrationMode = true;

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
    H_MIN = mTrackerBarDialog->H_MIN;
    H_MAX = mTrackerBarDialog->H_MAX;
    S_MIN = mTrackerBarDialog->S_MIN;
    S_MAX = mTrackerBarDialog->S_MAX;
    V_MIN = mTrackerBarDialog->V_MIN;
    V_MAX = mTrackerBarDialog->V_MAX;

    bool blnFrameReadSuccessfully = capWebcam.read(cameraFeed);

    //
    if (!blnFrameReadSuccessfully || cameraFeed.empty()) {                            // if we did not get a frame
        QMessageBox::information(this, "", "Unable to read from webcam \n\n This is probably not a video Stream!\n");        // show error via message box
        exitProgram();                                                              // and exit program
        return;                                                                     //
    }
    cv::namedWindow(windowName);
    //set mouse callback function to be active on "Webcam Feed" window
        //we pass the handle to our "frame" matrix so that we can draw a rectangle to it
        //as the user clicks and drags the mouse
        cv::setMouseCallback(windowName, clickAndDrag_Rectangle(), &cameraFeed);
        //initiate mouse move and drag to false
        mouseIsDragging = false;
        mouseMove = false;
        rectangleSelected = false;

    cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);

    //filter HSV image between values and store filtered image to
            //threshold matrix
    inRange(HSV,Scalar(H_MIN,S_MIN,V_MIN),Scalar(H_MAX,S_MAX,V_MAX),threshold);
   // morphOps(threshold);
    trackFilteredObject(x,y,threshold,cameraFeed);
   // imshow("windowName2",threshold);
    imshow("windowName",cameraFeed);
   // imshow("windowName1",HSV);


    QImage qimgOriginal = convertOpenCVMatToQtQImage(cameraFeed);
    QImage imageHSV = convertOpenCVMatToQtQImage(HSV);
    QImage imageThresold = convertOpenCVMatToQtQImage(threshold);

    ui->orginalPicture->setPixmap(QPixmap::fromImage(qimgOriginal));
    ui->HSVimage->setPixmap(QPixmap::fromImage(imageHSV));
    ui->thresholdedImage->setPixmap(QPixmap::fromImage(imageThresold));

    //waitKey(10);
}
void VideoForm::morphOps(Mat &thresh)
{
    //create structuring element that will be used to "dilate" and "erode" image.
        //the element chosen here is a 3px by 3px rectangle

        Mat erodeElement = getStructuringElement( MORPH_RECT,Size(1,1));
        //dilate with larger element so make sure object is nicely visible
        Mat dilateElement = getStructuringElement( MORPH_RECT,Size(4,4));

        erode(thresh,thresh,erodeElement);
        erode(thresh,thresh,erodeElement);


        dilate(thresh,thresh,dilateElement);
        dilate(thresh,thresh,dilateElement);
}

void VideoForm::trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed)
{
    Mat temp;
        threshold.copyTo(temp);
        //these two vectors needed for output of findContours
       vector< vector<Point> > contours;
       vector<Vec4i> hierarchy;
        //find contours of filtered image using openCV findContours function
        findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
        //use moments method to find our filtered object
        double refArea = 0;
        bool objectFound = false;
        if (hierarchy.size() > 0) {
            int numObjects = hierarchy.size();
            //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
            if(numObjects<MAX_NUM_OBJECTS){
                for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                    Moments moment = moments((cv::Mat)contours[index]);
                    double area = moment.m00;

                    //if the area is less than 20 px by 20px then it is probably just noise
                    //if the area is the same as the 3/2 of the image size, probably just a bad filter
                    //we only want the object with the largest area so we safe a reference area each
                    //iteration and compare it to the area in the next iteration.
                    if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
                        x = moment.m10/area;
                        y = moment.m01/area;
                        objectFound = true;
                        refArea = area;
                    }else objectFound = false;


                }
                //let user know you found an object
                if(objectFound ==true){
                    putText(cameraFeed,"Tracking Object",Point(0,50),2,1,Scalar(0,255,0),2);
                    //draw object location on screen
                    drawObject(x,y,cameraFeed);
                }

            }else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
        }

}

void VideoForm::drawObject(int x, int y, Mat &frame)
{
    //use some of the openCV drawing functions to draw crosshairs
        //on your tracked image
        circle(frame,Point(x,y),20,Scalar(0,255,0),2);
        if(y-25>0)
        line(frame,Point(x,y),Point(x,y-25),Scalar(0,255,0),2);
        else line(frame,Point(x,y),Point(x,0),Scalar(0,255,0),2);
        if(y+25<FRAME_HEIGHT)
        line(frame,Point(x,y),Point(x,y+25),Scalar(0,255,0),2);
        else line(frame,Point(x,y),Point(x,FRAME_HEIGHT),Scalar(0,255,0),2);
        if(x-25>0)
        line(frame,Point(x,y),Point(x-25,y),Scalar(0,255,0),2);
        else line(frame,Point(x,y),Point(0,y),Scalar(0,255,0),2);
        if(x+25<FRAME_WIDTH)
        line(frame,Point(x,y),Point(x+25,y),Scalar(0,255,0),2);
        else line(frame,Point(x,y),Point(FRAME_WIDTH,y),Scalar(0,255,0),2);

        putText(frame,intToString(x)+","+intToString(y),Point(x,y+30),1,1,Scalar(0,255,0),2);
}

string VideoForm::intToString(int number)
{
    std::stringstream ss;
    ss << number;
    return ss.str();
}

void VideoForm::clickAndDrag_Rectangle(int event, int x, int y, int flags, void *param)
{
    //only if calibration mode is true will we use the mouse to change HSV values
        if (calibrationMode == true){
            //get handle to video feed passed in as "param" and cast as Mat pointer
            Mat* videoFeed = (Mat*)param;

            if (event == CV_EVENT_LBUTTONDOWN && mouseIsDragging == false)
            {
                //keep track of initial point clicked
                initialClickPoint = cv::Point(x, y);
                //user has begun dragging the mouse
                mouseIsDragging = true;
            }
            /* user is dragging the mouse */
            if (event == CV_EVENT_MOUSEMOVE && mouseIsDragging == true)
            {
                //keep track of current mouse point
                currentMousePoint = cv::Point(x, y);
                //user has moved the mouse while clicking and dragging
                mouseMove = true;
            }
            /* user has released left button */
            if (event == CV_EVENT_LBUTTONUP && mouseIsDragging == true)
            {
                //set rectangle ROI to the rectangle that the user has selected
                rectangleROI = Rect(initialClickPoint, currentMousePoint);

                //reset boolean variables
                mouseIsDragging = false;
                mouseMove = false;
                rectangleSelected = true;
            }

            if (event == CV_EVENT_RBUTTONDOWN){
                //user has clicked right mouse button
                //Reset HSV Values
                H_MIN = 0;
                S_MIN = 0;
                V_MIN = 0;
                H_MAX = 255;
                S_MAX = 255;
                V_MAX = 255;

            }
            if (event == CV_EVENT_MBUTTONDOWN){

                //user has clicked middle mouse button
                //enter code here if needed.
            }
        }
}

void VideoForm::recordHSV_Values(Mat frame, Mat hsv_frame)
{
    //save HSV values for ROI that user selected to a vector
        if (mouseMove == false && rectangleSelected == true){

            //clear previous vector values
            if (H_ROI.size()>0) H_ROI.clear();
            if (S_ROI.size()>0) S_ROI.clear();
            if (V_ROI.size()>0 )V_ROI.clear();
            //if the rectangle has no width or height (user has only dragged a line) then we don't try to iterate over the width or height
            if (rectangleROI.width<1 || rectangleROI.height<1) qDebug() << "Please drag a rectangle, not a line" << endl;
            else{
                for (int i = rectangleROI.x; i<rectangleROI.x + rectangleROI.width; i++){
                    //iterate through both x and y direction and save HSV values at each and every point
                    for (int j = rectangleROI.y; j<rectangleROI.y + rectangleROI.height; j++){
                        //save HSV value at this point
                        H_ROI.push_back((int)hsv_frame.at<cv::Vec3b>(j, i)[0]);
                        S_ROI.push_back((int)hsv_frame.at<cv::Vec3b>(j, i)[1]);
                        V_ROI.push_back((int)hsv_frame.at<cv::Vec3b>(j, i)[2]);
                    }
                }
            }
            //reset rectangleSelected so user can select another region if necessary
            rectangleSelected = false;
            //set min and max HSV values from min and max elements of each array

            if (H_ROI.size()>0){
                //NOTE: min_element and max_element return iterators so we must dereference them with "*"
                H_MIN = *std::min_element(H_ROI.begin(), H_ROI.end());
                H_MAX = *std::max_element(H_ROI.begin(), H_ROI.end());
                qDebug() << "MIN 'H' VALUE: " << H_MIN << endl;
                qDebug() << "MAX 'H' VALUE: " << H_MAX << endl;
            }
            if (S_ROI.size()>0){
                S_MIN = *std::min_element(S_ROI.begin(), S_ROI.end());
                S_MAX = *std::max_element(S_ROI.begin(), S_ROI.end());
                qDebug() << "MIN 'S' VALUE: " << S_MIN << endl;
                qDebug() << "MAX 'S' VALUE: " << S_MAX << endl;
            }
            if (V_ROI.size()>0){
                V_MIN = *std::min_element(V_ROI.begin(), V_ROI.end());
                V_MAX = *std::max_element(V_ROI.begin(), V_ROI.end());
                qDebug() << "MIN 'V' VALUE: " << V_MIN << endl;
                qDebug() << "MAX 'V' VALUE: " << V_MAX << endl;
            }

        }

        if (mouseMove == true){
            //if the mouse is held down, we will draw the click and dragged rectangle to the screen
            rectangle(frame, initialClickPoint, cv::Point(currentMousePoint.x, currentMousePoint.y), cv::Scalar(0, 255, 0), 1, 8, 0);
        }
}

//   putText(cameraFeed, "WD Gui", Point(10,40), cv::FONT_HERSHEY_SIMPLEX, font_Size, Scalar(blue,green,red), font_Bold);
//    cv::putText(imgOriginal, dataShow.toLocal8Bit().constData(), cv::Point(10,80), cv::FONT_HERSHEY_SIMPLEX, font_Size, cv::Scalar(blue,green,red), font_Bold);
//    cv::putText(imgOriginal, roll.toLocal8Bit().constData(), cv::Point(10,120),cv::FONT_HERSHEY_SIMPLEX, font_Size, cv::Scalar(blue,green,red), font_Bold);
//    cv::putText(imgOriginal, pitch.toLocal8Bit().constData(), cv::Point(10,160),cv::FONT_HERSHEY_SIMPLEX, font_Size, cv::Scalar(blue,green,red), font_Bold);
//    cv::putText(imgOriginal, heading.toLocal8Bit().constData(), cv::Point(10,200),cv::FONT_HERSHEY_SIMPLEX, font_Size, cv::Scalar(blue,green,red), font_Bold);

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


  // qDebug() << "Stream setup: " << streamType << mCmdIpandPort->getHttpAdress() << mCmdIpandPort->getIpAdress() << mCmdIpandPort->getPort();

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
