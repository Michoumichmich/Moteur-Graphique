#ifndef GRAPHIC_ENGINE_OBJECT_H
#define GRAPHIC_ENGINE_OBJECT_H

#include <list>
#include <utils.h>
#include <string>
#include "Tessel.h"
#include "ApparenceProperties.h"
#include "CoordinatesHandler.h"

/**
 * @class L'objet doit être crée autour ce son centre géométrique. Ie une sphère aura son centre en (0;0;0).
 * Lorsqu'on va appliquer la tesselation on va ensuite transformer tous les points pour passer du référentiel de l'objet au référentiel global de la scène.
 * D'abord l'homothétie "transfo.scale", puis les rotations et finalement ma translation.
 * C'est effectué par CoordinatesHandler::fromLocalToGlobal
 */
class Object {
protected:
    struct transformations tranfo;
    std::list<Tessel *> tessels;
    ApparenceProperties properties;
public:
    virtual void Tesselate();

    std::list<Tessel *> getTessels();

    std::string ObjectName;
};

#endif //GRAPHIC_ENGINE_OBJECT_H
