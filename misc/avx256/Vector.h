#ifndef GRAPHIC_ENGINE_VECTOR_H
#define GRAPHIC_ENGINE_VECTOR_H

#pragma once
//#include <smmintrin.h>
#include <emmintrin.h>
#include<immintrin.h>
#include <iostream>
#include <cstdlib>

#if __APPLE__
# include <stdlib.h>
#else
# include <malloc.h>
#endif

#define _mm_extract_epi64(x, imm) _mm_cvtsi128_si64(_mm_srli_si128((x), 8 * (imm)))

// __m128 bits mask to target the doubleing point sign bit.
static const __m256d SIGNMASK = _mm256_castsi256_pd(_mm256_set1_epi64x(0x80000000));

/**
** 16-bytes aligned memory allocation function.
** \param size Size of the memory chunk to allocate in bytes.
** \return A pointer to the newly aligned memory, or nullptr.
*/
void *malloc_simd(const size_t size);

/**
** 16-bytes aligned memory free function.
** \param v Memory pointer to free, which must have been allocated using
** malloc_simd.
*/
void free_simd(void *v);


/**
** 3D doubleing-point precission mathematical vector class.
*/
#ifdef __GNUC__
class __attribute__((aligned (16))) Vector
#else
  _MM_ALIGN16 class Vector
