#ifndef GRAPHIC_ENGINE_VECTOR_H
#define GRAPHIC_ENGINE_VECTOR_H

#pragma once

#include <smmintrin.h>
#include <iostream>
#include <cstdlib>

#if __APPLE__

# include <cstdlib>
#include <array>

#else

# include <malloc.h>
#include <array>

#endif

// __m128 bits mask to target the doubleing point sign bit.
static const __m128 SIGNMASK = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));

/**
** 16-bytes aligned memory allocation function.
** \param size Size of the memory chunk to allocate in bytes.
** \return A pointer to the newly aligned memory, or nullptr.
*/
void* malloc_simd(size_t size);

/**
** 16-bytes aligned memory free function.
** \param v Memory pointer to free, which must have been allocated using
** malloc_simd.
*/
void free_simd(void* v);

/**
** 3D doubleing-point precission mathematical vector class.
*/
class Vector {
public:
    /// Constructors
    inline Vector()
            :mmvalue(_mm_setzero_ps()) { }

    inline Vector(double x, double y, double z)
            :mmvalue(_mm_set_ps(0, static_cast<float>(z), static_cast<float>(y), static_cast<float>(x))) { }

    inline Vector(__m128 m)
            :mmvalue(m) { }

    inline Vector(Vector vector1, Vector vector2)
            :Vector(vector2-vector1) { };

    inline Vector(std::array<double, 3> v)
            :Vector(v[0], v[1], v[2]) { }

/// Arithmetic operators with Vector3
    inline Vector operator+(const Vector& b) const
    {
        return _mm_add_ps(mmvalue, b.mmvalue);
    }

    inline Vector operator-(const Vector& b) const
    {
        return _mm_sub_ps(mmvalue, b.mmvalue);
    }

    inline Vector operator*(const Vector& b) const
    {
        return _mm_mul_ps(mmvalue, b.mmvalue);
    }

    inline Vector operator/(const Vector& b) const
    {
        return _mm_div_ps(mmvalue, b.mmvalue);
    }

    /// Assignation and arithmetic operators with Vector3
    inline Vector& operator+=(const Vector& b)
    {
        mmvalue = _mm_add_ps(mmvalue, b.mmvalue);
        return *this;
    }

    inline Vector& operator-=(const Vector& b)
    {
        mmvalue = _mm_sub_ps(mmvalue, b.mmvalue);
        return *this;
    }

    inline Vector& operator*=(const Vector& b)
    {
        mmvalue = _mm_mul_ps(mmvalue, b.mmvalue);
        return *this;
    }

    inline Vector& operator/=(const Vector& b)
    {
        mmvalue = _mm_div_ps(mmvalue, b.mmvalue);
        return *this;
    }

    /// Arithmetic operators with doubles
    inline Vector operator+(float b) const
    {
        return _mm_add_ps(mmvalue, _mm_set1_ps(b));
    }

    inline Vector operator-(float b) const
    {
        return _mm_sub_ps(mmvalue, _mm_set1_ps(b));
    }

    inline Vector operator*(float b) const
    {
        return _mm_mul_ps(mmvalue, _mm_set1_ps(b));
    }

    inline Vector operator/(float b) const
    {
        return _mm_div_ps(mmvalue, _mm_set1_ps(b));
    }

    /// Assignation and arithmetic operators with float
    inline Vector& operator+=(float b)
    {
        mmvalue = _mm_add_ps(mmvalue, _mm_set1_ps(b));
        return *this;
    }

    inline Vector& operator-=(float b)
    {
        mmvalue = _mm_sub_ps(mmvalue, _mm_set1_ps(b));
        return *this;
    }

    inline Vector& operator*=(float b)
    {
        mmvalue = _mm_mul_ps(mmvalue, _mm_set1_ps(b));
        return *this;
    }

    inline Vector& operator/=(float b)
    {
        mmvalue = _mm_div_ps(mmvalue, _mm_set1_ps(b));
        return *this;
    }

    /// Equality operators
    inline bool operator==(const Vector& b) const
    {
        return (((_mm_movemask_ps(_mm_cmpeq_ps(mmvalue, b.mmvalue))) & 0x7)==0x7);
    }

    inline bool operator<(const Vector& a)
    {
        return this->length()<a.length();
    }

    inline bool operator!=(const Vector& b) const
    {
        return !(*this==b);
    }

    /// Unary minus operator
    inline Vector operator-() const { return _mm_xor_ps(mmvalue, SIGNMASK); }

    /// Subscript operator
    // Note: there is not bound checking here.
    inline const float& operator[](const int i) const
    {
        return i==0 ? this->p.x : (i==1 ? this->p.y : this->p.z);
    }

    inline float operator[](const int i)
    {
        return i==0 ? this->p.x : (i==1 ? this->p.y : this->p.z);
    }

    /// Cross product
    [[nodiscard]] inline Vector cross(const Vector& b) const
    {
        return _mm_sub_ps(
                _mm_mul_ps(_mm_shuffle_ps(mmvalue, mmvalue, _MM_SHUFFLE(3, 0, 2, 1)),
                        _mm_shuffle_ps(b.mmvalue, b.mmvalue, _MM_SHUFFLE(3, 1, 0, 2))),
                _mm_mul_ps(_mm_shuffle_ps(mmvalue, mmvalue, _MM_SHUFFLE(3, 1, 0, 2)),
                        _mm_shuffle_ps(b.mmvalue, b.mmvalue, _MM_SHUFFLE(3, 0, 2, 1)))
        );
    }

    /// Dot product
    [[nodiscard]] inline float dot(const Vector& b) const
    {
        return _mm_cvtss_f32(_mm_dp_ps(mmvalue, b.mmvalue, 0x71));
    }

    /// Length of the vector
    [[nodiscard]] inline float length() const
    {
        return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(mmvalue, mmvalue, 0x71)));
    }

    /// Returns the normalized vector
    [[nodiscard]] inline Vector normalize() const
    {
        // multiplying by rsqrt does not yield an accurate enough result, so we
        // divide by sqrt instead.
        return _mm_div_ps(mmvalue, _mm_sqrt_ps(_mm_dp_ps(mmvalue, mmvalue, 0xFF)));
    }

    /// Overloaded operators that ensure alignment
    inline void* operator new[](size_t x)
    {
        return malloc_simd(x);
    }

    inline void operator delete[](void* x)
    {
        if (x) free_simd(x);
    }

    /// Textual representation
    friend std::ostream& operator<<(std::ostream& os, const Vector& t);

    /// Direct access member variables.

    struct pts {
      float x, y, z;
    };

    [[nodiscard]] inline float& x() { return p.x; }

    [[nodiscard]] inline float& y() { return p.y; }

    [[nodiscard]] inline float& z() { return p.z; }

    [[nodiscard]] inline float x() const { return p.x; }

    [[nodiscard]] inline float y() const { return p.y; }

    [[nodiscard]] inline float z() const { return p.z; }

    union {
      struct pts p;
      __m128 mmvalue;
    };
}__attribute__((aligned (16)));

/**
** External operators that maps to the actual Vector3 method.
*/
inline Vector operator+(float a, const Vector& b)
{
    return b+a;
}

inline Vector operator-(float a, const Vector& b)
{
    return Vector(_mm_set1_ps(a))-b;
}

inline Vector operator*(float a, const Vector& b)
{
    return b*a;
}

inline Vector operator/(float a, const Vector& b)
{
    return Vector(_mm_set1_ps(a))/b;
}

typedef Vector Point3D;

#endif //GRAPHIC_ENGINE_VECTOR_H
