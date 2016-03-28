#ifndef OVERLAYSETTINGSDIALOG_H
#define OVERLAYSETTINGSDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QSettings>

namespace Ui {
class OverlaySettingsDialog;
}

class OverlaySettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OverlaySettingsDialog(QWidget *parent = 0);
    ~OverlaySettingsDialog();

private:
    Ui::OverlaySettingsDialog *ui;
};

#endif // OVERLAYSETTINGSDIALOG_H
