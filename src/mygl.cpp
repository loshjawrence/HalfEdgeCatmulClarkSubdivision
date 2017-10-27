#include "mygl.h"
#include <la.h>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>
#include <unistd.h>

MyGL::MyGL(QWidget *parent)
    : GLWidget277(parent),
      geom_cylinder(this), geom_sphere(this), mesh(this), point_hl(this),halfedge_hl(this),face_hl(this),
      prog_lambert(this), prog_flat(this),
      timeCount(0),renderMode(0),
      gl_camera()
{
    // Connect the timer to a function so that when the timer ticks the function is executed
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    //Tell the timer to redraw 60 times per second
    timer.start(16);
}

MyGL::~MyGL()
{
    makeCurrent();
    glDeleteVertexArrays(1, &vao);
    //geom_cylinder.destroy();
    //geom_sphere.destroy();
}

void MyGL::initializeGL()
{
    // Create an OpenGL context using Qt's QOpenGLFunctions_3_2_Core class
    // If you were programming in a non-Qt context you might use GLEW (GL Extension Wrangler)instead
    initializeOpenGLFunctions();
    // Print out some information about the current OpenGL context
    debugContextVersion();

    // Set a few settings/modes in OpenGL rendering
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    // Set the size with which points should be rendered
    glPointSize(5);
    // Set the color with which the screen is filled at the start of each render call.
    glClearColor(0.5, 0.5, 0.5, 1);

    printGLErrorLog();

    // Create a Vertex Attribute Object
    glGenVertexArrays(1, &vao);


    //Create the instances of Cylinder and Sphere.
    //geom_cylinder.create();
    //geom_sphere.create();

    mesh.makeCube();
    mesh.create();

    resetHighlights();
    buildListWidgets();

    // Create and set up the flat lighting shader
    prog_flat.create(":/glsl/flat.vert.glsl", ":/glsl/flat.frag.glsl");

    // Create and set up the diffuse shader
    prog_lambert.create(":/glsl/lambert.vert.glsl", ":/glsl/lambert.frag.glsl");

    // Set a color with which to draw geometry since you won't have one
    // defined until you implement the Node classes.
    // This makes your geometry render green.
    prog_lambert.setGeometryColor(glm::vec4(0,1,0,1));

    // We have to have a VAO bound in OpenGL 3.2 Core. But if we're not
    // using multiple VAOs, we can just bind one once.
//    vao.bind();
    glBindVertexArray(vao);
}

void MyGL::resetHighlights() {
    point_hl.vertex = mesh.faces[0]->getStartEdge()->getVertex();
    point_hl.create();

    halfedge_hl.halfedge = mesh.faces[0]->getStartEdge();
    halfedge_hl.create();

    face_hl.face = mesh.faces[0];
    face_hl.create();
}

void MyGL::clearListWidgets() {
    //qDebug() << "Clearing face list widget";
    emit sig_clearFaceListWidget();
    //qDebug() << "Clearing halfedge list widget";
    emit sig_clearHalfEdgeListWidget();
    //qDebug() << "Clearing vertex list widget";
    emit sig_clearVertexListWidget();
}

void MyGL::buildListWidgets() {
    //qDebug() << "Building face list widget";
    buildFaceListWidget();
//    qDebug() << "Building halfedge list widget";
    buildHalfEdgeListWidget();
//    qDebug() << "Building vertex list widget";
    buildVertexListWidget();
}

void MyGL::buildFaceListWidget() {
    for (unsigned int i = 0; i < mesh.faces.size(); i++) {
        QListWidgetItem* listitem  = new QListWidgetItem( QString::number(mesh.faces[i]->getID()) );
        emit sig_addFaceID( listitem );
    }
}

void MyGL::buildHalfEdgeListWidget() {
    for (unsigned int i = 0; i < mesh.halfedges.size(); i++) {
        QListWidgetItem* listitem  = new QListWidgetItem( QString::number(mesh.halfedges[i]->getID()) );
        emit sig_addHalfEdgeID( listitem );
    }
}

