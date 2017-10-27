#pragma once

#include "Face.h"
#include "Vertex.h"
#include "la.h"
#include <iostream>
class Face;
class Vertex;

class HalfEdge {
protected:
    friend class Mesh;
    Face* face;
    Vertex* vert;
    HalfEdge* next;
    HalfEdge* sym;
    unsigned int id;
    float sharpness;

public:
    HalfEdge();
    HalfEdge(Face* _face, Vertex* _vert, HalfEdge* _next, HalfEdge* _sym, int _id);
    ~HalfEdge();

    Face* getFace() const;
    Vertex* getVertex() const;
    HalfEdge* getNext() const;
    HalfEdge* getSymmetric() const;
    HalfEdge* getPrevious();
    int getID() const;
    float getSharpness();

    void setFace(Face* const _face);
    void setSharpness(float value);
    void setVertex(Vertex* const _vert);
    void setNext(HalfEdge* const _next);
    void setSymmetric(HalfEdge* const _sym);
    void setID(const int _id);

};

std::ostream& operator<<(std::ostream& o, const HalfEdge& he);

