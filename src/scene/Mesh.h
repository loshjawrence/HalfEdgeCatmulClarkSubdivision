#pragma once

#include "drawable.h"

#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <la.h>

#include "Face.h"
#include "Vertex.h"
#include "HalfEdge.h"

class Face;
class Vertices;
class HalfEdge;

class Mesh : public Drawable {

protected:
    friend class MyGL;
    std::vector<Face*> faces;
    std::vector<Vertex*> vertices;
    std::vector<HalfEdge*> halfedges;
    unsigned int nextFaceID;
    unsigned int nextVertexID;
    unsigned int nextHalfEdgeID;

public:
    Mesh(GLWidget277 *context);
    void resetMesh();
    void makeCube();
    void makeOBJ(QString);
    void exportToObj(QString);

    int idToIndex(int id);
    Face* findFace(int id);
    HalfEdge* findHalfEdge(int id);
    Vertex* findVertex(int id);

    void initSyms(std::map<Vertex*, std::vector<HalfEdge*>>&);

    //Mesh Ops
    Vertex* splitEdge(HalfEdge*);
    void triangulateFace(Face*);
    void extrudeFace(Face*);
    void catmulClarkSubdivision();
    Vertex* insertVertex(HalfEdge* myedge, glm::vec4& point, HalfEdge** pointedge1, HalfEdge** pointedge2);
    void quadrangulateFace(Face* origface, std::vector<HalfEdge*>& facemidedges,
                           std::map<Face*, glm::vec4>& centroids,
                           std::map< Vertex*, std::vector<HalfEdge*> >& newhalfedges);
    void makeFacesPlanar();

    void updateColorVBO();
    void updatePosNorVBO();
    void buildBuffers(std::vector<GLuint>* const mesh_idx,
                      std::vector<glm::vec4>* const mesh_vert_pos,
                      std::vector<glm::vec4>* const mesh_vert_nor,
                      std::vector<glm::vec4>* const mesh_vert_col);
    void buildColorBuffer(std::vector<glm::vec4>& mesh_vert_col);

    void printMesh();

    virtual void create();

};
