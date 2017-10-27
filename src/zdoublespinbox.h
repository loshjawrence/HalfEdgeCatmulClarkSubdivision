#ifndef ZDOUBLESPINBOX_H
#define ZDOUBLESPINBOX_H


#include <QDoubleSpinBox>
#include <QListWidgetItem>
#include <Vertex.h>


class ZDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    ZDoubleSpinBox(QWidget* p);

signals:
    void sig_sendZ(double*);
};

#endif // ZDOUBLESPINBOX_H
