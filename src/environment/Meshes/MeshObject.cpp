#include "MeshObject.h"

template<typename T>
std::unordered_set<T> getUnion(const std::unordered_set<T> &a, const std::unordered_set<T> &b) {
    std::unordered_set<T> result = a;
    result.insert(b.begin(), b.end());
    return result;
}

void MeshObject::add_mesh_tessel(std::shared_ptr<struct MeshTessel> m_tessel) {
    if (!meshed_tessels.contains(m_tessel) && m_tessel->mesh_nodes.size() == 3) {
        meshed_tessels.insert(m_tessel);
        all_mesh_nodes = getUnion(m_tessel->mesh_nodes, all_mesh_nodes);
    }
}

void MeshObject::Tesselate(int resolution) {
    update_meshes_position(current_frame_numer);
    for (const std::shared_ptr<struct MeshTessel> &tessel:meshed_tessels) {
        std::vector<MeshNode> output;
        output.reserve(tessel->mesh_nodes.size());
        for (auto it = tessel->mesh_nodes.begin(); it != tessel->mesh_nodes.end();) {
            output.push_back(std::move(*tessel->mesh_nodes.extract(it++).value()));
        }
        tessels->emplace_back(output[0].current_position, output[1].current_position, output[2].current_position);
    }
}

void MeshObject::update_meshes_position(int frame) {
    for (std::shared_ptr<MeshNode> one_node : all_mesh_nodes) {
        one_node->update_current_transformation(frame);
        one_node->current_position = CoordinatesHandler::fromLocalToGlobal(one_node->original_position,
                                                                           one_node->animator_current_transformation);
    }
}
