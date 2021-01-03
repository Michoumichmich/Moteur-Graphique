#include "PlyObject.h"
#include "../utils/io/PlyParser.hpp"

#include <algorithm> 

PlyObject::PlyObject(std::string ply_file) : source_file(ply_file) {
    happly::PLYData plyIn(source_file);

    std::vector<std::array<double, 3>> vPos = plyIn.getVertexPositions();
    std::vector<Point3D> nodes(vPos.begin(), vPos.end());
    float max_dist = std::max_element(nodes.begin(), nodes.end())->length();
    std::for_each(nodes.begin(), nodes.end(), [max_dist](Point3D &x) { x = x / max_dist; }); /* Normalizing the object */

    std::vector<std::vector<size_t>> fInd = plyIn.getFaceIndices<size_t>();
    constructed_tessels = std::vector<Tessel>(fInd.size());

    for (auto &f : fInd) {
        if (f.size() == 3) constructed_tessels.emplace_back(nodes[f[0]], nodes[f[1]], nodes[f[2]]);
    }
}

void PlyObject::Tesselate(int resolution) {
    this->tessels->insert(this->tessels->end(), constructed_tessels.begin(), constructed_tessels.end());
}

void PlyObject::serialize(std::stringstream &stream) {

}

void PlyObject::deserialize(std::istream &stream) {

}

std::ostream &PlyObject::print(std::ostream &str) {
    return str << "Ply Object from file:" << source_file << std::endl;
}