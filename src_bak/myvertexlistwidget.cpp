#include <myvertexlistwidget.h>

MyVertexListWidget::MyVertexListWidget(QWidget* p)
    : QListWidget(p)
{
}

void MyVertexListWidget::slot_addVertexID(QListWidgetItem* item) {
    addItem(item);
}

void MyVertexListWidget::slot_setSelected(int id) {
    QString myid = QString::number(id);
    for(int i = this->count()-1; i >= 0; i--) {
        if(item(i)->text() == myid) {
            setCurrentRow(i);
            emit itemClicked(currentItem());
            return;
        }
    }
}
