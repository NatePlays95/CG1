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
    vector<unsigned int> uvIndices;
};

class Mesh : public Shape {
    public:
        std::string meshName = "noName";

        Mesh();
        Mesh( vector<Vec3*>& vertices_in,  vector<Vec3*>& normals_in, vector<Vec3*>& uvs_in, vector<Face>& faces_in);

        void printToConsole();
        bool intersect(Ray& raycast);

        // static Mesh loadFromFileObj(const std::string& fileName);
        void loadFromFileObj(const std::string& fileName);

        bool intersectFace(Face& face, Ray& raycast);

        void applyTransform(Mat4 transform);

        void printNormals();

    protected:
        vector<Vec3*> vertices;
        vector<Vec3*> normals;
        vector<Vec3*> uvs;
        vector<Face> faces;
};

#endif