#ifndef MYQLISTWIDGET_H
#define MYQLISTWIDGET_H

#include <QListWidget>
#include <QListWidgetItem>
#include <Face.h>

class Face;

class MyFaceListWidget : public QListWidget
{
    Q_OBJECT
public:
    MyFaceListWidget(QWidget* p);

public slots:
    void slot_addFaceID(QListWidgetItem*);
    void slot_setSelected(int);
};

#endif // MYQLISTWIDGET_H
