#ifndef FONTSIZEDIALOG_H
#define FONTSIZEDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QSettings>
#include <QObject>


namespace Ui {
class FontSizeDialog;
}

class FontSizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FontSizeDialog(QWidget *parent = 0);
    ~FontSizeDialog();

    float getFontSize() const;
    void setFontSize(float value);

    float getFontBold() const;
    void setFontBold(float value);

private:
    Ui::FontSizeDialog *ui;

    float fontSize;
    float fontBold;
    void writeSettings();
    void readSettings();


signals:
    void fontChanged(float size, float bold);



private slots:
    void on_pushButtonSaveAndClose_clicked();
    void on_pushButtonCancel_clicked();
};

#endif // FONTSIZEDIALOG_H
