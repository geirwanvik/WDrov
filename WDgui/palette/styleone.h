#ifndef STYLEONE_H
#define STYLEONE_H

#include <QObject>
#include <QProxyStyle>
#include <QStyleFactory>
#include <QtWidgets>
#include <QDebug>
#include <QColorDialog>
#include <QPalette>

QT_BEGIN_NAMESPACE
class QPainterPath;
QT_END_NAMESPACE

class styleOne : public QProxyStyle
{
public:
    styleOne();
    ~styleOne();

    void polish(QPalette &palette) Q_DECL_OVERRIDE;
    void polish(QWidget *widget) Q_DECL_OVERRIDE;
    void unpolish(QWidget *widget) Q_DECL_OVERRIDE;
    int pixelMetric(PixelMetric metric, const QStyleOption *option,
                    const QWidget *widget) const Q_DECL_OVERRIDE;
    int styleHint(StyleHint hint, const QStyleOption *option,
                  const QWidget *widget, QStyleHintReturn *returnData) const Q_DECL_OVERRIDE;
    void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                       QPainter *painter, const QWidget *widget) const Q_DECL_OVERRIDE;
    void drawControl(ControlElement control, const QStyleOption *option,
                     QPainter *painter, const QWidget *widget) const Q_DECL_OVERRIDE;





    QColor getRGB() const;
    void setRGB(const QColor &value);

private:
    static void setTexture(QPalette &palette, QPalette::ColorRole role,
                           const QPixmap &pixmap);
    static QPainterPath roundRectPath(const QRect &rect);



    QColor RGB;





};

#endif // STYLEONE_H
