#ifndef REDDOUBLESPINBOX_H
#define REDDOUBLESPINBOX_H

#include <QDoubleSpinBox>
#include <QListWidgetItem>
#include <Face.h>


class RedDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    RedDoubleSpinBox(QWidget* p);

signals:
    void sig_sendRed(double*);
};

#endif // REDDOUBLESPINBOX_H
