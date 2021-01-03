#include "PlyObjectMesh.h"
#include "../utils/io/PlyParser.hpp"

#include <algorithm>

PlyObjectMesh::PlyObjectMesh(std::string ply_file) : source_file(ply_file) {
    happly::PLYData plyIn(source_file);

    std::vector<std::array<double, 3>> vPos = plyIn.getVertexPositions();
    std::vector<Point3D> nodes(vPos.begin(), vPos.end());
    float max_dist = std::max_element(nodes.begin(), nodes.end())->length();
    std::for_each(nodes.begin(), nodes.end(), [max_dist](Point3D &x) { x = x / max_dist; }); /* Normalizing the object */

    all_nodes = std::vector<MeshNode>(nodes.begin(), nodes.end());
    std::vector<std::vector<size_t>> fInd = plyIn.getFaceIndices<size_t>();
    all_mesh_tessels.reserve(fInd.size());
    for (auto &f : fInd) {
        if (f.size() == 3) {
            this->add_mesh_tessel({f[0], f[1], f[2]});
        }
    }

    std::cout << this->all_nodes.size() << std::endl;
    std::cout << this->all_mesh_tessels.size() << std::endl;
}