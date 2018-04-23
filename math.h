#ifndef RMATH_H
#define RMATH_H

#include "debug.h"
#include "def.h"
#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062
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

static inline float *Index2dFloatArray(float *m, int width, int height, int x, int y)
{
    assert(x < width && y < height);
    return m + y * width + x;
}

static inline float *IndexMat4f(Mat4f *mat, int x, int y)
{
    return Index2dFloatArray((float *)mat->e, 4, 4, x, y);
}

static inline float AbsFloat(float f)
{
    return f < 0 ? -f : f;
}

Mat4f RotateMat4f(Mat4f mat, float rads, Vec3f vec);
Mat4f ScaleMat4f(Mat4f mat, Vec3f vec);
Mat4f TranslateMat4f(Mat4f mat, Vec3f vec);

static Vec3f vec3f(float x, float y, float z)
{
    return (Vec3f){x, y, z};
}

static float DegToRad(float deg)
{
    return deg / 180 * PI;
}

const static Mat4f IdMat4f = {{{1, 0, 0, 0},
                               {0, 1, 0, 0},
                               {0, 0, 1, 0},
                               {0, 0, 0, 1}}};
Mat4f MultiplyMatrices(Mat4f mat1, Mat4f mat2);

Mat4f CreatePerspectiveMat4f(float rads, float aspect, float near, float far);

#endif
