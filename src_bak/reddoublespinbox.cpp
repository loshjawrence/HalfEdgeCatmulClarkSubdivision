#include <reddoublespinbox.h>

RedDoubleSpinBox::RedDoubleSpinBox(QWidget* p)
    : QDoubleSpinBox(p)
{
    setRange(0,1);
    setSingleStep(0.1);
}

