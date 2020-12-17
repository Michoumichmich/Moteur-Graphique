//
// Created by lilian on 17/12/2020.
//

#ifndef GRAPHICSENGINE_PYRAMID_H
#define GRAPHICSENGINE_PYRAMID_H

#include "../Object.h"

class Pyramid : public Object {
    private:
        double edge;
    public:
        explicit Pyramid(double size);

        void Tesselate(int resolution) override;

        void serialize(std::stringstream& stream) override;

        void deserialize(std::istream& stream) override;

        std::ostream& print(std::ostream& str) override;
};


#endif //GRAPHICSENGINE_PYRAMID_H