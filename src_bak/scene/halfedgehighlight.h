#ifndef HALFEDGEHIGHLIGHT_H
#define HALFEDGEHIGHLIGHT_H

#include "drawable.h"

#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <la.h>


#include "HalfEdge.h"

class HalfEdge;

class HalfEdgeHighlight : public Drawable {

protected:
    friend class MyGL;
    HalfEdge* halfedge;


public:
    HalfEdgeHighlight(GLWidget277 *context);
    virtual GLenum drawMode();
    virtual void create();

};
#endif // HALFEDGEHIGHLIGHT_H
