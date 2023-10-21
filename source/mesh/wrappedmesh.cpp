#include "wrappedmesh.h"

WrappedMesh::WrappedMesh(){};

bool WrappedMesh::intersect(Ray& raycast) {
    bool result = intersectBounds(raycast);
    if (result == true) {
        result = Mesh::intersect(raycast);
    }
    return result;
};

bool WrappedMesh::intersectBounds(Ray& raycast) {
    double txMin = (boundsMinX - raycast.position.x) / raycast.direction.x;
    double txMax = (boundsMaxX - raycast.position.x) / raycast.direction.x;
    if (txMax < txMin) { double tmp = txMax; txMax = txMin; txMin = tmp; }

    double tyMin = (boundsMinY - raycast.position.y) / raycast.direction.y;
    double tyMax = (boundsMaxY - raycast.position.y) / raycast.direction.y;
    if (tyMax < tyMin) { double tmp = tyMax; tyMax = tyMin; tyMin = tmp; }

    double tzMin = (boundsMinZ - raycast.position.z) / raycast.direction.z;
    double tzMax = (boundsMaxZ - raycast.position.z) / raycast.direction.z;
    if (tzMax < tzMin) { double tmp = tzMax; tzMax = tzMin; tzMin = tmp; }

    double tMin = (txMin > tyMin) ? txMin : tyMin;
    double tMax = (txMax < tyMax) ? txMax : tyMax;

    if (txMin > tyMax || tyMin > txMax) return false;
    if (tMin > tzMax || tzMin > tMax) return false;
    return true;

    // float tNear = max(max(t1.x, t1.y), t1.z);
    // float tFar = min(min(t2.x, t2.y), t2.z);
};

void WrappedMesh::applyTransform(Mat4 transform) {
    Mesh::applyTransform(transform);
    recalculateBounds();
};

void WrappedMesh::recalculateBounds() {
    if (vertices.size() < 1) return;
    //defaults
    Vec3 v = *(vertices[0]);
    boundsMinX = v.x; boundsMinY = v.y; boundsMinZ = v.z;
    boundsMaxX = v.x; boundsMaxY = v.y; boundsMaxZ = v.z;
    //checks
    for (auto vertex : vertices) {
        if (boundsMinX > vertex->x) boundsMinX = vertex->x;
        if (boundsMinY > vertex->y) boundsMinY = vertex->y;
        if (boundsMinZ > vertex->z) boundsMinZ = vertex->z;
        if (boundsMaxX < vertex->x) boundsMaxX = vertex->x;
        if (boundsMaxY < vertex->y) boundsMaxY = vertex->y;
        if (boundsMaxZ < vertex->z) boundsMaxZ = vertex->z;
    }
    boundsMinX -= margin; boundsMinY -= margin; boundsMinZ -= margin;
    boundsMaxX += margin; boundsMaxY += margin; boundsMaxZ += margin;
    return;
}
