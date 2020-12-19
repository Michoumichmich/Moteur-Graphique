#include "Animated.h"

void Animated::add_keyframe(struct keyframe frame) {
    keyframes.emplace_back(frame);
}

void Animated::update_current_transformation(int frame) {
    if (test_shrink) {
        anim_curr_transformation.scale = frame;
        anim_object_moved = true;
    } else if (keyframes.empty()) {
        anim_object_moved = false;
        anim_curr_transformation = {};
    }
}

void Animated::anim_set_frame_number(int num) {
    this->current_frame_number = num;
    update_current_transformation(num);
}
