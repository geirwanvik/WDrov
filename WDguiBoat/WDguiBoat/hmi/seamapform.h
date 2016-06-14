#ifndef SEAMAPFORM_H
#define SEAMAPFORM_H

#include <QWidget>




namespace Ui {
class SeaMapForm;
}

class SeaMapForm : public QWidget
{
    Q_OBJECT

public:
    explicit SeaMapForm(QWidget *parent = 0);
    ~SeaMapForm();

private:
    Ui::SeaMapForm *ui;

};

#endif // SEAMAPFORM_H
