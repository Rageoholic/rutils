#ifndef RMATH_H
#define RMATH_H
#include "debug.h"
#include "def.h"
#include <float.h>
#include <math.h>
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062f
#ifdef __cplusplus
extern "C"
{
#endif
    /* All these math functions are kind of elementary so you'll excuse me for
       not documenting them in great detail */
    typedef struct Vec2f
    {
        float x, y;
    } Vec2f;
    typedef struct Vec3f
    {
        float x, y, z;
    } Vec3f;

    typedef struct Vec4f
    {
        float x, y, z, w;
    } Vec4f;

    typedef struct Mat4f
    {
        /* This is addressed mat.e[y][x]. Yes its stupid. We give you a function to
       work around it if you want. This is what I get for it having a convenient
       layout in memory */
        float e[4][4];
    } Mat4f;

    static inline Vec3f AddVec3f(Vec3f vec1, Vec3f vec2)
    {
        return (Vec3f){vec1.x + vec2.x,
                       vec1.y + vec2.y,
                       vec1.z + vec2.z};
    }

    static inline Vec2f AddVec2f(Vec2f vec1, Vec2f vec2)
    {
        return (Vec2f){vec1.x + vec2.x,
                       vec1.y + vec2.y};
    }

    static inline Vec3f MultiplyScalarVec3f(Vec3f vec, float f)
    {
        return (Vec3f){vec.x * f,
                       vec.y * f,
                       vec.z * f};
    }

    static inline Vec2f MultiplyScalarVec2f(Vec2f vec, float f)
    {
        return (Vec2f){vec.x * f,
                       vec.y * f};
    }

    static inline float DotProdVec3f(Vec3f a, Vec3f b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
    static inline float LengthVec3f(Vec3f vec)
    {
        return sqrtf(vec.x * vec.x +
                     vec.y * vec.y +
                     vec.z * vec.z);
    }
    static inline float *Index2dFloatArray(float *m, int width, int height, int x, int y)
    {
        assert(x < width && y < height);
        return m + y * width + x;
    }

    static inline float *IndexMat4f(Mat4f *mat, int x, int y)
    {
        return Index2dFloatArray((float *)mat->e, 4, 4, x, y);
    }

    Vec3f NormalizeVec3f(Vec3f vec);
    Vec2f NormalizeVec2f(Vec2f vec);

    static inline float AbsFloat(float f)
    {
        return f < 0 ? -f : f;
    }

    /* You must Translate, then Rotate, then Scale */
    Mat4f RotateMat4f(const Mat4f *mat, float rads, Vec3f vec);
    Mat4f ScaleMat4f(const Mat4f *mat, Vec3f vec);
    Mat4f TranslateMat4f(const Mat4f *mat, Vec3f vec);

    static Vec3f vec3f(float x, float y, float z)
    {
        return (Vec3f){x, y, z};
    }

    static Vec2f vec2f(float x, float y)
    {
        return (Vec2f){x, y};
    }

    static float DegToRad(float deg)
    {
        return deg / 180 * PI;
    }

    static const Mat4f IdMat4f = {{{1, 0, 0, 0},
                                   {0, 1, 0, 0},
                                   {0, 0, 1, 0},
                                   {0, 0, 0, 1}}};
    Mat4f MultiplyMat4f(const Mat4f *mat1, const Mat4f *mat2);

    int PrintVec3f(Vec3f vec);

    Mat4f CreatePerspectiveMat4f(float rads, float aspect, float near, float far);

    Mat4f CalcLookAtMat4f(Vec3f position, Vec3f target, Vec3f worldUp);

    static inline Vec3f NegateVec3f(Vec3f vec)
    {
        return (Vec3f){-vec.x,
                       -vec.y,
                       -vec.z};
    }
    static inline Vec3f SubVec3f(Vec3f v1, Vec3f v2)
    {
        return AddVec3f(v1, NegateVec3f(v2));
    }
    Vec3f CrossProductVec3f(Vec3f v1, Vec3f v2);
    Mat4f CreateOrthoMat4f(float left, float right, float bottom, float top);
#ifdef __cplusplus
}
#endif
#endif
