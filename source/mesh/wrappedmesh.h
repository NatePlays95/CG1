#ifndef WRAPPEDMESH_H
#define WRAPPEDMESH_H

#include "mesh.h"

class WrappedMesh : public Mesh {
    public:

        WrappedMesh();

        double boundsMinX = 1000, boundsMinY = 1000, boundsMinZ = 1000;
        double boundsMaxX = 1000, boundsMaxY = 1000, boundsMaxZ = 1000;

        double margin = 0.5;

        bool intersect(Ray& raycast);
        bool intersectBounds(Ray& raycast);

        void applyTransform(Mat4 transform);
        void recalculateBounds();
};

#endif