#include "mesh.h"
using namespace std;

Mesh::Mesh() {}

// Mesh::Mesh(const std::vector<Vertex>& vertices_in, const std::vector<Edge>& edges_in, const std::vector<Face>& faces_in) {

// }

bool Mesh::intersect(Ray& raycast) {
    return false;
}

Mesh::Mesh(vector<Vec3*>& vertices_in, vector<Vec3*>& vertexNormals_in, vector<Face>& faces_in) {
    vertices = vertices_in;
    normals = vertexNormals_in;
    faces = faces_in;
};

// Mesh Mesh::loadFromFileObj(const std::string& fileName) {
//     return Mesh();
// };


Mesh Mesh::loadFromFileObj(const std::string& fileName) {
    // Mesh mesh;
    std::ifstream objFile("assets/models/" + fileName + ".obj");

    if (!objFile.is_open()) {
        cerr << "Error: Unable to open .obj file." << endl;
        return Mesh();  // Return an empty mesh in case of an error.
    }

    vector<Vec3*> vertices_in;
    vector<Vec3*> normals_in;
    // vector<Edge> edges_in;
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
            cout << line.substr(1) << endl;
            double x, y, z;
            iss >> x >> y >> z;
            // Vertex vertex;
            Vec3* vertex = new Vec3(x,y,z);
            vertices_in.push_back(vertex);
        }
        else if (line.substr(0, 3) == "vn ") { // Parse vertex normal line
            istringstream iss(line.substr(2));
            cout << line.substr(2) << endl;
            double x, y, z;
            iss >> x >> y >> z;
            // Vec3 n = Vec3(x,y,z);
            // Normal n;
            // n.x = x; n.y = y; n.z = z;
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
                        // } else if (loopCount == 1) {
                            // indexStream >> faceVertex.texCoordIndex;
                        } else if (loopCount == 2) {
                            indexStream >> normalIndex;
                        }
                        loopCount++;
                    }
                }
                face.vertexIndices.push_back(vertexIndex);
                face.normalIndices.push_back(normalIndex);
            }
            faces_in.push_back(face);
        }
        // else if (line.substr(0, 3) == "vn ") { // Parse vertex normal line
        //     // Extract the normal's x, y, and z values
        //     // Store the normal in your mesh's normals array
        // }
        // else if (line.substr(0, 3) == "vt ") { // Parse texture coordinate line
        //     // Extract the u and v values
        //     // Store the texture coordinate in your mesh's texture coordinates array
        // }
        // if (line.substr(0, 2) == "o ") {
        //     // Start parsing a new object or group
        //     // Create a new Mesh object or group in your data structure
        // }
        continue;
    }
    objFile.close();

    Mesh mesh = Mesh(vertices_in, normals_in, faces_in);
    return mesh;
};