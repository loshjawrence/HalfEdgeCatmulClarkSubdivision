#ifndef GREENDOUBLESPINBOX_H
#define GREENDOUBLESPINBOX_H

#include <QDoubleSpinBox>
#include <QListWidgetItem>
#include <Face.h>

class GreenDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    GreenDoubleSpinBox(QWidget* p);


signals:
    void sig_sendGreen(double*);
};

#endif // GREENDOUBLESPINBOX_H
