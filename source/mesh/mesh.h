#ifndef MESH_H
#define MESH_H

#include "../shape.h"
#include "../mat4.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// struct Vertex {
//     Vec3 position;
// };

// struct Normal {
//     double x, y, z;
// };

// struct FaceVertex {
//     unsigned int vertexIndex;
//     unsigned int normalIndex;
//     // double u; double v; //replace with UV coords
//     Vec3 textureCoords; 
// };


struct Face { //all faces should be triangulated
    vector<unsigned int> vertexIndices;
    vector<unsigned int> normalIndices;
};

class Mesh : public Shape {
    public:
        Mesh();
        Mesh( vector<Vec3*>& vertices_in,  vector<Vec3*>& vertexNormals_in,  vector<Face>& faces_in);
        bool intersect(Ray& raycast);

        static Mesh loadFromFileObj(const std::string& fileName);

    private:
        vector<Vec3*> vertices;
        vector<Vec3*> normals;
        vector<Face> faces;
};

#endif