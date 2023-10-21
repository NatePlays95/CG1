#ifndef WRAPPEDMESH_H
#define WRAPPEDMESH_H

#include "mesh.h"

class WrappedMesh : public Mesh {
    public:

        WrappedMesh();

        double boundsMinX = -100000, boundsMinY = -100000, boundsMinZ = -100000;
        double boundsMaxX = 100000, boundsMaxY = 100000, boundsMaxZ = 100000;

        double margin = 0.5;

        bool intersect(Ray& raycast);
        bool intersectBounds(Ray& raycast);

        void applyTransform(Mat4 transform);
        void recalculateBounds();
};

#endif