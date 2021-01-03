#ifndef CONFIG_H
#define CONFIG_H

#ifdef __GNUC__
/**
 * Tells the branch predictor that it is very likely that the condition is true
 * Wether it does something or not is implementation dependant.
 */
//#define likely(x)       __builtin_expect((x),1)

/**
 * Tells the branch predictor that the condition is very unlikely false.
 */
//#define unlikely(x)     __builtin_expect((x),0)
#else
#define likely(x) (x)
#define unlikely(x) (x)
#endif


/**
 * Coloring mode NONSENSE or LINEAR
 */

#include <cmath>
const double PI = std::atan(1.0) * 4;

constexpr auto MAX_BOUNCES = 2;
constexpr auto DEFAULT_WIDTH = 2001;
constexpr auto DEFAULT_HEIGHT = 1001;

constexpr auto MIN_RAY_LENGTH = 0.0001;

#endif //INC_3D_RENDERER_CONFIG_H
