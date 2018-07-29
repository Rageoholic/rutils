#include "math.h"
#include <math.h>

int PrintVec3f(Vec3f vec)
{
    return printf("{ x: %f, y: %f, z: %f }", vec.x, vec.y, vec.z);
}

Vec3f NormalizeVec3f(Vec3f vec)
{
    float len = sqrtf(vec.x * vec.x +
                      vec.y * vec.y +
                      vec.z * vec.z);

    Vec3f normalizedVec = {vec.x / len,
                           vec.y / len,
                           vec.z / len};
    return normalizedVec;
}

Mat4f MultiplyMatrices(const Mat4f *mat1, const Mat4f *mat2)
{
    /* TODO: SIMD operations as opposed to a ton of iteration */
    Mat4f ret = {0};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            float res = 0;
            for (int k = 0; k < 4; k++)
            {
                res += mat2->e[i][k] * mat1->e[k][j];
            }
            ret.e[i][j] = res;
        }
    }
    return ret;
}

Mat4f CreatePerspectiveMat4f(float fov, float aspect, float near, float far)
{
    assert(fov > 0 && aspect != 0);

    float xScale = (float)1 / tanf(fov / 2) / aspect;
    float yScale = xScale * aspect;
    float frustumLength = far - near;
    Mat4f result = {0};
    *IndexMat4f(&result, 0, 0) = xScale;
    *IndexMat4f(&result, 1, 1) = yScale;
    *IndexMat4f(&result, 2, 2) = -((far + near) / frustumLength);
    *IndexMat4f(&result, 3, 2) = -1;
    *IndexMat4f(&result, 2, 3) = -((2 * near * far) / frustumLength);
    *IndexMat4f(&result, 3, 3) = 0;

    return result;
}

Mat4f RotateMat4f(const Mat4f *mat, float rads, Vec3f axis)
{
    Vec3f normalAxis = NormalizeVec3f(axis);
    float x = normalAxis.x;
    float y = normalAxis.y;
    float z = normalAxis.z;
    float xx = normalAxis.x * normalAxis.x;
    float xy = normalAxis.x * normalAxis.y;
    float xz = normalAxis.x * normalAxis.z;
    float yy = normalAxis.y * normalAxis.y;
    float yz = normalAxis.y * normalAxis.z;
    float zz = normalAxis.z * normalAxis.z;
    float cost = cosf(rads);
    float sint = sinf(rads);
    /* TODO: make this not ugly as sin */
    Mat4f rotationMatrix =
        {{{cost + xx * (1 - cost), xy * (1 - cost) - z * sint,
           xz * (1 - cost) + y * sint, 0},
          {xy * (1 - cost) + z * sint, cost + yy * (1 - cost),
           yz * (1 - cost) - z * sint, 0},
          {xz * (1 - cost) - y * sint, yz * (1 - cost) + x * sint,
           cost + zz * (1 - cost), 0},
          {0, 0, 0, 1}}};
    return MultiplyMatrices(mat, &rotationMatrix);
}

Mat4f ScaleMat4f(const Mat4f *mat, Vec3f vec)
{
    Mat4f res = IdMat4f;
    *IndexMat4f(&res, 0, 0) *= vec.x;
    *IndexMat4f(&res, 1, 1) *= vec.y;
    *IndexMat4f(&res, 2, 2) *= vec.z;
    return MultiplyMatrices(mat, &res);
}

Mat4f TranslateMat4f(const Mat4f *mat, Vec3f vec)
{
    Mat4f res = *mat;
    *IndexMat4f(&res, 0, 3) += vec.x;
    *IndexMat4f(&res, 1, 3) += vec.y;
    *IndexMat4f(&res, 2, 3) += vec.z;

    return MultiplyMatrices(mat, &res);
}
