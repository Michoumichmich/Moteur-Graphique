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

#define DEFAULT_WIDTH 1000
#define DEFAULT_HEIGHT 1000

#endif //INC_3D_RENDERER_CONFIG_H