void MyGL::buildVertexListWidget() {
    for (unsigned int i = 0; i < mesh.vertices.size(); i++) {
        QListWidgetItem* listitem  = new QListWidgetItem( QString::number(mesh.vertices[i]->getID()) );
        emit sig_addVertexID( listitem );
    }
}

void MyGL::slot_faceSelected(QListWidgetItem *current) {
    if(current == nullptr) return;
    int id = current->text().toInt();
    Face* myface = mesh.findFace(id);
    if (myface == nullptr) return;

    setFocus();
    face_hl.face = myface;
    face_hl.create();
//    qDebug() << "\nFace " << myface->getID() << " selected";
    emit sig_sendFaceRed((double)myface->getColor()[0]);
    emit sig_sendFaceGreen((double)myface->getColor()[1]);
    emit sig_sendFaceBlue((double)myface->getColor()[2]);
}

void MyGL::slot_updateFaceRed(double red) {
    face_hl.face->setRed(red);
    face_hl.create();
    mesh.create();
}

void MyGL::slot_updateFaceGreen(double green) {
    face_hl.face->setGreen(green);
    face_hl.create();
    mesh.create();
}

void MyGL::slot_updateFaceBlue(double blue) {
    face_hl.face->setBlue(blue);
    face_hl.create();
    mesh.create();
}


void MyGL::slot_halfedgeSelected(QListWidgetItem *current) {
    if(current == nullptr) return;
    int id = current->text().toInt();
    HalfEdge* myhalfedge = mesh.findHalfEdge(id);
    if (myhalfedge == nullptr) return;
    setFocus();
//    std::cout << "\nHalfEdge " << myhalfedge->getID() << " selected";
    halfedge_hl.halfedge = myhalfedge;
    halfedge_hl.create();
}

void MyGL::slot_vertexSelected(QListWidgetItem *current) {
    if(current == nullptr) return;
    int id = current->text().toInt();
    Vertex* myvertex = mesh.findVertex(id);
    if (myvertex == nullptr) return;
    setFocus();
    point_hl.vertex = myvertex;
    point_hl.create();
//    std::cout << "\nVertex " << myvertex->getID() << " selected";
    emit sig_sendVertexX((double)myvertex->getPosition()[0]);
    emit sig_sendVertexY((double)myvertex->getPosition()[1]);
    emit sig_sendVertexZ((double)myvertex->getPosition()[2]);

}

void MyGL::slot_updateVertexX(double x) {
    point_hl.vertex->setX(x);
    mesh.create();
    point_hl.create();
    halfedge_hl.create();
    face_hl.create();
}

void MyGL::slot_updateVertexY(double y) {
    point_hl.vertex->setY(y);
    mesh.create();
    point_hl.create();
    halfedge_hl.create();
    face_hl.create();
}
void MyGL::slot_updateVertexZ(double z) {
    point_hl.vertex->setZ(z);
    mesh.create();
    point_hl.create();
    halfedge_hl.create();
    face_hl.create();
}

void MyGL::slot_splitEdge() {
    setFocus();
    point_hl.vertex = mesh.splitEdge(halfedge_hl.halfedge);
    emit sig_clearHalfEdgeListWidget();
    emit sig_clearVertexListWidget();
    buildHalfEdgeListWidget();
    buildVertexListWidget();
    mesh.create();
    point_hl.create();
    halfedge_hl.create();
    face_hl.create();
}

void MyGL::slot_triangulateFace() {
    setFocus();
    mesh.triangulateFace(face_hl.face);
    emit sig_clearFaceListWidget();
    emit sig_clearHalfEdgeListWidget();
    buildFaceListWidget();
    buildHalfEdgeListWidget();
    mesh.create();
    face_hl.create();
}

void MyGL::slot_extrudeFace() {
    setFocus();
    mesh.extrudeFace(face_hl.face);
    clearListWidgets();
    buildListWidgets();
    mesh.create();
    face_hl.create();
}

void MyGL::slot_catmulClarkSubDivideMesh() {
    setFocus();
    mesh.catmulClarkSubdivision();
    clearListWidgets();
    buildListWidgets();
    mesh.create();
    point_hl.create();
    halfedge_hl.create();
    face_hl.create();
}

