#ifndef SCREENDATA_H
#define SCREENDATA_H

#include <QObject>
#include <QScreen>
#include <QGuiApplication>
#include <QDebug>
#include <QApplication>

class ScreenData : public QObject
{
    Q_OBJECT
public:
    explicit ScreenData(QObject *parent = 0);
    ~ScreenData();

    int getPixelHeight() const;
    void setPixelHeight(int value);
    int getPixelWidth() const;
    void setPixelWidth(int value);
    float getPhysicalDPI() const;
    void setPhysicalDPI(float value);

    qreal ratio() const;
    void setRatio(const qreal &ratio);

    qreal ratioFont() const;
    void setRatioFont(const qreal &ratioFont);

signals:
    void rotationNow(QString rotation);

public slots:

private slots:
    void rotationHappend(Qt::ScreenOrientation orientation);

private:

    void getScreenResolution(void);
    void CalculateRatio(void);
    QString Orientation(Qt::ScreenOrientation orientation);
    int pixelHeight;
    int pixelWidth;
    float physicalDPI;
    qreal mRatio;
    qreal mRatioFont;
    qreal refDpi;
    qreal refHeight;
    qreal refWidth;

};

#endif // SCREENDATA_H
