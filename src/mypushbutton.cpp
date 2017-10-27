#include <mypushbutton.h>

MyPushButton::MyPushButton(QWidget* p) : QPushButton(p) {
}

void MyPushButton::slot_splitEdgeButtonClicked() {
    emit sig_splitEdge();
}

void MyPushButton::slot_triangulateFaceButtonClicked() {
    emit sig_triangulateFace();
}

void MyPushButton::slot_extrudeFaceButtonClicked() {
    emit sig_extrudeFace();
}

void MyPushButton::slot_catmulClarkButtonClicked() {
    emit sig_catmulClarkSubDivideMesh();
}

void MyPushButton::slot_makeFacesPlanarButtonClicked() {
    emit sig_makeFacesPlanar();
}

void MyPushButton::slot_makeVertexSharpButtonClicked() {
    emit sig_getVertexSharpnessValue();
}

void MyPushButton::slot_makeEdgeSharpButtonClicked() {
    emit sig_getEdgeSharpnessValue();
}

void MyPushButton::slot_makeFaceSharpButtonClicked() {
    emit sig_getFaceSharpnessValue();
}