void MyGL::slot_makeFacesPlanar() {
    setFocus();
    mesh.makeFacesPlanar();
    clearListWidgets();
    buildListWidgets();
    mesh.create();
    face_hl.create();
}

void MyGL::slot_setVertexSharpnessValue(double value) {
    setFocus();
    point_hl.vertex->setSharpness(value);
    qDebug() << "vertex " << point_hl.vertex->getID() << " sharpness: " << point_hl.vertex->getSharpness();
}

void MyGL::slot_setEdgeSharpnessValue(double value) {
    setFocus();
    halfedge_hl.halfedge->setSharpness(value);
    qDebug() << "halfedge " << halfedge_hl.halfedge->getID()
             << " and sym " << halfedge_hl.halfedge->getSymmetric()->getID() << " sharpness: "
             << halfedge_hl.halfedge->getSharpness() << " and "
             << halfedge_hl.halfedge->getSymmetric()->getSharpness();
}

void MyGL::slot_setFaceSharpnessValue(double value) {
    setFocus();
    face_hl.face->setSharpness(value);
    qDebug() << "face " << face_hl.face->getID() << " sharpness: " << face_hl.face->getSharpness();
}

void MyGL::importToMesh(QString filename) {
    //emit sig_clearSelections();
    mesh.makeOBJ(filename);
    mesh.create();
    clearListWidgets();
    buildListWidgets();
    resetHighlights();
}

void MyGL::exportMeshToObj(QString filename) {
    mesh.exportToObj(filename);
    mesh.create();//mesh vanishes from gl window when written to file
}

void MyGL::resizeGL(int w, int h)
{
    //This code sets the concatenated view and perspective projection matrices used for
    //our scene's camera view.
    gl_camera = Camera(w, h);
    glm::mat4 viewproj = gl_camera.getViewProj();

    // Upload the view-projection matrix to our shaders (i.e. onto the graphics card)

    prog_lambert.setViewProjMatrix(viewproj);
    prog_flat.setViewProjMatrix(viewproj);

    printGLErrorLog();
}

//This function is called by Qt any time your GL window is supposed to update
//For example, when the function updateGL is called, paintGL is called implicitly.
//DO NOT CONSTRUCT YOUR SCENE GRAPH IN THIS FUNCTION!
void MyGL::paintGL()
{
    // Clear the screen so that we only see newly drawn images
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    prog_flat.setViewProjMatrix(gl_camera.getViewProj());
    prog_lambert.setViewProjMatrix(gl_camera.getViewProj());

#define NOPE
#ifdef NOPE
    //Create a model matrix. This one scales the sphere uniformly by 3, then translates it by <-2,0,0>.
    //Note that we have to transpose the model matrix before passing it to the shader
    //This is because OpenGL expects column-major matrices, but you've
    //implemented row-major matrices.
//    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-2,0,0)) * glm::scale(glm::mat4(1.0f), glm::vec3(3,3,3));
    //Send the geometry's transformation matrix to the shader
    //prog_lambert.setModelMatrix(model);
    //Draw the example sphere using our lambert shader
    //prog_lambert.draw(geom_sphere);

    //Now do the same to render the cylinder
    //We've rotated it -45 degrees on the Z axis, then translated it to the point <2,2,0>
    //model = glm::translate(glm::mat4(1.0f), glm::vec3(2,2,0)) * glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0,0,1));
    //prog_lambert.setModelMatrix(model);
    //prog_lambert.draw(geom_cylinder);

    glm::mat4 model = glm::mat4(1.0f);
//            * glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0))
//            * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1,0,0))
//            * glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0,1,0))
//            * glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0,0,1))
//            * glm::scale(glm::mat4(1.0f), glm::vec3(2,2,2));
    if(renderMode == 1) {
        float thetax = glm::radians((timeCount>>1)*1/1.f);
        float thetay = glm::radians((timeCount>>1)*1/1.f);
        float thetaz = glm::radians((timeCount>>1)*1/1.f);
        float sf = glm::clamp(cos(thetax), 0.5, 1.0);
        model = model * glm::translate(glm::mat4(1.0f), glm::vec3(cos(thetax),cos(thetay),cos(thetaz)))
                * glm::rotate(glm::mat4(1.0f), thetax, glm::vec3(1,0,0))
                * glm::rotate(glm::mat4(1.0f), thetay, glm::vec3(0,1,0))
                * glm::rotate(glm::mat4(1.0f), thetaz, glm::vec3(0,0,1))
                * glm::scale(glm::mat4(1.0f), glm::vec3(sf,sf,sf));
    } else {
        prog_flat.setModelMatrix(model);
        prog_flat.draw(point_hl);

        prog_flat.setModelMatrix(model);
        prog_flat.draw(halfedge_hl);

        prog_flat.setModelMatrix(model);
        prog_flat.draw(face_hl);
    }
    prog_lambert.setModelMatrix(model);
    prog_lambert.draw(mesh);




#endif
}


