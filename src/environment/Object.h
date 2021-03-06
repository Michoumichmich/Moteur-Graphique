#ifndef GRAPHIC_ENGINE_OBJECT_H
#define GRAPHIC_ENGINE_OBJECT_H

#include <list>
#include <string>
#include <memory>

#include <utils.h>
#include "Tessel.h"
#include "ApparenceProperties.h"
#include "CoordinatesHandler.h"
#include "Animated.h"

/**
 * @class L'objet doit être crée autour ce son centre géométrique. Ie une sphère aura son centre en (0;0;0).
 * Lorsqu'on va appliquer la tesselation on va ensuite transformer tous les points pour passer du référentiel de l'objet au référentiel global de la scène.
 * D'abord l'homothétie "transfo.scale", puis les rotations et finalement ma translation.
 * C'est effectué par CoordinatesHandler::fromLocalToGlobal
 */
class Object : public Serializable, public Animated {
protected:
    struct transformations transformations{};
    std::shared_ptr<std::list<Tessel>> tessels = std::make_shared<std::list<Tessel>>();
    ApparenceProperties properties;
    bool state_changed_since_last_tessel = true;

    virtual void Tesselate(int resolution) = 0;

    bool all_anim_disabled = false;

    bool needToRecompute();

public:
    std::string ObjectName;


    /**
     * Computes if needed the tessels and if needed moves them in the environment
     * Also passes a copt of ApparenceProperties to child tessels
     * @return
     */
    std::shared_ptr<std::list<Tessel>> getTessels(int resolution);

    virtual void setFrame(int frame);

    Object *setTransformation(struct transformations);

    Object *setCenter(Point3D);

    Object *setColor(Color color);

    Object *disableAnimations();

    Object *setTransparency(double transparency);

    Object *setRefractiveIndex(double index);

    Object *setReflexivity(double reflexivity);

    Object *setDiffusivity(double diffusivity);

    Object *setLightIntensity(double intensity);

    virtual std::ostream &print(std::ostream &str) = 0;

    friend std::ostream &operator<<(std::ostream &, Object &);

    ~Object() override;

    Object *enableAnimations();
};

#endif //GRAPHIC_ENGINE_OBJECT_H
