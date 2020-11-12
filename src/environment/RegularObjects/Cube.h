//
// Created by lilian on 15/10/2020.
//

#ifndef GRAPHICSENGINE_CUBE_H
#define GRAPHICSENGINE_CUBE_H

#include "../Object.h"

class Cube : public Object {
private:
    double size;
public:
    explicit Cube(double size);

  void Tesselate(int resolution) override;

    void serialize(std::stringstream &stream) override;

    void deserialize(std::istream &stream) override;
};

#endif //GRAPHICSENGINE_CUBE_H
