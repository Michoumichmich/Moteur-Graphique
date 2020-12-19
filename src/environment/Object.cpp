#include <memory>
#include "Object.h"


std::shared_ptr<std::list<Tessel>> Object::getTessels(int resolution) {
    if (needToRecompute()) {
        tessels->clear();
        Tesselate(resolution);

        for (Tessel &aTessel : *tessels) {
            aTessel = CoordinatesHandler::fromLocalToGlobal(aTessel, anim_curr_transformation);
            aTessel = CoordinatesHandler::fromLocalToGlobal(aTessel, transformations);
            aTessel.properties = properties;
        }
        state_changed_since_last_tessel = false;
        anim_object_moved = false;
    }
    return tessels;
}

Object *Object::setTransformation(struct transformations transfo) {
    transformations = transfo;
    state_changed_since_last_tessel = true;
    return this;
}

Object *Object::setCenter(Point3D center) {
    state_changed_since_last_tessel = true;
    transformations.pt = center;
    return this;
}

Object *Object::setColor(Color color) {
    state_changed_since_last_tessel = true;
    properties.color = color;
    return this;
}

Object *Object::setLightIntensity(double intensity) {
    state_changed_since_last_tessel = true;
    properties.lightIntensity = intensity;
    return this;
}

Object *Object::setDiffusivity(double diffusivity) {
    state_changed_since_last_tessel = true;
    properties.diffusivity = diffusivity;
    return this;
}

Object *Object::setReflexivity(double reflexivity) {
    state_changed_since_last_tessel = true;
    properties.reflexivity = reflexivity;
    return this;
}

Object *Object::setRefractiveIndex(double index) {
    state_changed_since_last_tessel = true;
    properties.refractiveIndex = index;
    return this;
}

Object *Object::setTransparency(double transparency) {
    state_changed_since_last_tessel = true;
    properties.transparency = transparency;
    return this;
}

std::ostream &operator<<(std::ostream &out, Object &object) {
    return object.print(out);
}

bool Object::needToRecompute() {
    return state_changed_since_last_tessel || anim_object_moved;
}

void Object::setFrame(int frame) {
    if (!all_anim_disabled) {
        this->anim_set_frame_number(frame);
    }
}

Object *Object::disableAnimations() {
    all_anim_disabled = true;
    return this;
}

Object *Object::enableAnimations() {
    all_anim_disabled = false;
    return this;
}

Object::~Object() = default;