void MyGL::keyPressEvent(QKeyEvent *e)
{

    float amount = 2.0f;
    if(e->modifiers() & Qt::ShiftModifier){
        amount = 10.0f;
    }
    // http://doc.qt.io/qt-5/qt.html#Key-enum
    // This could all be much more efficient if a switch
    // statement were used, but I really dislike their
    // syntax so I chose to be lazy and use a long
    // chain of if statements instead
    if (e->key() == Qt::Key_Escape) {
        QApplication::quit();
    } else if (e->key() == Qt::Key_N) {
        emit sig_setSelectedHalfEdge(halfedge_hl.halfedge->getNext()->getID());
    } else if (e->key() == Qt::Key_M) {
        emit sig_setSelectedHalfEdge(halfedge_hl.halfedge->getSymmetric()->getID());
    } else if (e->key() == Qt::Key_F) {
        emit sig_setSelectedFace(halfedge_hl.halfedge->getFace()->getID());
    } else if (e->key() == Qt::Key_V) {
        emit sig_setSelectedVertex(halfedge_hl.halfedge->getVertex()->getID());
    } else if (e->key() == Qt::Key_H) {
        if (amount == 2.f) {
            emit sig_setSelectedHalfEdge(point_hl.vertex->getHalfEdge()->getID());
        } else if (amount == 10.f) {
            emit sig_setSelectedHalfEdge(face_hl.face->getStartEdge()->getID());
        }

    } else if (e->key() == Qt::Key_Right) {
        gl_camera.RotateAboutUp(-amount);
    } else if (e->key() == Qt::Key_Left) {
        gl_camera.RotateAboutUp(amount);
    } else if (e->key() == Qt::Key_Up) {
        gl_camera.RotateAboutRight(-amount);
    } else if (e->key() == Qt::Key_Down) {
        gl_camera.RotateAboutRight(amount);
    } else if (e->key() == Qt::Key_1) {
        gl_camera.fovy += amount;
    } else if (e->key() == Qt::Key_2) {
        gl_camera.fovy -= amount;
    } else if (e->key() == Qt::Key_W) {
        gl_camera.TranslateAlongLook(amount);
    } else if (e->key() == Qt::Key_S) {
        gl_camera.TranslateAlongLook(-amount);
    } else if (e->key() == Qt::Key_D) {
        gl_camera.TranslateAlongRight(amount);
    } else if (e->key() == Qt::Key_A) {
        gl_camera.TranslateAlongRight(-amount);
    } else if (e->key() == Qt::Key_Q) {
        gl_camera.TranslateAlongUp(-amount);
    } else if (e->key() == Qt::Key_E) {
        gl_camera.TranslateAlongUp(amount);
    } else if (e->key() == Qt::Key_R) {
        if (amount == 2.f) {
            gl_camera = Camera(this->width(), this->height());
        } else if (amount == 10.f) {
            renderMode ^= 1;
            prog_lambert.setRenderMode(renderMode);
//            std::cout << "\nRender mode: " << renderMode;
        }
    }
    gl_camera.RecomputeAttributes();
    update();  // Calls paintGL, among other things
}

void MyGL::timerUpdate()
{
    // This function is called roughly 60 times per second.
    // Use it to perform any repeated actions you want to do,
    // such as
    timeCount++;
    prog_lambert.setTime(timeCount);
    QOpenGLWidget::update();

}
