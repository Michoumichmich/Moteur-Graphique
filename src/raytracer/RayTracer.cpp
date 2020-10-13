#include "RayTracer.h"

#include <utils.h>
#include "RT_Ray.h"
#include "RT_RayCaster.h"

void RayTracer::renderScene()
{
  std::list<RT_Ray> firstRays = RT_RayCaster::generateFirstRays(environment->getCurrentCam());
  std::list<RT_Ray>::iterator aRay;
  for (aRay = firstRays.begin(); aRay != firstRays.end(); aRay++)
    {
      /**
       * Here some multithreading could be useful
       */
      aRay->RT_ComputeRay(envIntersector, picManager);
    }
}

RayTracer::RayTracer(Environment *env, OutputPictureManager *pic)
{
  this->picManager = pic;
  this->envIntersector = new RT_RayEnvIntersector(env);
}
RayTracer::RayTracer(Environment *env, OutputPictureManager *pic, struct rayTracerConfig conf) : config(conf)
{
  this->envIntersector = new RT_RayEnvIntersector(env);
  this->picManager = pic;
}
