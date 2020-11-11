#ifndef BUSINESS_CARD_DEMO_CPP_LIGHT_H
#define BUSINESS_CARD_DEMO_CPP_LIGHT_H

#include "utils.h"

class Light {
    public:
        Light(Vector p, double intensity);
        Vector position;
        double intensity;
};


#endif //BUSINESS_CARD_DEMO_CPP_LIGHT_H
