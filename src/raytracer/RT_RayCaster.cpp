#include "RT_RayCaster.h"

std::list<RT_Ray> RT_RayCaster::generateFirstRays(Camera *cam, OutputPictureManager *pic,double height,double width){
    std::list<RT_Ray> Rays;
    for(int i=0;i<width;i+=1/height){
        for(int j=0;j<width;j+=1/width){
            Rays.push_back(RT_Ray(Vector(cam->origin,cam->target),cam->origin,1 /*default counter ?*/,true));
        }
    }
    return Rays;
}
