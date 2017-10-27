#ifndef MYVERTEXLISTWIDGET_H
#define MYVERTEXLISTWIDGET_H


#include <QListWidget>
#include <QListWidgetItem>
#include <Vertex.h>
class Vertex;

class MyVertexListWidget : public QListWidget
{
    Q_OBJECT
public:
    MyVertexListWidget(QWidget* p);

public slots:
    void slot_addVertexID(QListWidgetItem*);
    void slot_setSelected(int);
};

#endif // MYVERTEXLISTWIDGET_H
