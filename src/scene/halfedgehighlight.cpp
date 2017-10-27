#include "halfedgehighlight.h"

HalfEdgeHighlight::HalfEdgeHighlight(GLWidget277 *context)
    : Drawable(context), halfedge(nullptr)
{
}

GLenum HalfEdgeHighlight::drawMode()
{
    // Since we want individual indices in bufIdx to be
    // read to draw our points, we tell that the draw mode
    // of this Drawable is GL_POINT
    return GL_LINES;
}

void HalfEdgeHighlight::create() {

    std::vector<GLuint> halfedge_idx{0,1};

    std::vector<glm::vec4> halfedge_pos(2);
    halfedge_pos[0] = halfedge->getVertex()->getPosition();
    HalfEdge* current = halfedge->getNext();
    while(current->getNext() != halfedge) {
        current = current->getNext();
    }
    halfedge_pos[1] = current->getVertex()->getPosition();


    std::vector<glm::vec4> halfedge_col(2);
    glm::vec4 headcol(1,1,0,1);//yellow
    glm::vec4 tailcol(1,0,0,1);
    halfedge_col[0] = headcol;
    halfedge_col[1] = tailcol;

    count = halfedge_idx.size();

    generateIdx();
    context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    context->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                          sizeof(halfedge_idx) * sizeof(GLuint), halfedge_idx.data(), GL_STATIC_DRAW);

    generatePos();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    context->glBufferData(GL_ARRAY_BUFFER,
                          sizeof(halfedge_pos) *sizeof(glm::vec4), halfedge_pos.data(), GL_STATIC_DRAW);

    generateCol();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    context->glBufferData(GL_ARRAY_BUFFER,
                          sizeof(halfedge_col) *sizeof(glm::vec4), halfedge_col.data(), GL_STATIC_DRAW);

}
