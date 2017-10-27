#include "Mesh.h"
#include <iostream>
#include <QFile>
#include <cstdlib>
#include <ctime>
#include <map>
#include <string>


#define DEBUG 0

Mesh::Mesh(GLWidget277 *context) 
    : Drawable(context), nextFaceID(0),nextVertexID(0),nextHalfEdgeID(0)
{
}

void Mesh::makeCube() {
    resetMesh();
    faces = std::vector<Face*>(6);
    vertices = std::vector<Vertex*>(8);
    halfedges = std::vector<HalfEdge*>(24);
    // faces: 0 front, 1 right, 2 bottom, 3 left, 4 top, 5 back
    // first vert is 'bottom-right' of face
    //face 0 front
    vertices[ 0] = new Vertex( glm::vec4( .5f, -.5f, .5f, 1.f), nullptr, 0);
    vertices[ 1] = new Vertex( glm::vec4( .5f,  .5f, .5f, 1.f), nullptr, 1);
    vertices[ 2] = new Vertex( glm::vec4(-.5f,  .5f, .5f, 1.f), nullptr, 2);
    vertices[ 3] = new Vertex( glm::vec4(-.5f, -.5f, .5f, 1.f), nullptr, 3);
    //face 5 back
    vertices[ 4] = new Vertex( glm::vec4(-.5f, -.5f,-.5f, 1.f), nullptr, 4);
    vertices[ 5] = new Vertex( glm::vec4(-.5f,  .5f,-.5f, 1.f), nullptr, 5);
    vertices[ 6] = new Vertex( glm::vec4( .5f,  .5f,-.5f, 1.f), nullptr, 6);
    vertices[ 7] = new Vertex( glm::vec4( .5f, -.5f,-.5f, 1.f), nullptr, 7);

    //face 0 front
    faces[0] = new Face(nullptr, glm::vec4(1.0f,0.0f,0.0f,1.0f), 0);
    halfedges[ 3] = new HalfEdge(faces[0], vertices[3], nullptr      , nullptr,  3);
    halfedges[ 2] = new HalfEdge(faces[0], vertices[2], halfedges[ 3], nullptr,  2);
    halfedges[ 1] = new HalfEdge(faces[0], vertices[1], halfedges[ 2], nullptr,  1);
    halfedges[ 0] = new HalfEdge(faces[0], vertices[0], halfedges[ 1], nullptr,  0);
    halfedges[ 3]->setNext(halfedges[ 0]);
    //face 1 right
    faces[1] = new Face(nullptr, glm::vec4(0.0f,1.0f,0.0f,1.0f), 1);
    halfedges[ 7] = new HalfEdge(faces[1], vertices[0], nullptr      , nullptr,  7);
    halfedges[ 6] = new HalfEdge(faces[1], vertices[1], halfedges[ 7], nullptr,  6);
    halfedges[ 5] = new HalfEdge(faces[1], vertices[6], halfedges[ 6], nullptr,  5);
    halfedges[ 4] = new HalfEdge(faces[1], vertices[7], halfedges[ 5], nullptr,  4);
    halfedges[ 7]->setNext(halfedges[ 4]);
    //face 2 bottom
    faces[2] = new Face(nullptr, glm::vec4(0.0f,0.0f,1.0f,1.0f), 2);
    halfedges[11] = new HalfEdge(faces[2], vertices[4], nullptr      , nullptr, 11);
    halfedges[10] = new HalfEdge(faces[2], vertices[3], halfedges[11], nullptr, 10);
    halfedges[ 9] = new HalfEdge(faces[2], vertices[0], halfedges[10], nullptr,  9);
    halfedges[ 8] = new HalfEdge(faces[2], vertices[7], halfedges[ 9], nullptr,  8);
    halfedges[11]->setNext(halfedges[ 8]);
    //face 3 left
    faces[3] = new Face(nullptr, glm::vec4(1.0f,0.5f,0.5f,1.0f), 3);
    halfedges[15] = new HalfEdge(faces[3], vertices[4], nullptr      , nullptr, 15);
    halfedges[14] = new HalfEdge(faces[3], vertices[5], halfedges[15], nullptr, 14);
    halfedges[13] = new HalfEdge(faces[3], vertices[2], halfedges[14], nullptr, 13);
    halfedges[12] = new HalfEdge(faces[3], vertices[3], halfedges[13], nullptr, 12);
    halfedges[15]->setNext(halfedges[12]);
    //face 4 top
    faces[4] = new Face(nullptr, glm::vec4(0.5f,1.0f,0.5f,1.0f), 4);
    halfedges[19] = new HalfEdge(faces[4], vertices[2], nullptr      , nullptr, 19);
    halfedges[18] = new HalfEdge(faces[4], vertices[5], halfedges[19], nullptr, 18);
    halfedges[17] = new HalfEdge(faces[4], vertices[6], halfedges[18], nullptr, 17);
    halfedges[16] = new HalfEdge(faces[4], vertices[1], halfedges[17], nullptr, 16);
    halfedges[19]->setNext(halfedges[16]);
    //face 5 back
    faces[5] = new Face(nullptr, glm::vec4(0.5f,0.5f,1.0f,1.0f), 5);
    halfedges[23] = new HalfEdge(faces[5], vertices[7], nullptr      , nullptr, 23);
    halfedges[22] = new HalfEdge(faces[5], vertices[6], halfedges[23], nullptr, 22);
    halfedges[21] = new HalfEdge(faces[5], vertices[5], halfedges[22], nullptr, 21);
    halfedges[20] = new HalfEdge(faces[5], vertices[4], halfedges[21], nullptr, 20);
    halfedges[23]->setNext(halfedges[20]);
    //sym edges
    //face 1 right
    halfedges[ 4]->setSymmetric(halfedges[ 9]);
    halfedges[ 5]->setSymmetric(halfedges[23]);
    halfedges[ 6]->setSymmetric(halfedges[17]);
    halfedges[ 7]->setSymmetric(halfedges[ 1]);
    //face 2 bottom
    halfedges[ 8]->setSymmetric(halfedges[20]);
    halfedges[10]->setSymmetric(halfedges[ 0]);
    halfedges[11]->setSymmetric(halfedges[12]);
    //face 3 left
    halfedges[13]->setSymmetric(halfedges[ 3]);
    halfedges[14]->setSymmetric(halfedges[19]);
    halfedges[15]->setSymmetric(halfedges[21]);
    //face 4 top
    halfedges[16]->setSymmetric(halfedges[ 2]);
    halfedges[18]->setSymmetric(halfedges[22]);

    nextHalfEdgeID = halfedges.size();
    nextFaceID = faces.size();
    nextVertexID = vertices.size();
#if DEBUG
    printMesh();
#endif
}

