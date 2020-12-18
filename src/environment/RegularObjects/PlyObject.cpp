#include "PlyObject.h"
#include "../utils/io/PlyParser.hpp"

PlyObject::PlyObject(std::string ply_file) : source_file(ply_file) {
    happly::PLYData plyIn(source_file);

    std::vector<std::array<double, 3>> vPos = plyIn.getVertexPositions();
    std::vector<std::array<unsigned char, 3>> colors = plyIn.getVertexColors();
    std::vector<std::vector<size_t>> fInd = plyIn.getFaceIndices<size_t>();
// Get data from the object
//    std::vector<float> elementA_prop1 = plyIn.getElement("elementA").getProperty<float>("prop1");
//    std::vector<std::vector<double>> elementB_listProp =
//            plyIn.getElement("elementB").getListProperty<double>("listprop1");

// Type promotion is automatic for numeric types: even if this property was stored as a float,
// we can access it as a double
//    std::vector<double> elementA_prop1_as_double =
//            plyIn.getElement("elementA").getProperty<double>("prop1");
}

void PlyObject::Tesselate(int resolution) {

}

void PlyObject::serialize(std::stringstream &stream) {

}

void PlyObject::deserialize(std::istream &stream) {

}

std::ostream &PlyObject::print(std::ostream &str) {
    return str << "Ply Object from file:" << source_file << std::endl;
}