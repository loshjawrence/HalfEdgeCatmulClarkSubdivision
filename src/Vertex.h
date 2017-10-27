#pragma once

#include "HalfEdge.h"
#include "la.h"
#include <iostream>
class HalfEdge;

class Vertex {

protected:
    friend class Mesh;
    glm::vec4 pos;
    HalfEdge* edge;
    unsigned int id;
    float sharpness;

public:
    Vertex();
    //Vertex(glm::vec4& _pos, HalfEdge* _edge, int _id);
    Vertex(glm::vec4  _pos, HalfEdge* _edge, int _id);
    ~Vertex();

    glm::vec4 getPosition() const;
    HalfEdge* getHalfEdge() const;
    int getID() const;
    float getSharpness();

    void setPosition(const glm::vec4& _pos);
    void setSharpness(float value);
    void setX(const float x);
    void setY(const float y);
    void setZ(const float z);
    void setHalfEdge(HalfEdge* const _edge);
    void setID(const int _id);


};

std::ostream& operator<<(std::ostream& o, const Vertex& v);