void Mesh::resetMesh() {

    for(unsigned int i = 0; i < faces.size(); i++) {
        if(faces[i] != nullptr) { //
            //qDebug() << "deleting face " << faces[i]->getID();
            delete faces[i];
            faces[i] == nullptr;
        }
    }
    for(unsigned int i = 0; i < vertices.size(); i++) {
        if(vertices[i] != nullptr) {
            //qDebug() << "deleting vertex " << vertices[i]->getID();
            delete vertices[i];
            vertices[i] = nullptr;
        }
    }
    for(unsigned int i = 0; i < halfedges.size(); i++) {
        if(halfedges[i] != nullptr) {
            //qDebug() << "deleting halfedge " << halfedges[i]->getID();
            delete halfedges[i];
            halfedges[i] = nullptr;
        }
    }

    faces = std::vector<Face*>(0);
    vertices = std::vector<Vertex*>(0);
    halfedges = std::vector<HalfEdge*>(0);

    nextFaceID = 0;
    nextVertexID = 0;
    nextHalfEdgeID = 0;
}

void Mesh::makeOBJ(QString filename) {

    QFile objfile(filename);
    if (objfile.open(QIODevice::ReadOnly)) {
//        std::cout << "\nReading OBJ file: " << filename.toStdString();

        //qDebug() << "attempting to delete mesh components..";
        resetMesh();
        //qDebug() << "DONE deleting mesh components";

        QTextStream in(&objfile);
        srand (static_cast <unsigned> (time(0)));
        std::map<Vertex*, std::vector<HalfEdge*>> mymap;
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList words = line.split(" ");
            if(words.at(0).compare("v") == 0) {
                float x = words.at(1).toFloat();
                float y = words.at(2).toFloat();
                float z = words.at(3).toFloat();
                Vertex* vert = new Vertex(glm::vec4(x,y,z,1), nullptr, nextVertexID++);
                vertices.push_back(vert);

            } else if (words.at(0).compare("f") == 0) {
                float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                Face* face = new Face(nullptr, glm::vec4(r,g,b,1), nextFaceID++);
                faces.push_back(face);
                //setup half edges around this face
                for(int i = 1; i < words.size(); i++) {
                    QStringList vtn = words.at(i).split("/");
                    int vert_idx = vtn.at(0).toInt() - 1;
                    HalfEdge* halfedge = new HalfEdge(face, vertices[vert_idx], nullptr, nullptr, nextHalfEdgeID++);
                    mymap[ vertices[vert_idx] ].push_back(halfedge);
                    halfedges.push_back(halfedge);
                }

                //set up next pointers
                int last = halfedges.size() - 1;
                int first = last - (words.size() - 2);
                halfedges[last]->setNext( halfedges[first] );
                for (int i = first; i < last; i++) {
                    halfedges[i]->setNext( halfedges[i+1] );
                }

            } //if words compare
        } //while not atEnd

        //Begin setting up symmmetric halfedge pointers
        initSyms(mymap);

        //setupAllSyms();
        objfile.close();
    } else {
        std::cout << "\nERROR: Could not open OBJ file: " << filename.toStdString();
    }
}

