#ifndef FACEHIGHLIGHT_H
#define FACEHIGHLIGHT_H

#include "drawable.h"

#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <la.h>


#include "Face.h"

class Face;

class FaceHighlight : public Drawable {

protected:
    friend class MyGL;
    Face* face;

public:
    FaceHighlight(GLWidget277 *context);
    virtual GLenum drawMode();
    void buildBuffers(std::vector<GLuint>& facering_idx,
                                     std::vector<glm::vec4>& facering_pos,
                                     std::vector<glm::vec4>& facering_col);
    void printBuffers(std::vector<GLuint>* const mesh_idx,
                      std::vector<glm::vec4>* const mesh_vert_pos,
                      std::vector<glm::vec4>* const mesh_vert_col);
    virtual void create();

};

#endif // FACEHIGHLIGHT_H
