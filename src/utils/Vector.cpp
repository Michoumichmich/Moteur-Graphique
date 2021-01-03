#include "Vector.h"

void *malloc_simd(const size_t size) {
#if defined WIN32
    return _aligned_malloc(size, 16);
#elif defined __linux__
    return memalign(16, size);
#elif defined __MACH__
    return malloc(size);
#else // use page-aligned memory for other systems
    return _aligned_malloc(size, 16);
#endif
}

void free_simd(void *v) {
#if defined WIN32
    return _aligned_free(v);
#else
    return free(v);
#endif
}

std::ostream &operator<<(std::ostream &os, const Vector &v) {
    os << "Vector(" << v.x() << ", "
       << v.y() << ", "
       << v.z() << ")";
    return os;
}