int Mesh::idToIndex(int id) {
    if (vertices[id]->getID() == id) {
        return id;
    } else {
        for(unsigned int i = 0; i < vertices.size(); i++) {
            if (vertices[i]->getID() == i) {
                return i;

            }
        }
    }
    return -1;
}

Face* Mesh::findFace(int id) {
    if (faces[id]->getID() == id) {
        return faces[id];
    } else {
        for(unsigned int i = 0; i < faces.size(); i++) {
            if (faces[i]->getID() == i) {
                return faces[i];
            }
        }
    }
    return nullptr;
}

HalfEdge* Mesh::findHalfEdge(int id) {
    if (halfedges[id]->getID() == id) {
        return halfedges[id];
    } else {
        for(unsigned int i = 0; i < halfedges.size(); i++) {
            if (halfedges[i]->getID() == i) {
                return halfedges[i];
            }
        }
    }
    return nullptr;
}

Vertex* Mesh::findVertex(int id) {
    if (vertices[id]->getID() == id) {
        return vertices[id];
    } else {
        for(unsigned int i = 0; i < vertices.size(); i++) {
            if (vertices[i]->getID() == i) {
                return vertices[i];
            }
        }
    }
    return nullptr;
}

void Mesh::exportToObj(QString filename) {
    QFile objfile(filename);
    if (objfile.open(QIODevice::WriteOnly)) {
        std::cout << "\Writing OBJ file: " << filename.toStdString();
        QTextStream out(&objfile);
        out.setRealNumberPrecision(5);

        //vertices
        for(unsigned int i = 0; i < vertices.size(); i++) {
            glm::vec4 pos = vertices[i]->getPosition();
            out << "\nv " << pos[0] << " " << pos[1] << " " << pos[2];
        }

        //normals, create map of (face*, map(vertex*,offset))
        std::map< Face*, std::map<Vertex*,int> > lookup_normal;
        int idx = 0;
        for(unsigned int i = 0; i < faces.size(); i++) {//assuming face is flat
            HalfEdge* start = faces[i]->getStartEdge();
            HalfEdge* next = start->getNext();
            HalfEdge* current = next->getNext();

            glm::vec4 s0_v4 = next->getVertex()->getPosition() - start->getVertex()->getPosition();
            glm::vec4 s1_v4 = current->getVertex()->getPosition() - start->getVertex()->getPosition();
            glm::vec3 s0_v3(s0_v4);
            glm::vec3 s1_v3(s1_v4);
            glm::vec3 face_nor_v3 = glm::cross(s0_v3, s1_v3);
            count = 0;
            lookup_normal[ faces[i] ][start->getVertex()] = idx + count++;
            out << "\nvn " << face_nor_v3[0] << " " << face_nor_v3[1] << " " << face_nor_v3[2];
            lookup_normal[ faces[i] ][next->getVertex()] = idx + count++;
            out << "\nvn " << face_nor_v3[0] << " " << face_nor_v3[1] << " " << face_nor_v3[2];
            lookup_normal[ faces[i] ][current->getVertex()] = idx + count++;
            out << "\nvn " << face_nor_v3[0] << " " << face_nor_v3[1] << " " << face_nor_v3[2];

            current = current->getNext();
            do {
                lookup_normal[ faces[i] ][current->getVertex()] = idx + count++;
                out << "\nvn " << face_nor_v3[0] << " " << face_nor_v3[1] << " " << face_nor_v3[2];
                current = current->getNext();
            } while(current != start);
            idx += count;
        }

        //faces
        for(unsigned int i = 0; i < faces.size(); i++) {
            out << "\nf";
            HalfEdge* start = faces[i]->getStartEdge();
            HalfEdge* current = start;
            do {
                int vert_idx = idToIndex(current->getVertex()->getID());
                out << " " << ++vert_idx << "/" << "0" << "/" << ++(lookup_normal[ faces[i] ][ current->getVertex()]);

                current = current->getNext();
            } while(current != start);
        }
        objfile.close();
    } else {
       std::cout << "\nERROR: Could not open OBJ file: " << filename.toStdString();
    }

}

