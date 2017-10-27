#include <myhalfedgelistwidget.h>

MyHalfEdgeListWidget::MyHalfEdgeListWidget(QWidget* p)
    : QListWidget(p)
{
}

void MyHalfEdgeListWidget::slot_addHalfEdgeID(QListWidgetItem* item) {
    addItem(item);
}

void MyHalfEdgeListWidget::slot_setSelected(int id) {
    QString myid = QString::number(id);
    for(int i = this->count()-1; i >= 0; i--) {
        if(item(i)->text() == myid) {
            setCurrentRow(i);
            emit itemClicked(currentItem());
            return;
        }
    }
}
