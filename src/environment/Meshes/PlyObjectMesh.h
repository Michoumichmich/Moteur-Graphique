#ifndef GRAPHICSENGINE_PLYOBJECTMESH_H
#define GRAPHICSENGINE_PLYOBJECTMESH_H

#include "MeshObject.h"

class PlyObjectMesh : public MeshObject {

private:
    std::string source_file;
public:
    explicit PlyObjectMesh(std::string ply_file);
};


#endif //GRAPHICSENGINE_PLYOBJECT_H