void Mesh::initSyms(std::map<Vertex*, std::vector<HalfEdge*>>& mymap) {
    for(std::map<Vertex*,std::vector<HalfEdge*>>::iterator iter = mymap.begin(); iter != mymap.end(); iter++) {
        const Vertex* const vert_head =  iter->first;
        const std::vector<HalfEdge*> edges = iter->second;
        for(int i = edges.size()-1; i >= 0; i--) {
            if(edges[i]->getSymmetric() != nullptr) {
                continue;
            }
            HalfEdge* start = edges[i];
            Vertex* vert_tail = start->getPrevious()->vert;
            const std::vector<HalfEdge*> poss_syms = mymap[vert_tail];
            for(int j = poss_syms.size()-1; j >= 0; j--) {
                if(poss_syms[j]->getSymmetric() != nullptr) {
                    continue;
                }
                HalfEdge* poss_start = poss_syms[j];
                if(poss_start->getPrevious()->vert == vert_head) {
                    edges[i]->setSymmetric(poss_start);
                    break;
                }
            }//poss_syms
        }
    }
}

Vertex* Mesh::splitEdge(HalfEdge* myedge) {
    HalfEdge* start = myedge;
    HalfEdge* mysym = myedge->sym;
    HalfEdge* prev = start->getPrevious();

    Vertex* behind = prev->vert;
    Vertex* midvert = new Vertex((behind->pos + myedge->vert->pos) / 2.f, nullptr, nextVertexID++);
    HalfEdge* newedge = new HalfEdge(myedge->face, midvert, myedge, nullptr, nextHalfEdgeID++ );
    HalfEdge* newsym = new HalfEdge(mysym->face, mysym->vert,mysym->next, newedge, nextHalfEdgeID++);
    halfedges.push_back(newedge);
    halfedges.push_back(newsym);
    vertices.push_back(midvert);
    prev->next = newedge;
    mysym->next = newsym;
    mysym->vert = midvert;
    return midvert;
}

void Mesh::triangulateFace(Face* myface) {
    srand (static_cast <unsigned> (time(0)));
    HalfEdge* last = myface->start_edge->getPrevious();
    Vertex* root = last->vert;
    HalfEdge* beforevert = myface->start_edge->next;
    HalfEdge* aftervert = beforevert->next;
    HalfEdge* facestart = myface->start_edge;
    while(aftervert != last) {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        Face* newface = new Face(facestart,glm::vec4(r,g,b,1),nextFaceID++);
        HalfEdge* facelastedge = new HalfEdge(newface,root,facestart,nullptr,nextHalfEdgeID++);
        beforevert->next = facelastedge;
        beforevert->face = newface;
        HalfEdge* facelastsym = new HalfEdge(myface,beforevert->vert,aftervert,facelastedge,nextHalfEdgeID++);
        last->next = facelastsym;
        facestart = facelastsym;
        beforevert = aftervert;
        aftervert = aftervert->next;

        faces.push_back(newface);
        halfedges.push_back(facelastedge);
        halfedges.push_back(facelastsym);
    }
}

void Mesh::makeFacesPlanar() {
    for(int i = 0; i < faces.size(); i++) {
        HalfEdge* prev = faces[i]->start_edge;
        HalfEdge* last = prev->getPrevious();
        HalfEdge* next = prev->next;
        glm::vec4 root_pos = prev->sym->vert->pos;
        glm::vec4 prev_pos = prev->vert->pos;
        glm::vec4 next_pos = next->vert->pos;

        glm::vec4 s0_v4 = prev_pos - root_pos;
        glm::vec4 s1_v4 = next_pos - root_pos;
        glm::vec3 s0_v3(s0_v4);
        glm::vec3 s1_v3(s1_v4);
        glm::vec3 cross_normal_ref = glm::normalize( glm::cross(s0_v3, s1_v3) );

        prev = next;
        next = next->next;
        while(next != last) {
            prev_pos = prev->vert->pos;
            next_pos = next->vert->pos;

            s0_v4 = prev_pos - root_pos;
            s1_v4 = next_pos - root_pos;
            s0_v3.x = s0_v4.x; s0_v3.y = s0_v4.y; s0_v3.z = s0_v4.z;
            s1_v3.x = s1_v4.x; s1_v3.y = s1_v4.y; s1_v3.z = s1_v4.z;
            glm::vec3 cross_normal = glm::normalize( glm::cross(s0_v3, s1_v3) );

            if( 1.f - glm::dot(cross_normal_ref, cross_normal) > FLT_EPSILON ) {
                triangulateFace(faces[i]);
                break;
            }
            prev = next;
            next = next->next;
        }



    }
}

