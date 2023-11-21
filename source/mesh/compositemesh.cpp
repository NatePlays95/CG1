#include "compositemesh.h"

CompositeMesh::CompositeMesh() {
    meshes = {};
};

void CompositeMesh::addMesh(WrappedMesh* shape_in) {
    meshes.push_front(shape_in);
};

void CompositeMesh::applyTransform(Mat4 transform) {
    for (auto i : meshes) {
        i->applyTransform(transform);
    }
};

bool CompositeMesh::intersect(Ray& raycast) {
    bool result = false;
    for (auto i : meshes) {
        bool stepResult = i->intersect(raycast);
        if (!result) result = stepResult;
    }

    return result;
};