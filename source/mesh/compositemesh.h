#ifndef COMPOSITEMESH_H
#define COMPOSITEMESH_H

#include <list>
#include "../compositeshape.h"
#include "wrappedmesh.h"

class CompositeMesh : public Shape {
    public:
        std::list<WrappedMesh*> meshes;
        
        CompositeMesh();

        void addMesh(WrappedMesh* mesh);

        void applyTransform(Mat4 transform);
        bool intersect(Ray& raycast);
};

#endif