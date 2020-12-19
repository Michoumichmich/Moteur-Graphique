#ifndef GRAPHICSENGINE_MESHOBJECT_H
#define GRAPHICSENGINE_MESHOBJECT_H

#include <utils.h>
#include <memory>
#include <unordered_set>
#include "../Tessel.h"
#include "../CoordinatesHandler.h"
#include "../Object.h"
#include "../Animated.h"

/**
 * Corresponds to one node of the mesh that can be shared between a lot of tessels
 */
class MeshNode : public Animated {
public:
    Point3D original_position;
    Point3D current_position;

    class MeshObject *parent = nullptr;

    MeshNode(Point3D pt) : original_position(pt), current_position(pt) {}

    MeshNode(Point3D pt, class MeshObject *par) : MeshNode(pt) { this->parent = par; }
};

/**
 * Tessel composed of mesh nodes
 */
struct MeshTessel {
    std::array<MeshNode, 3> nodes;
};

class MeshObject : public Object {
protected:
    std::vector<std::array<size_t, 3>> all_mesh_tessels;
    std::vector<MeshNode> all_nodes;

public:
    /**
     * Adds a mesh tessel in the environment. Checks wether the nodes are already presend in all_mesh_nodes
     * @param m_tessel
     */
    void add_mesh_tessel(std::array<size_t, 3> m_tessel);

    void update_nodes_position();

    void Tesselate(int resolution) override;

    void serialize(std::stringstream &stream) override;

    void deserialize(std::istream &stream) override;

    void setFrame(int frame) override;

    std::ostream &print(std::ostream &str) override;
};


#endif //GRAPHICSENGINE_MESHOBJECT_H
