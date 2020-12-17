#ifndef GRAPHICSENGINE_ANIMATED_H
#define GRAPHICSENGINE_ANIMATED_H

#include "CoordinatesHandler.h"

struct keyframe {
    int frame_number;
    struct transformations transfo;
};

/**
 * @class Animated
 * Furnishes basic functions to add keyframes, remove, and get the current struct transformations related to the animation
 * in function of the number of the frame. Can use interpolation. Could also work with lambda functions that compute
 * the current struct in function of the frame number
 */
class Animated {
private:
    std::list<struct keyframe> keyframes;
    bool use_interpolation = false;
    bool use_keyframes = true;
public:
    struct transformations animator_current_transformation;

    void add_keyframe(struct keyframe frame);

    /**
     *
     * @param frame
     * @return bool that tells if the transformation is different from the previous one;
     */
    bool update_current_transformation(int frame);
};


#endif //GRAPHICSENGINE_ANIMATED_H
