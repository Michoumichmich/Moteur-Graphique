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
    void update_current_transformation(int frame);

    std::list<struct keyframe> keyframes;
    bool use_interpolation = false;
    bool use_keyframes = true;
protected:
    int current_frame_number = 0;
    bool anim_object_moved = true;

public:
    struct transformations anim_curr_transformation;

    void anim_set_frame_number(int num);

    void add_keyframe(struct keyframe frame);

    bool test_spin = false;
};


#endif //GRAPHICSENGINE_ANIMATED_H
