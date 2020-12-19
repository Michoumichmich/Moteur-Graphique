#include "MeshObject.h"

/**
 * Returns the union of two unordered sets
 */
template<typename T>
void in_place_union(std::unordered_set<T> &a, const std::unordered_set<T> &b) {
    a.insert(b.begin(), b.end());
}


void MeshObject::add_mesh_tessel(std::array<size_t, 3> m_tessel) {
    this->all_mesh_tessels.emplace_back(m_tessel);
}

void MeshObject::Tesselate(int resolution) {
    update_nodes_position();

    for (const auto &triplets:all_mesh_tessels) {
        /* Converting the set into a vector */
        std::vector<MeshNode> output;
        tessels->emplace_back(all_nodes[triplets[0]].current_position, all_nodes[triplets[1]].current_position, all_nodes[triplets[2]].current_position);
    }
    std::cout << "tesselation called" << std::endl;
}

void MeshObject::update_nodes_position() {
    if (!all_anim_disabled) {
        for (auto &one_node : all_nodes) {
            one_node.anim_set_frame_number(this->current_frame_number);
            one_node.current_position = CoordinatesHandler::fromLocalToGlobal(one_node.original_position, one_node.anim_curr_transformation);
        }
    } else {
        for (auto &one_node : all_nodes) {
            one_node.current_position = one_node.original_position;
        }
    }
}


void MeshObject::setFrame(int frame) {
    if (!all_anim_disabled) {
        Object::setFrame(frame);
        this->anim_object_moved = true;
        for (auto &one_node : all_nodes) {
            one_node.anim_set_frame_number(this->current_frame_number);
        }
    }
}


void MeshObject::serialize(std::stringstream &stream) {}

void MeshObject::deserialize(std::istream &stream) {}

std::ostream &MeshObject::print(std::ostream &str) {
    return str << "Mesh object" << std::endl;
}