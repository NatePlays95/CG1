#include "mesh.h"
using namespace std;

Mesh::Mesh() {}

// Mesh::Mesh(const std::vector<Vertex>& vertices_in, const std::vector<Edge>& edges_in, const std::vector<Face>& faces_in) {

// }

Mesh::Mesh(vector<Vec3*>& vertices_in, vector<Vec3*>& normals_in, vector<Vec3*>& uvs_in, vector<Face>& faces_in) {
    vertices = vertices_in;
    normals = normals_in;
    uvs = uvs_in;
    faces = faces_in;
};

bool Mesh::intersect(Ray& raycast) {
    bool result = false;
    for (auto face : faces) {
        result = intersectFace(face, raycast) || result;
    }
    return result;
};

bool Mesh::intersectFace(Face& face, Ray& raycast) {
    Vec3 p1 = *(vertices[face.vertexIndices[0]]);
    Vec3 p2 = *(vertices[face.vertexIndices[1]]);
    Vec3 p3 = *(vertices[face.vertexIndices[2]]);
    Vec3 r1 = p2 - p1; Vec3 r2 = p3 - p1;

    //plane normal vector (not final normal vector)
    Vec3 plane_normal = r1.cross(r2).normalized();
    double t = - ((raycast.position - p1).dot(plane_normal)) / (raycast.direction.dot(plane_normal));

    //otimization: return early
    if (t < 0) return false;
    if (t > raycast.t) return false;

    Vec3 pContact = raycast.position + raycast.direction*t;
    Vec3 v = pContact - p1;
    Vec3 r2CrossN = r2.cross(plane_normal);
    Vec3 nCrossR1 = plane_normal.cross(r1);
    Vec3 w1 = (r2CrossN) / (r1.dot(r2CrossN));
    Vec3 w2 = (nCrossR1) / (r2.dot(nCrossR1));
    // baricentric coords
    double denominator = (r1.cross(r2)).dot(plane_normal);
    double c1 = ((p3 - pContact).cross(p1 - pContact)).dot(plane_normal) / denominator;
    double c2 = ((p1 - pContact).cross(p2 - pContact)).dot(plane_normal) / denominator;
    double c3 = ((p2 - pContact).cross(p3 - pContact)).dot(plane_normal) / denominator;

    if (c1 < 0 || c2 < 0 || c3 < 0) return false; // outside the triangle

    //interpolate uv coords
    //TODO: also interpolate vector normals
    Vec3 vt1 = *(uvs[face.uvIndices[0]]);
    Vec3 vt2 = *(uvs[face.uvIndices[1]]);
    Vec3 vt3 = *(uvs[face.uvIndices[2]]);
    Vec3 uv = vt1*c3 + vt2*c1 + vt3*c2;
    

    Vec3 normal = plane_normal; //TODO: interpolate normals
    return raycast.updateT(t, normal, material, uv);
};

void Mesh::applyTransform(Mat4 transform) {
    vector<Vec3*> new_vertices;
    for (auto vertex : vertices) {
        Vec4 vec4 = Vec4(*vertex, 1);
        new_vertices.push_back(new Vec3((transform * vec4).to3()));
    }
    int a = 1;
    // delete vertices;
    vertices = new_vertices;
};

// Mesh Mesh::loadFromFileObj(const std::string& fileName) {
//     // Mesh mesh;
//     std::ifstream objFile("assets/models/" + fileName + ".obj");

//     if (!objFile.is_open()) {
//         cerr << "Error: Unable to open .obj file." << endl;
//         return Mesh();  // Return an empty mesh in case of an error.
//     }

//     vector<Vec3*> vertices_in;
//     vector<Vec3*> normals_in;
//     // vector<Edge> edges_in;
//     vector<Face> faces_in;

//     string line;
//     while (getline(objFile, line)) {
//         // Parse the line and populate the mesh data structures.
//         // For example, extract vertex positions and face definitions.
//         if (line[0] == '#') {
//             // Ignore comments
//             continue;
//         }
//         if (line.substr(0, 2) == "v ") { // Parse vertex position line
//             istringstream iss(line.substr(1));
//             cout << line.substr(1) << endl;
//             double x, y, z;
//             iss >> x >> y >> z;
//             // Vertex vertex;
//             Vec3* vertex = new Vec3(x,y,z);
//             vertices_in.push_back(vertex);
//         }
//         else if (line.substr(0, 3) == "vn ") { // Parse vertex normal line
//             istringstream iss(line.substr(2));
//             cout << line.substr(2) << endl;
//             double x, y, z;
//             iss >> x >> y >> z;
//             // Vec3 n = Vec3(x,y,z);
//             // Normal n;
//             // n.x = x; n.y = y; n.z = z;
//             Vec3* normal = new Vec3(x,y,z);
//             normals_in.push_back(normal);
//         }
//         if (line.substr(0, 2) == "f ") { // Parse face line
//             istringstream iss(line.substr(1));
//             Face face; // Edge e1, e2, e3;

