#ifndef MYDOUBLESPINBOX_H
#define MYDOUBLESPINBOX_H

#include <QDoubleSpinBox>

class MyDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    MyDoubleSpinBox(QWidget* p);
public slots:
    void slot_makeVertexSharpButtonClicked();
    void slot_makeEdgeSharpButtonClicked();
    void slot_makeFaceSharpButtonClicked();
signals:
    void sig_setVertexSharpnessValue(double);
    void sig_setEdgeSharpnessValue(double);
    void sig_setFaceSharpnessValue(double);
};
#endif // MYDOUBLESPINBOX_H
