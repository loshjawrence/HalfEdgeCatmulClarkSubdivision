#ifndef MYGL_H
#define MYGL_H

#include <glwidget277.h>
#include <utils.h>
#include <shaderprogram.h>
#include <scene/cylinder.h>
#include <scene/sphere.h>
#include <scene/Mesh.h>
#include <scene/pointhighlight.h>
#include <scene/halfedgehighlight.h>
#include <scene/facehighlight.h>
#include "camera.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>


class MyGL
    : public GLWidget277
{
    Q_OBJECT
private:
    Cylinder geom_cylinder;// The instance of a unit cylinder we can use to render any cylinder
    Sphere geom_sphere;// The instance of a unit sphere we can use to render any sphere

    Mesh mesh;
    PointHighlight point_hl;
    HalfEdgeHighlight halfedge_hl;
    FaceHighlight face_hl;

    int timeCount;
    int renderMode;

    ShaderProgram prog_flat;// A shader program that uses "flat" reflection (no shadowing at all)
    ShaderProgram prog_lambert;// A shader program that uses lambertian reflection

    GLuint vao; // A handle for our vertex array object. This will store the VBOs created in our geometry classes.
                // Don't worry too much about this. Just know it is necessary in order to render geometry.

    Camera gl_camera;

    /// Timer linked to timerUpdate(). Fires approx. 60 times per second
    QTimer timer;


public:
    explicit MyGL(QWidget *parent = 0);
    ~MyGL();

    void initializeGL();
    void clearListWidgets();
    void buildListWidgets();
    void buildFaceListWidget();
    void buildHalfEdgeListWidget();
    void buildVertexListWidget();
    void resetHighlights();
    void importToMesh(QString filename);
    void exportMeshToObj(QString filename);
    void resizeGL(int w, int h);
    void paintGL();

protected:
    void keyPressEvent(QKeyEvent *e);

signals:
    void sig_addFaceID(QListWidgetItem*);
    void sig_sendFaceRed(double);
    void sig_sendFaceGreen(double);
    void sig_sendFaceBlue(double);
    void sig_setSelectedFace(int);
    void sig_clearSelections();
    void sig_clearFaceListWidget();

    void sig_addHalfEdgeID(QListWidgetItem*);
    void sig_setSelectedHalfEdge(int);
    void sig_clearHalfEdgeListWidget();

    void sig_addVertexID(QListWidgetItem*);
    void sig_sendVertexX(double);
    void sig_sendVertexY(double);
    void sig_sendVertexZ(double);
    void sig_setSelectedVertex(int);
    void sig_clearVertexListWidget();

public slots:

    void slot_faceSelected(QListWidgetItem*);
    void slot_updateFaceRed(double red);
    void slot_updateFaceGreen(double green);
    void slot_updateFaceBlue(double blue);

    //halfedge
    void slot_halfedgeSelected(QListWidgetItem*);

    //vertex edit
    void slot_vertexSelected(QListWidgetItem*);
    void slot_updateVertexX(double x);
    void slot_updateVertexY(double y);
    void slot_updateVertexZ(double z);

    ////Mesh Ops
    void slot_splitEdge();
    void slot_triangulateFace();
    void slot_extrudeFace();
    void slot_catmulClarkSubDivideMesh();
    void slot_makeFacesPlanar();
    //sharpness
    void slot_setVertexSharpnessValue(double);
    void slot_setEdgeSharpnessValue(double);
    void slot_setFaceSharpnessValue(double);


private slots:
    /// Slot that gets called ~60 times per second
    void timerUpdate();
};


#endif // MYGL_H
