#include "pointhighlight.h"

PointHighlight::PointHighlight(GLWidget277 *context)
    : Drawable(context), vertex(nullptr)
{
}

GLenum PointHighlight::drawMode()
{
    // Since we want individual indices in bufIdx to be
    // read to draw our points, we tell that the draw mode
    // of this Drawable is GL_POINT
    return GL_POINTS;
}

void PointHighlight::create() {

    GLuint index = 0;

    glm::vec4 pos = vertex->getPosition();
    glm::vec4 col(1,1,1,1);//white
    count = 1;

    generateIdx();
    context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    context->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                          sizeof(GLuint), &index, GL_STATIC_DRAW);

    generatePos();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    context->glBufferData(GL_ARRAY_BUFFER,
                          sizeof(glm::vec4), &pos, GL_STATIC_DRAW);

    generateCol();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    context->glBufferData(GL_ARRAY_BUFFER,
                          sizeof(glm::vec4), &col, GL_STATIC_DRAW);

}
