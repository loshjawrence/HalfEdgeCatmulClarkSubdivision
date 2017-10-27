#include <myfacelistwidget.h>
#include <Face.h>

MyFaceListWidget::MyFaceListWidget(QWidget* p)
    : QListWidget(p)
{
}

void MyFaceListWidget::slot_addFaceID(QListWidgetItem* item) {
    addItem(item);
}

void MyFaceListWidget::slot_setSelected(int id) {
    QString myid = QString::number(id);
    for(int i = this->count()-1; i >= 0; i--) {
        if(item(i)->text() == myid) {
            setCurrentRow(i);
            emit itemClicked(currentItem());
            return;
        }
    }
}
