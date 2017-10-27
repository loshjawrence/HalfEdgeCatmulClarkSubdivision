#include "HalfEdge.h"


HalfEdge::HalfEdge()
    : face(nullptr), vert(nullptr), next(nullptr), sym(nullptr), id(), sharpness()
{
}

HalfEdge::HalfEdge(Face* _face, Vertex* _vert, HalfEdge* _next, HalfEdge* _sym, int _id)
    : face(_face), vert(_vert), next(_next), sym(_sym), id(_id), sharpness(0.f)
{
    if(_face) 
        _face->setStartEdge(this);
    if(_vert) 
        _vert->setHalfEdge(this);
    if(_sym) 
        _sym->setSymmetric(this);
}

HalfEdge::~HalfEdge() {
}

Face* HalfEdge::getFace() const {
    return face;
}

Vertex* HalfEdge::getVertex() const {
    return vert;
}

HalfEdge* HalfEdge::getNext() const {
    return next;
}

HalfEdge* HalfEdge::getSymmetric() const {
    return sym;
}

HalfEdge* HalfEdge::getPrevious() {
    HalfEdge* current = this;
    while(current->next != this) {
        current = current->next;
    }
    return current;
}
float HalfEdge::getSharpness() {
    return sharpness;
}
int HalfEdge::getID() const {
    return id;
}
void HalfEdge::setSharpness(float value)  {
    sharpness = value;
    if(sym != nullptr) {
        sym->sharpness = value;
    }
}
void HalfEdge::setFace(Face* const _face) {
    face = _face;
    if(_face->getStartEdge() != this)
        _face->setStartEdge(this);
}

void HalfEdge::setVertex(Vertex* const _vert) {
    vert = _vert;
    if(_vert->getHalfEdge() != this)
        _vert->setHalfEdge(this);
}

void HalfEdge::setNext(HalfEdge* const _next) {
    next = _next;
}

void HalfEdge::setSymmetric(HalfEdge* const _sym) {
    sym = _sym;
    if(_sym->getSymmetric() != this)
        _sym->setSymmetric(this);
}

void HalfEdge::setID(const int _id) {
    id = _id;
}

std::ostream& operator<<(std::ostream& o, const HalfEdge& he) {
    o << "\n\t\tHALFEDGE: faceID(" << he.getFace()->getID() << "), ID(" << he.getID() << ") ,nextID(" << he.getNext()->getID()
      << "), symID(" << he.getSymmetric()->getID() << "), vertID(" << he.getVertex()->getID() << ")";
    return o;
}

