#ifndef CONFIG_H
#define CONFIG_H

/**
 * Tells the branch predictor that it is very likely that the condition is true
 * Wether it does something or not is implementation dependant.
 */
#define likely(x)       __builtin_expect((x),1)

/**
 * Tells the branch predictor that the condition is very unlikely false.
 */
#define unlikely(x)     __builtin_expect((x),0)

#define PI 3.1415926
#define TESSELATION_DENSITY 20
#define MAX_BOUNCES 1
#define DEFAULT_WIDTH 400
#define DEFAULT_HEIGHT 200

#endif //INC_3D_RENDERER_CONFIG_H
