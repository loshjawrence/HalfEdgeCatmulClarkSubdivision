#include <zdoublespinbox.h>

ZDoubleSpinBox::ZDoubleSpinBox(QWidget* p)
    : QDoubleSpinBox(p)
{
    setDecimals(3);
    setRange(-10,10);
    setSingleStep(0.1);
}
