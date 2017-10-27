#include <mydoublespinbox.h>

MyDoubleSpinBox::MyDoubleSpinBox(QWidget* p)
    : QDoubleSpinBox(p)
{
    setDecimals(1);
    setRange(0,1);
    setSingleStep(0.1);
    setValue(1);
}

void MyDoubleSpinBox::slot_makeVertexSharpButtonClicked() {
    emit sig_setVertexSharpnessValue(value());
}

void MyDoubleSpinBox::slot_makeEdgeSharpButtonClicked() {
    emit sig_setEdgeSharpnessValue(value());
}

void MyDoubleSpinBox::slot_makeFaceSharpButtonClicked() {
    emit sig_setFaceSharpnessValue(value());
}