void Mesh::extrudeFace(Face* myface) {
    srand (static_cast <unsigned> (time(0)));

    //get normal
    HalfEdge* start = myface->start_edge;
    glm::vec4 s0_v4 = start->next->vert->pos - start->vert->pos;
    glm::vec4 s1_v4 = start->next->next->vert->pos - start->vert->pos;
    glm::vec3 s0_v3(s0_v4);
    glm::vec3 s1_v3(s1_v4);
    glm::vec3 nor_dist_v3 = 0.5f * glm::normalize(glm::cross(s0_v3, s1_v3));
    glm::vec4 nor_dist_v4(nor_dist_v3.x,nor_dist_v3.y,nor_dist_v3.z,0);

    HalfEdge* current = start;
    HalfEdge* last = start->getPrevious();
    HalfEdge* previous = last;
    Vertex* curr_vert = current->vert;
    Vertex* prev_vert = current->sym->vert;

    Vertex* ext_prev_vert = new Vertex(prev_vert->pos + nor_dist_v4 , previous   , nextVertexID++);
    vertices.push_back(ext_prev_vert);

    std::map<Vertex*,std::vector<HalfEdge*>> mymap;

    do {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        Vertex* ext_curr_vert = nullptr;
        if (current == last) {
            ext_curr_vert = current->vert;// on final face, ext_curr_vert exists and current already points to it
            curr_vert = current->next->sym->next->vert;
        } else {
            ext_curr_vert = new Vertex(curr_vert->pos + nor_dist_v4 , current    , nextVertexID++);
            vertices.push_back(ext_curr_vert);
        }
        Face* newface   = new Face(nullptr  , glm::vec4(r,g,b,1)    , nextFaceID++);
        HalfEdge* top   = new HalfEdge(newface, curr_vert       , nullptr   , current->sym  , nextHalfEdgeID++);
        HalfEdge* right = new HalfEdge(newface, prev_vert       , top       , nullptr       , nextHalfEdgeID++);
        HalfEdge* bot   = new HalfEdge(newface, ext_prev_vert   , right     , current       , nextHalfEdgeID++);
        HalfEdge* left  = new HalfEdge(newface, ext_curr_vert   , bot       , nullptr       , nextHalfEdgeID++);
        top->next = left;

        faces.push_back(newface);
        halfedges.push_back(top);
        halfedges.push_back(right);
        halfedges.push_back(bot);
        halfedges.push_back(left);

        mymap[left->vert].push_back(left);
        mymap[right->vert].push_back(right);

        previous = current;
        current = current->next;
        curr_vert = current->vert;
        prev_vert = current->sym->vert;
        ext_prev_vert = ext_curr_vert;
    } while(current != start);
    initSyms(mymap);
}

