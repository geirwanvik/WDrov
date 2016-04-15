#ifndef INSTRUMENTFORM_H
#define INSTRUMENTFORM_H

#include <QWidget>

namespace Ui {
class InstrumentForm;
}

class InstrumentForm : public QWidget
{
    Q_OBJECT

public:
    explicit InstrumentForm(QWidget *parent = 0);
    ~InstrumentForm();

private:
    Ui::InstrumentForm *ui;
};

#endif // INSTRUMENTFORM_H
