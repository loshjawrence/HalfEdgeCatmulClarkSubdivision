#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton {

    Q_OBJECT

public:
    MyPushButton(QWidget* p);

public slots:
    //feedback button push to slots to emit meshop signal
    void slot_splitEdgeButtonClicked();
    void slot_triangulateFaceButtonClicked();
    void slot_extrudeFaceButtonClicked();
    void slot_catmulClarkButtonClicked();
    void slot_makeFacesPlanarButtonClicked();
    //sharpness
    void slot_makeVertexSharpButtonClicked();
    void slot_makeEdgeSharpButtonClicked();
    void slot_makeFaceSharpButtonClicked();


signals:
    //mesh ops
    void sig_splitEdge();
    void sig_triangulateFace();
    void sig_extrudeFace();
    void sig_catmulClarkSubDivideMesh();
    void sig_makeFacesPlanar();
    //sharpness
    void sig_getVertexSharpnessValue();
    void sig_getEdgeSharpnessValue();
    void sig_getFaceSharpnessValue();
};

#endif // MYPUSHBUTTON_H
