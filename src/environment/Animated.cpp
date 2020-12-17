#include "Animated.h"

void Animated::add_keyframe(struct keyframe frame) {
    keyframes.emplace_back(frame);
}

bool Animated::update_current_transformation(int frame) {
    if (keyframes.empty()) {
        animator_current_transformation = {};
    } else {
        //TODO
    }
    return true;
}
