#ifndef POINHIGHLIGHT_H
#define POINHIGHLIGHT_H


#include "drawable.h"

#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <la.h>


#include "Vertex.h"

class Vertices;

class PointHighlight : public Drawable {

protected:
    friend class MyGL;
    Vertex* vertex;

public:
    PointHighlight(GLWidget277 *context);
    virtual GLenum drawMode();
    virtual void create();

};
#endif // POINHIGHLIGHT_H
