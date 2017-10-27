#include <ydoublespinbox.h>

YDoubleSpinBox::YDoubleSpinBox(QWidget* p)
    : QDoubleSpinBox(p)
{
    setDecimals(3);
    setRange(-10,10);
    setSingleStep(0.1);
}
