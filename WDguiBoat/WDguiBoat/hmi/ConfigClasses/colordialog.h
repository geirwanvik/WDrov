#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QDialog>
#include <QColorDialog>
#include <QColormap>
#include <QDebug>
#include <QSettings>

namespace Ui {
class ColorDialog;
}

class ColorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorDialog(QWidget *parent = 0);
    ~ColorDialog();



    quint8 getRed() const;
    void setRed(const quint8 &value);

    quint8 getGreen() const;
    void setGreen(const quint8 &value);

    quint8 getBlue() const;
    void setBlue(const quint8 &value);

private slots:
    void on_horizontalSliderRed_sliderMoved(int position);
    void on_horizontalSliderGreen_sliderMoved(int position);
    void on_horizontalSliderBlue_sliderMoved(int position);
    void on_pushButtonSaveAndClose_clicked();

    void on_pushButtonUpdate_clicked();

    void on_pushButtonRed_clicked();

    void on_pushButtonWhite_clicked();

    void on_pushButtonPurple_clicked();

private:
    Ui::ColorDialog *ui;
    QColorDialog *mColor;

    quint8 Red;
    quint8 Green;
    quint8 Blue;

    void ReadSetting();
    void WriteSetting();

    void updateResultColor();
    void updateSliders();

signals:
    void ColorsDialog(quint8 Red, quint8 Green, quint8 Blue);
    void writeToSocket(QString String);

};

#endif // COLORDIALOG_H