#endif
{
 public:
  /// Constructors
  inline Vector() : mmvalue(_mm256_setzero_pd())
  {}
  inline Vector(double x, double y, double z) : mmvalue(_mm256_set_pd(0, z, y, x))
  {}
  inline Vector(__m256d m) : mmvalue(m)
  {}

  inline Vector(Vector vector1, Vector vector2) : Vector(vector2 - vector1)
  {};

/// Arithmetic operators with Vector3
  inline Vector operator+(const Vector &b) const
  { return _mm256_add_pd(mmvalue, b.mmvalue); }
  inline Vector operator-(const Vector &b) const
  { return _mm256_sub_pd(mmvalue, b.mmvalue); }
  inline Vector operator*(const Vector &b) const
  { return _mm256_mul_pd(mmvalue, b.mmvalue); }
  inline Vector operator/(const Vector &b) const
  { return _mm256_div_pd(mmvalue, b.mmvalue); }

  /// Assignation and arithmetic operators with Vector3
  inline Vector &operator+=(const Vector &b)
  {
    mmvalue = _mm256_add_pd(mmvalue, b.mmvalue);
    return *this;
  }
  inline Vector &operator-=(const Vector &b)
  {
    mmvalue = _mm256_sub_pd(mmvalue, b.mmvalue);
    return *this;
  }
  inline Vector &operator*=(const Vector &b)
  {
    mmvalue = _mm256_mul_pd(mmvalue, b.mmvalue);
    return *this;
  }
  inline Vector &operator/=(const Vector &b)
  {
    mmvalue = _mm256_div_pd(mmvalue, b.mmvalue);
    return *this;
  }

  /// Arithmetic operators with doubles
  inline Vector operator+(double b) const
  { return _mm256_add_pd(mmvalue, _mm256_set1_pd(b)); }
  inline Vector operator-(double b) const
  { return _mm256_sub_pd(mmvalue, _mm256_set1_pd(b)); }
  inline Vector operator*(double b) const
  { return _mm256_mul_pd(mmvalue, _mm256_set1_pd(b)); }
  inline Vector operator/(double b) const
  { return _mm256_div_pd(mmvalue, _mm256_set1_pd(b)); }

  /// Assignation and arithmetic operators with double
  inline Vector &operator+=(double b)
  {
    mmvalue = _mm256_add_pd(mmvalue, _mm256_set1_pd(b));
    return *this;
  }
  inline Vector &operator-=(double b)
  {
    mmvalue = _mm256_sub_pd(mmvalue, _mm256_set1_pd(b));
    return *this;
  }
  inline Vector &operator*=(double b)
  {
    mmvalue = _mm256_mul_pd(mmvalue, _mm256_set1_pd(b));
    return *this;
  }
  inline Vector &operator/=(double b)
  {
    mmvalue = _mm256_div_pd(mmvalue, _mm256_set1_pd(b));
    return *this;
  }

  /// Equality operators
  inline bool operator==(const Vector &b) const
  {
    return (((_mm256_movemask_pd(_mm256_cmp_pd(mmvalue, b.mmvalue, 0x0))) & 0x7) == 0x7);
  }
  inline bool operator!=(const Vector &b) const
  { return !(*this == b); }

  /// Unary minus operator
  inline Vector operator-() const
  { return _mm256_xor_pd(mmvalue, SIGNMASK); }

  /// Subscript operator
  // Note: there is not bound checking here.
  inline const double &operator[](const int i) const
  {
    return i == 0 ? this->x : (i == 1 ? this->y : this->z);
  }
  inline double &operator[](const int i)
  {
    return i == 0 ? this->x : (i == 1 ? this->y : this->z);
  }

  /// Cross product
  [[nodiscard]] inline Vector cross(const Vector &b) const
  {
    return _mm256_sub_pd(
        _mm256_mul_pd(_mm256_shuffle_pd(mmvalue, mmvalue, _MM_SHUFFLE(3, 0, 2, 1)), _mm256_shuffle_pd(b.mmvalue, b.mmvalue, _MM_SHUFFLE(3, 1, 0, 2))),
        _mm256_mul_pd(_mm256_shuffle_pd(mmvalue, mmvalue, _MM_SHUFFLE(3, 1, 0, 2)), _mm256_shuffle_pd(b.mmvalue, b.mmvalue, _MM_SHUFFLE(3, 0, 2, 1)))
    );
  }

  /// Dot product
  [[nodiscard]] inline double dot(const Vector &b) const
  {
    __m256d xy = _mm256_mul_pd(mmvalue, b.mmvalue);
    __m256d temp = _mm256_hadd_pd(xy, xy);
    __m128d hi128 = _mm256_extractf128_pd(temp, 1);
    __m128d lo128 = _mm256_extractf128_pd(temp, 0);
    __m128d dotproduct = _mm_add_pd(lo128, hi128);
    return _mm_cvtsd_f64(dotproduct);
  }
  /// Length of the vector
  [[nodiscard]] inline double length() const
  {
    __m256d xy = _mm256_mul_pd(mmvalue, mmvalue);
    __m256d temp = _mm256_hadd_pd(xy, xy);
    __m128d hi128 = _mm256_extractf128_pd(temp, 1);
    __m128d lo128 = _mm256_extractf128_pd(temp, 0);
    __m128d dotproduct = _mm_add_pd(lo128, hi128);
      return _mm256_cvtsd_f64(_mm256_sqrt_pd(_mm256_castpd128_pd256(dotproduct)));
  }
  /// Returns the normalized vector
  [[nodiscard]] inline Vector normalize() const
  {
    __m256d xy = _mm256_mul_pd(mmvalue, mmvalue);
    __m256d temp = _mm256_hadd_pd(xy, xy);
    __m128d hi128 = _mm256_extractf128_pd(temp, 1);
    __m128d lo128 = _mm256_extractf128_pd(temp, 0);
    __m128d dotproduct = _mm_add_pd(lo128, hi128);
    // multiplying by rsqrt does not yield an accurate enough result, so we
    // divide by sqrt instead.
    return _mm256_div_pd(mmvalue, _mm256_sqrt_pd(_mm256_castpd128_pd256(dotproduct)));
  }

  /// Overloaded operators that ensure alignment
  inline void *operator new[](size_t x)
  { return malloc_simd(x); }
  inline void operator delete[](void *x)
  { if (x) free_simd(x); }

  /// Textual representation
  friend std::ostream &operator<<(std::ostream &os, const Vector &t);

  /// Direct access member variables.
  union {
      struct {
          double x, y, z;
      };
      __m256d mmvalue;
  };
};

/**
** External operators that maps to the actual Vector3 method.
*/
inline Vector operator+(double a, const Vector &b)
{ return b + a; }
inline Vector operator-(double a, const Vector &b)
{ return Vector(_mm256_set1_pd(a)) - b; }
inline Vector operator*(double a, const Vector &b)
{ return b * a; }
inline Vector operator/(double a, const Vector &b)
{ return Vector(_mm256_set1_pd(a)) / b; }

typedef Vector Point3D;

#endif //GRAPHIC_ENGINE_VECTOR_H