void Mesh::catmulClarkSubdivision() {
    ////CENTROIDS
    std::map<Face*, glm::vec4> centroids;
    for(int i = 0; i < faces.size(); i++) {
        HalfEdge* start = faces[i]->start_edge;
        HalfEdge* current = start;
        unsigned int count = 0;
        glm::vec4 sum(0,0,0,0);
        do {
            sum += current->vert->pos;
            count++;
            current = current->next;
        } while (current != start);
        sum /= count; // make sure this is correct;
        centroids[ faces[i] ] = sum;
    }

    ////SMOOTHED MIDPOINTS
    std::map< HalfEdge*, char > processed;//contains syms of already processed halfedges
    std::map< Face*, std::vector<HalfEdge*> > facemidedges;
    unsigned int origsizevertices = vertices.size();
    unsigned int origsizehalfedges = halfedges.size();
    unsigned int origsizefaces = faces.size();
    for (int i = 0; i < origsizehalfedges; i++) { //stuff is getting push_back so dont process the new stuff
        if(processed.count(halfedges[i]) == 1) {//check if key exists
            continue;
        }
        glm::vec4 f1 = centroids[ halfedges[i]->face ];
        glm::vec4 f2 = centroids[ halfedges[i]->sym->face ];
        glm::vec4 v1 = halfedges[i]->vert->pos;
        glm::vec4 v2 = halfedges[i]->sym->vert->pos;

        float u = halfedges[i]->face->sharpness;
        float u2 = halfedges[i]->sym->face->sharpness;
        if (u2 > u) {
            u = u2;
        }
        //u += halfedges[i]->sym->face->sharpness;
        u += halfedges[i]->sharpness;

        if(u > 1.f) u = 1.f;
        glm::vec4 smoothmid = ( ((1.f-u) * (f1 + f2)/2.f) + ((v1 + v2)/2.f) ) / (1.f + (1.f-u));

        //// ADDING SMOOTHED MIDPOINT
        HalfEdge* midedge1;
        HalfEdge* midedge2;
        Vertex* midvert = insertVertex(halfedges[i], smoothmid, &midedge1, &midedge2);
        midedge1->setSharpness(halfedges[i]->sharpness);
        midedge2->setSharpness(halfedges[i]->sharpness);
        facemidedges[midedge1->face].push_back(midedge1);
        facemidedges[midedge2->face].push_back(midedge2);
        processed[ halfedges[i]->sym ] = 1;
    }

    //processed.clear();

    ////SMOOTH ORIGINAL VERTICES
    for(int i = 0; i < origsizevertices; i++) {
        HalfEdge* start = vertices[i]->edge;
        HalfEdge* current = start;
        float n = 0;
        glm::vec4 sume(0,0,0,0);
        glm::vec4 sumf(0,0,0,0);
        do {
            sumf += centroids[current->face];
            sume += current->next->vert->pos;
            n++;
            current = current->next->sym;
        } while(current != start);



        float vertsharpness = vertices[i]->sharpness;

        current = vertices[i]->edge;
        Face* startface = current->face;
        float facesharpness = startface->sharpness;//just take max face sharpness
        current = current->next->sym;
        while(current->face != startface) {
//            facesharpness += current->face->sharpness;
//            if(facesharpness >= 1.f) {
//                break;
//            }
            if (current->face->sharpness > facesharpness) {
                facesharpness = current->face->sharpness;
            }
            current = current->next->sym;
        }

        //check if 2 or more are sharp
        std::map<HalfEdge*,float> sharpedges;
        float maxedgesharp = 0.f;
        start = vertices[i]->edge;
        current = start;
        do {
            if(current->sharpness > 0.f) {
                sharpedges[current] = current->sharpness;
                if(current->sharpness > maxedgesharp) {
                    maxedgesharp = current->sharpness;
                }
            }
            current = current->next->sym;
        } while(current != start);

        //vector from orig vert to smoothed position
        glm::vec4 fully_smoothed_pos = ( (n-2) * vertices[i]->pos / n )
                + ( (sume + sumf) / (n*n) );

        //should prob lerp between all of these settings
        if(vertsharpness > 0.f) {
            float u = vertsharpness;
            vertices[i]->pos = ((1.f-u) * fully_smoothed_pos) + (u * vertices[i]->pos);
        } else if (facesharpness > 0.f) {
            float u = facesharpness;
            vertices[i]->pos = ((1.f-u) * fully_smoothed_pos) + (u * vertices[i]->pos);
        } else if (sharpedges.size() >= 2) {
            if(sharpedges.size() > 2) {
                 float u = maxedgesharp;
                 vertices[i]->pos = ((1.f-u) * fully_smoothed_pos) + (u * vertices[i]->pos);
            } else if (sharpedges.size() == 2) {
                std::map<HalfEdge*,float>::iterator it = sharpedges.begin();
                HalfEdge* edge_1 = it->first;
                glm::vec4 edge_1_endpoint = edge_1->sym->vert->pos;
                float u1 = it->second;
                it++;
                HalfEdge* edge_2 = it->first;
                glm::vec4 edge_2_endpoint = edge_2->sym->vert->pos;
                float u2 = it->second;
                vertices[i]->pos =  ( ( 0.75f + (.125f * (1.f - u1)) + (.125f * (1.f - u2)) ) * vertices[i]->pos)
                        + (0.125f * (u1) * edge_1_endpoint)
                        + (0.125f * (u2) * edge_2_endpoint);

            }

        } else {
            vertices[i]->pos = fully_smoothed_pos;
        }


        vertices[i]->pos.w = 1.f;
    }


    ////QUADRANGULATE ORIGINAL FACES
    /// new faces made up of an orignal vert, a centroid
    /// and a pair of mids on either side of the vert
    std::map< Vertex*, std::vector<HalfEdge*> > newhalfedges;
    for( int i = 0; i < origsizefaces; i++) {
        quadrangulateFace(faces[i], facemidedges[ faces[i] ], centroids, newhalfedges);
    }

    initSyms(newhalfedges);



}

