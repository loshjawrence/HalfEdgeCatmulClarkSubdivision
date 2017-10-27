#ifndef YDOUBLESPINBOX_H
#define YDOUBLESPINBOX_H

#include <QDoubleSpinBox>
#include <QListWidgetItem>
#include <Vertex.h>


class YDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    YDoubleSpinBox(QWidget* p);

signals:
    void sig_sendY(double*);
};

#endif // YDOUBLESPINBOX_H
