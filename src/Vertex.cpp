#include "Vertex.h"

class HalfEdge;

Vertex::Vertex()
    : pos(), edge(nullptr), id(), sharpness()
{
}

//Vertex::Vertex(glm::vec4& _pos, HalfEdge* _edge, int _id)
//    : pos(_pos), edge(_edge), id(_id)
//{
//    if(_edge) {
//        _edge->setVertex(this);
//    }
//}

Vertex::Vertex(glm::vec4 _pos, HalfEdge* _edge, int _id)
    : pos(_pos), edge(_edge), id(_id), sharpness(0.f)
{
    if(_edge) {
        _edge->setVertex(this);
    }
}

Vertex::~Vertex() {
}

glm::vec4 Vertex::getPosition() const {
    return pos;
}

HalfEdge* Vertex::getHalfEdge() const {
    return edge;
}

int Vertex::getID() const {
    return id;
}
void Vertex::setSharpness(float value)  {
    sharpness = value;
}
void Vertex::setPosition(const glm::vec4& _pos) {
    pos = _pos;
}
float Vertex::getSharpness() {
    return sharpness;
}
void Vertex::setX(const float x) {
    pos[0] = x;
}

void Vertex::setY(const float y) {
    pos[1] = y;
}

void Vertex::setZ(const float z) {
    pos[2] = z;
}

void Vertex::setHalfEdge(HalfEdge* const _edge) {
    edge = _edge;
    if(_edge->getVertex() != this)
        _edge->setVertex(this);
}

void Vertex::setID(const int _id) {
    id = _id;
}

std::ostream& operator<<(std::ostream& o, const Vertex& v) {
    glm::vec4 pos = v.getPosition();
    o << "\n\t\t\tVERTEX: halfedgeID(" << v.getHalfEdge()->getID() << "), ID(" << v.getID()
      << "), pos(" << pos[0] << "," << pos[1] << "," << pos[2] << ")";
    return o;
}
