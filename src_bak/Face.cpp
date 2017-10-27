#include <Face.h>
Face::Face() 
    : start_edge(nullptr), color(), id()
{
}

//Face::Face(HalfEdge* _start_edge, glm::vec4& _color, int _id)
//    : start_edge(_start_edge), color(_color), id(_id)
//{
//    if(_start_edge) {
//        _start_edge->setFace(this);
//    }
//}

Face::Face(HalfEdge* _start_edge, glm::vec4 _color, int _id)
    : start_edge(_start_edge), color(_color), id(_id), sharpness(0.f)
{
    if(_start_edge) {
        _start_edge->setFace(this);
    }
}

Face::~Face() {
}

glm::vec4 Face::getColor() const {
    return color;
}

int Face::getID() const {
    return id;
}

HalfEdge* Face::getStartEdge() const {
    return start_edge;
}
float Face::getSharpness() {
    return sharpness;
}

void Face::setColor(const glm::vec4& _color)  {
    color = _color;
}
void Face::setSharpness(float value)  {
    sharpness = value;
}
void Face::setRed(const float red) {
    color[0] = red;
}

void Face::setGreen(const float green) {
    color[1] = green;
}
void Face::setBlue(const float blue) {
    color[2] = blue;
}

void Face::setID(const int _id) {
    id = _id;
}

void Face::setStartEdge(HalfEdge* const _start_edge) {
    start_edge = _start_edge;
    if(_start_edge->getFace() != this)
        _start_edge->setFace(this);
}

std::ostream& operator<<(std::ostream& o, const Face& f) {
    glm::vec4 c = f.getColor();
    o << "\n\tFACE: ID(" << f.getID() << ") ,startedgeID(" << f.getStartEdge()->getID()
      << "), color(" << c[0] << "," << c[1] << "," << c[2] << "," << c[3] << ")";
    return o;
}
