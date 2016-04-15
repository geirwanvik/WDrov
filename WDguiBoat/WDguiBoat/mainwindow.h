#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>

#include "Palette/styleone.h"
#include "hmi/instrumentform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void createToolbar();

    QAction *mBoatPanel;
    QAction *mBoatSensors;

    InstrumentForm *mInstrumentForm;
};

#endif // MAINWINDOW_H
