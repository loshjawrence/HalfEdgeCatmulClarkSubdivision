#pragma once

#include "HalfEdge.h"
#include "la.h"

class HalfEdge;

class Face {
protected:
    friend class Mesh;
    HalfEdge* start_edge;
    glm::vec4 color;
    unsigned int id;
    float sharpness;

public:
    Face();
    //Face(HalfEdge* _start_edge, glm::vec4& _color, int _id);
    Face(HalfEdge* _start_edge, glm::vec4  _color, int _id);
    ~Face();
    
    glm::vec4 getColor() const;
    int getID() const;
    HalfEdge* getStartEdge() const;
    
    float getSharpness();
    void setColor(const glm::vec4& _color);
    void setSharpness(float value);
    void setRed(const float red);
    void setGreen(const float green);
    void setBlue(const float blue);
    void setID(const int _id);
    void setStartEdge(HalfEdge* const _star_edge);
};

std::ostream& operator<<(std::ostream& o, const Face& f);