void Mesh::quadrangulateFace(Face* origface, std::vector<HalfEdge*>& midedges,
                             std::map<Face*, glm::vec4>& centroids,
                             std::map< Vertex*, std::vector<HalfEdge*> >& newhalfedges)
{
    Vertex* centroid = new Vertex(centroids[origface], nullptr, nextVertexID++);
    vertices.push_back(centroid);
    for(int i = 0; i < midedges.size(); i++) {
        ////FIND MID ON OTHER SIDE OF VERT FOR THIS FACE
        HalfEdge* start = midedges[i];
        HalfEdge* current = start;
        do {
            if(current->sym->face == origface){
                break;
            }
            current = current->sym->next;
        } while(current != start);
        Vertex* othermid = current->vert;
        HalfEdge* origverthalfedge = current->sym;
        Vertex* origvert = origverthalfedge->vert;
        Face* newface;
        if (i != midedges.size() -  1) {
            newface = new Face(start, origface->color, nextFaceID++);
            newface->sharpness = origface->sharpness;
            faces.push_back(newface);
        } else {
            newface = origface;
        }

        HalfEdge* fromcentroid = new HalfEdge(newface, othermid, origverthalfedge, nullptr, nextHalfEdgeID++);
        HalfEdge* tocentroid = new HalfEdge(newface, centroid, fromcentroid, nullptr, nextHalfEdgeID++);
        midedges[i]->face = newface;
        midedges[i]->next = tocentroid;
        origverthalfedge->face = newface;

        newhalfedges[othermid].push_back(fromcentroid);
        newhalfedges[centroid].push_back(tocentroid);


        halfedges.push_back(fromcentroid);
        halfedges.push_back(tocentroid);
    }
}

Vertex* Mesh::insertVertex(HalfEdge* myedge, glm::vec4& point, HalfEdge** pointedge1, HalfEdge** pointedge2) {
    HalfEdge* mysym = myedge->sym;
    HalfEdge* prev = myedge->getPrevious();

    Vertex* midvert = new Vertex(point, nullptr, nextVertexID++);
    HalfEdge* newedge = new HalfEdge(myedge->face, midvert, myedge, nullptr, nextHalfEdgeID++ );
    HalfEdge* newsym = new HalfEdge(mysym->face, mysym->vert,mysym->next, newedge, nextHalfEdgeID++);
    halfedges.push_back(newedge);
    halfedges.push_back(newsym);
    vertices.push_back(midvert);
    prev->next = newedge;
    mysym->next = newsym;
    mysym->vert = midvert;
    *pointedge1 = newedge;
    *pointedge2 = mysym;
    return midvert;
}

void Mesh::buildBuffers(std::vector<GLuint>* const mesh_idx,
                        std::vector<glm::vec4>* const mesh_vert_pos,
                        std::vector<glm::vec4>* const mesh_vert_nor,
                        std::vector<glm::vec4>* const mesh_vert_col)
{   

    int vert_idx = -1;

    for(unsigned int i = 0; i < faces.size(); i++) {
        glm::vec4 face_col = faces[i]->getColor();
        HalfEdge* start = faces[i]->getStartEdge();
        HalfEdge* current = start;
        int root_idx = ++vert_idx; 
        mesh_vert_pos->push_back(current->getVertex()->getPosition());
        mesh_idx->push_back(root_idx);

        current = current->getNext();
        mesh_vert_pos->push_back(current->getVertex()->getPosition());
        mesh_idx->push_back(++vert_idx);

        current = current->getNext();
        mesh_vert_pos->push_back(current->getVertex()->getPosition());
        mesh_idx->push_back(++vert_idx);
        int last_idx = vert_idx;
        
        glm::vec4 s0_v4 = (*mesh_vert_pos)[vert_idx-1] - (*mesh_vert_pos)[root_idx];
        glm::vec4 s1_v4 = (*mesh_vert_pos)[last_idx  ] - (*mesh_vert_pos)[root_idx];
        glm::vec3 s0_v3(s0_v4);
        glm::vec3 s1_v3(s1_v4);
        glm::vec3 face_nor_v3 = glm::cross(s0_v3, s1_v3);
        glm::vec4 face_nor(face_nor_v3[0],face_nor_v3[1],face_nor_v3[2],0.f);
        mesh_vert_nor->push_back(face_nor);
        mesh_vert_nor->push_back(face_nor);
        mesh_vert_nor->push_back(face_nor);
        mesh_vert_col->push_back(face_col);
        mesh_vert_col->push_back(face_col);
        mesh_vert_col->push_back(face_col);

        current = current->getNext();
        while(current != start) {
            mesh_vert_pos->push_back(current->getVertex()->getPosition());
            mesh_vert_nor->push_back(face_nor);
            mesh_vert_col->push_back(face_col);

            mesh_idx->push_back(root_idx);
            mesh_idx->push_back(last_idx);
            mesh_idx->push_back(++vert_idx);

            last_idx = vert_idx;
            current = current->getNext();
        }
    }
}

