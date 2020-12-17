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
};

/**
 * Tessel composed of mesh nodes
 */
struct MeshTessel {
    std::unordered_set<std::shared_ptr<MeshNode>> mesh_nodes{};
};

class MeshObject : public Object {
private:
    std::unordered_set<std::shared_ptr<struct MeshTessel>> meshed_tessels{};
    std::unordered_set<std::shared_ptr<MeshNode>> all_mesh_nodes{};

public:
    void add_mesh_tessel(std::shared_ptr<struct MeshTessel> m_tessel);


    void update_meshes_position(int frame);

    void Tesselate(int resolution) override;
};


#endif //GRAPHICSENGINE_MESHOBJECT_H