//             string vertexPart;
//             while (iss >> vertexPart) {
//                 istringstream vertexStream(vertexPart);
//                 string vertexInfo;
//                 // FaceVertex faceVertex;
//                 unsigned int vertexIndex;
//                 unsigned int normalIndex;

//                 int loopCount = 0;
//                 while (getline(vertexStream, vertexInfo, '/')) {
//                     if (vertexInfo.empty()) {
//                         // Handle cases where some indices are missing
//                         vertexIndex = -1;
//                         // faceVertex.textureCoords = -1;
//                         normalIndex = -1;
//                     } else {
//                         // Parse vertex index, texture coordinate index, and normal index
//                         istringstream indexStream(vertexInfo);
//                         if (loopCount == 0) {
//                             indexStream >> vertexIndex;
//                         // } else if (loopCount == 1) {
//                             // indexStream >> faceVertex.texCoordIndex;
//                         } else if (loopCount == 2) {
//                             indexStream >> normalIndex;
//                         }
//                         loopCount++;
//                     }
//                 }
//                 face.vertexIndices.push_back(vertexIndex);
//                 face.normalIndices.push_back(normalIndex);
//             }
//             faces_in.push_back(face);
//         }
//         // else if (line.substr(0, 3) == "vn ") { // Parse vertex normal line
//         //     // Extract the normal's x, y, and z values
//         //     // Store the normal in your mesh's normals array
//         // }
//         // else if (line.substr(0, 3) == "vt ") { // Parse texture coordinate line
//         //     // Extract the u and v values
//         //     // Store the texture coordinate in your mesh's texture coordinates array
//         // }
//         // if (line.substr(0, 2) == "o ") {
//         //     // Start parsing a new object or group
//         //     // Create a new Mesh object or group in your data structure
//         // }
//         continue;
//     }
//     objFile.close();

//     Mesh mesh = Mesh(vertices_in, normals_in, faces_in);
//     return mesh;
// };

//remember, indices are 1-indexed.
void Mesh::loadFromFileObj(const std::string& fileName) {
    // Mesh mesh;
    std::ifstream objFile("assets/models/" + fileName + ".obj");

    if (!objFile.is_open()) {
        cerr << "Error: Unable to open .obj file." << endl;
        return;// Mesh();  // Return an empty mesh in case of an error.
    }

    vector<Vec3*> vertices_in;
    vector<Vec3*> normals_in;
    vector<Vec3*> uvs_in;
    vector<Face> faces_in;

    string line;
    while (getline(objFile, line)) {
        // Parse the line and populate the mesh data structures.
        // For example, extract vertex positions and face definitions.
        if (line[0] == '#') {
            // Ignore comments
            continue;
        }
        if (line.substr(0, 2) == "v ") { // Parse vertex position line
            istringstream iss(line.substr(1));
            // cout << line.substr(1) << endl;
            double x, y, z;
            iss >> x >> y >> z;
            // Vertex vertex;
            Vec3* vertex = new Vec3(x,y,z);
            vertices_in.push_back(vertex);
        }
        else if (line.substr(0, 3) == "vt ") { // Parse texture coordinate line
            istringstream iss(line.substr(2));
            double u, v;
            iss >> u >> v;
            // Vertex vertex;
            Vec3* uv = new Vec3(u, v, 0);
            uvs_in.push_back(uv);
        }
        else if (line.substr(0, 3) == "vn ") { // Parse vertex normal line
            istringstream iss(line.substr(2));
            // cout << line.substr(2) << endl;
            double x, y, z;
            iss >> x >> y >> z;
            Vec3* normal = new Vec3(x,y,z);
            normals_in.push_back(normal);
        }
        if (line.substr(0, 2) == "f ") { // Parse face line
            istringstream iss(line.substr(1));
            Face face; // Edge e1, e2, e3;

            string vertexPart;
            while (iss >> vertexPart) {
                istringstream vertexStream(vertexPart);
                string vertexInfo;
                // FaceVertex faceVertex;
                unsigned int vertexIndex;
                unsigned int normalIndex;
                unsigned int uvIndex;

                int loopCount = 0;
                while (getline(vertexStream, vertexInfo, '/')) {
                    if (vertexInfo.empty()) {
                        // Handle cases where some indices are missing
                        vertexIndex = -1;
                        // faceVertex.textureCoords = -1;
                        normalIndex = -1;
                    } else {
                        // Parse vertex index, texture coordinate index, and normal index
                        istringstream indexStream(vertexInfo);
                        if (loopCount == 0) {
                            indexStream >> vertexIndex;
                        } else if (loopCount == 1) {
                            indexStream >> uvIndex;
                        } else if (loopCount == 2) {
                            indexStream >> normalIndex;
                        }
                        loopCount++;
                    }
                }
                face.vertexIndices.push_back(vertexIndex-1);
                face.normalIndices.push_back(normalIndex-1);
                face.uvIndices.push_back(uvIndex-1);
            }
            faces_in.push_back(face);
        }
        continue;
    }
    objFile.close();

    vertices = vertices_in;
    normals = normals_in;
    uvs = uvs_in;
    faces = faces_in;
    return;
};