void Mesh::printMesh() {
    std::cout << "\nMESH";
    for(unsigned int i = 0; i < faces.size(); i++) {
        std::cout << *(faces[i]);
        HalfEdge* start = faces[i]->getStartEdge();
        HalfEdge* current = start;
        do {
            std::cout << *current << *(current->getVertex()) ;
            current = current->getNext();
        } while (current != start);
    }
}

void printBuffers(std::vector<GLuint>* const mesh_idx,
                  std::vector<glm::vec4>* const mesh_vert_pos,
                  std::vector<glm::vec4>* const mesh_vert_nor,
                  std::vector<glm::vec4>* const mesh_vert_col)
{
    std::cout << "\nmesh_idx:";
    for(unsigned int i = 0; i < mesh_idx->size(); i += 3) {
        std::cout << "\n\tTriangle " << i/3 << ": " << (*mesh_idx)[i] << "," << (*mesh_idx)[i+1] << "," << (*mesh_idx)[i+2];
    }
    std::cout << "\nmesh_vert_pos:";
    for(unsigned int i = 0; i < mesh_vert_pos->size(); i++) {
        glm::vec4 pos = (*mesh_vert_pos)[i];
        std::cout << "\n\t" << i << ": " << pos[0] << "," << pos[1] << "," << pos[2] << "," << pos[3];
    }
    std::cout << "\nmesh_vert_nor:";
    for(unsigned int i = 0; i < mesh_vert_nor->size(); i++) {
        glm::vec4 nor = (*mesh_vert_nor)[i];
        std::cout << "\n\t" << i << ": " << nor[0] << "," << nor[1] << "," << nor[2] << "," << nor[3];
    }
    std::cout << "\nmesh_vert_col:";
    for(unsigned int i = 0; i < mesh_vert_col->size(); i++) {
        glm::vec4 col = (*mesh_vert_col)[i];
        std::cout << "\n\t" << i << ": " << col[0] << "," << col[1] << "," << col[2] << "," << col[3];
    }

}

void Mesh::buildColorBuffer(std::vector<glm::vec4>& mesh_vert_col){
    for(unsigned int i = 0; i < faces.size(); i++) {
        glm::vec4 face_col = faces[i]->getColor();
        HalfEdge* start = faces[i]->getStartEdge();
        HalfEdge* current = start;

        current = current->getNext();
        current = current->getNext();

        mesh_vert_col.push_back(face_col);
        mesh_vert_col.push_back(face_col);
        mesh_vert_col.push_back(face_col);

        current = current->getNext();//one past first tri
        while(current != start) {
            mesh_vert_col.push_back(face_col);
            current = current->getNext();
        }
    }
}

void Mesh::updateColorVBO() {
    std::vector<glm::vec4> mesh_vert_col(0);
    buildColorBuffer(mesh_vert_col);
    context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    context->glBufferData(GL_ARRAY_BUFFER,
                          mesh_vert_col.size() * sizeof(glm::vec4), mesh_vert_col.data(), GL_STATIC_DRAW);
}

void Mesh::create() {
    std::vector<GLuint> mesh_idx(0);
    std::vector<glm::vec4> mesh_vert_pos(0);
    std::vector<glm::vec4> mesh_vert_nor(0);
    std::vector<glm::vec4> mesh_vert_col(0);

    buildBuffers(&mesh_idx, &mesh_vert_pos, &mesh_vert_nor, &mesh_vert_col);

#if DEBUG
    printBuffers(&mesh_idx, &mesh_vert_pos, &mesh_vert_nor, &mesh_vert_col);
#endif

    count = mesh_idx.size();


    generateIdx();
    context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                          mesh_idx.size() * sizeof(GLuint), mesh_idx.data(), GL_STATIC_DRAW);

    generatePos();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    context->glBufferData(GL_ARRAY_BUFFER,
                          mesh_vert_pos.size() * sizeof(glm::vec4), mesh_vert_pos.data(), GL_STATIC_DRAW);

    generateNor();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    context->glBufferData(GL_ARRAY_BUFFER, 
                          mesh_vert_nor.size() * sizeof(glm::vec4), mesh_vert_nor.data(), GL_STATIC_DRAW);

    generateCol();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    context->glBufferData(GL_ARRAY_BUFFER,
                          mesh_vert_col.size() * sizeof(glm::vec4), mesh_vert_col.data(), GL_STATIC_DRAW);
}
