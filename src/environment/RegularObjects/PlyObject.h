#ifndef GRAPHICSENGINE_PLYOBJECT_H
#define GRAPHICSENGINE_PLYOBJECT_H

#include "../Object.h"

class PlyObject : public Object {

private:
    std::string source_file;
    std::vector<Tessel> constructed_tessels;
public:
    explicit PlyObject(std::string ply_file);

    void Tesselate(int resolution) override;

    void serialize(std::stringstream &stream) override;

    void deserialize(std::istream &stream) override;

    std::ostream &print(std::ostream &str) override;
};


#endif //GRAPHICSENGINE_PLYOBJECT_H
