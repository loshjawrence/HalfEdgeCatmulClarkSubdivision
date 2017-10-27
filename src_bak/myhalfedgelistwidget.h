#ifndef MYHALFEDGELISTWIDGET_H
#define MYHALFEDGELISTWIDGET_H


#include <QListWidget>
#include <QListWidgetItem>
#include <HalfEdge.h>
class HalfEdge;

class MyHalfEdgeListWidget : public QListWidget
{
    Q_OBJECT
public:
    MyHalfEdgeListWidget(QWidget* p);

public slots:
    void slot_addHalfEdgeID(QListWidgetItem* item);
    void slot_setSelected(int);

};


#endif // MYHALFEDGELISTWIDGET_H
