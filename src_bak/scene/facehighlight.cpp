#include "facehighlight.h"

#define DEBUG 0
FaceHighlight::FaceHighlight(GLWidget277 *context)
    : Drawable(context), face(nullptr)
{
}

GLenum FaceHighlight::drawMode()
{
    return GL_LINE_LOOP;
}

void FaceHighlight::buildBuffers(std::vector<GLuint>& facering_idx,
                                 std::vector<glm::vec4>& facering_pos,
                                 std::vector<glm::vec4>& facering_col) {

    glm::vec4 color = face->getColor();
    color[0] = 1 - color[0];
    color[1] = 1 - color[1];
    color[2] = 1 - color[2];
    unsigned int count = 0;
    HalfEdge* start = face->getStartEdge();
    HalfEdge* current = start;
    do {
        facering_idx.push_back(count++);
        facering_pos.push_back(current->getVertex()->getPosition());
        facering_col.push_back(color);
        current = current->getNext();
    } while(current != start);

}

void FaceHighlight::printBuffers(std::vector<GLuint>* const mesh_idx,
                  std::vector<glm::vec4>* const mesh_vert_pos,
                  std::vector<glm::vec4>* const mesh_vert_col)
{
    std::cout << "\nmesh_idx:";
    for(unsigned int i = 0; i < mesh_idx->size(); i++) {
        std::cout << "\n\t" << i << ": " << (*mesh_idx)[i];
    }
    std::cout << "\nmesh_vert_pos:";
    for(unsigned int i = 0; i < mesh_vert_pos->size(); i++) {
        glm::vec4 pos = (*mesh_vert_pos)[i];
        std::cout << "\n\t" << i << ": " << pos[0] << "," << pos[1] << "," << pos[2] << "," << pos[3];
    }
    std::cout << "\nmesh_vert_col:";
    for(unsigned int i = 0; i < mesh_vert_col->size(); i++) {
        glm::vec4 col = (*mesh_vert_col)[i];
        std::cout << "\n\t" << i << ": " << col[0] << "," << col[1] << "," << col[2] << "," << col[3];
    }

}


void FaceHighlight::create() {
    std::vector<GLuint> facering_idx(0);
    std::vector<glm::vec4> facering_pos(0);
    std::vector<glm::vec4> facering_col(0);

    buildBuffers(facering_idx,facering_pos,facering_col);

#if DEBUG
    FaceHighlight::printBuffers(&facering_idx, &facering_pos, &facering_col);
#endif

    count = facering_idx.size();
    generateIdx();
    context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    context->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                          sizeof(facering_idx) * sizeof(GLuint), facering_idx.data(), GL_STATIC_DRAW);

    generatePos();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    context->glBufferData(GL_ARRAY_BUFFER,
                          sizeof(facering_pos) *sizeof(glm::vec4), facering_pos.data(), GL_STATIC_DRAW);

    generateCol();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    context->glBufferData(GL_ARRAY_BUFFER,
                          sizeof(facering_col) *sizeof(glm::vec4), facering_col.data(), GL_STATIC_DRAW);

}
