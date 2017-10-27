#ifndef XDOUBLESPINBOX_H
#define XDOUBLESPINBOX_H

#include <QDoubleSpinBox>
#include <QListWidgetItem>
#include <Vertex.h>


class XDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    XDoubleSpinBox(QWidget* p);

signals:
    void sig_sendX(double*);
};

#endif // XDOUBLESPINBOX_H
