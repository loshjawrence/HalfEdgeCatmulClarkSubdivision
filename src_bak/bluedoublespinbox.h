#ifndef BLUEDOUBLESPINBOX_H
#define BLUEDOUBLESPINBOX_H


#include <QDoubleSpinBox>
#include <QListWidgetItem>
#include <Face.h>


class BlueDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    BlueDoubleSpinBox(QWidget* p);

signals:
    void sig_sendBlue(double*);
};

#endif // BLUEDOUBLESPINBOX_H
