#include "math.h"
#include <math.h>
#include <stdio.h>

int PrintVec3f(Vec3f vec)
{
    return printf("{ x: %f, y: %f, z: %f }", (double)vec.x, (double)vec.y, (double)vec.z);
}

Vec3f NormalizeVec3f(Vec3f vec)
{
    float len = sqrtf(vec.x * vec.x +
                      vec.y * vec.y +
                      vec.z * vec.z);
    
    if(F32Eq(len, 0.0f, FLT_EPSILON))
    {
	return (Vec3f) {0,0,0};
    }

    Vec3f normalizedVec = {vec.x / len,
                           vec.y / len,
                           vec.z / len};
    return normalizedVec;
}

Vec2f NormalizeVec2f(Vec2f vec)
{
    float len = sqrtf(vec.x * vec.x +
                      vec.y * vec.y);

    if(F32Eq(len, 0.0f, FLT_EPSILON))
    {
	return (Vec2f) {0,0};
    }


    Vec2f normalizedVec = {vec.x / len,
                           vec.y / len};

    return normalizedVec;
}

Mat4f MultiplyMat4f(const Mat4f *mat1, const Mat4f *mat2)
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
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"
    /* We turn off this warning because we're just looking for literal zero */
    assert(fov > 0 && aspect != 0);
#pragma clang diagnostic pop
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

Mat4f CreateOrthoMat4f(float left, float right, float bottom, float top)
{
    Mat4f result = IdMat4f;
    *IndexMat4f(&result, 0, 0) = 2 / (right - left);
    *IndexMat4f(&result, 1, 1) = 2 / (top - bottom);
    *IndexMat4f(&result, 2, 2) = -1;
    *IndexMat4f(&result, 0, 3) = -(right + left) / (right - left);
    *IndexMat4f(&result, 1, 3) = -(top + bottom) / (top - bottom);
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
           yz * (1 - cost) - x * sint, 0},
          {xz * (1 - cost) - y * sint, yz * (1 - cost) + x * sint,
           cost + zz * (1 - cost), 0},
          {0, 0, 0, 1}}};
    return MultiplyMat4f(mat, &rotationMatrix);
}

Mat4f ScaleMat4f(const Mat4f *mat, Vec3f vec)
{
    Mat4f res = IdMat4f;
    *IndexMat4f(&res, 0, 0) *= vec.x;
    *IndexMat4f(&res, 1, 1) *= vec.y;
    *IndexMat4f(&res, 2, 2) *= vec.z;
    return MultiplyMat4f(mat, &res);
}

Mat4f TranslateMat4f(const Mat4f *mat, Vec3f vec)
{
    Mat4f res = *mat;
    *IndexMat4f(&res, 0, 3) += vec.x;
    *IndexMat4f(&res, 1, 3) += vec.y;
    *IndexMat4f(&res, 2, 3) += vec.z;

    return MultiplyMat4f(mat, &res);
}

Vec3f CrossProductVec3f(Vec3f v1, Vec3f v2)
{
    return (Vec3f){
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x};
}

Mat4f CalcLookAtMat4f(Vec3f position, Vec3f target, Vec3f worldUp)
{
    // 1. Position = known
    // 2. Calculate cameraDirection
    Vec3f zaxis = NormalizeVec3f((Vec3f){
        position.x - target.x,
        position.y - target.y,
        position.z - target.z});
    // 3. Get positive right axis vector
    Vec3f xaxis = NormalizeVec3f(CrossProductVec3f(NormalizeVec3f(worldUp),
                                                   zaxis));
    // 4. Calculate camera up vector
    Vec3f yaxis = CrossProductVec3f(zaxis, xaxis);

    Mat4f translation = IdMat4f;
    *IndexMat4f(&translation, 0, 3) = -position.x;
    *IndexMat4f(&translation, 1, 3) = -position.y;
    *IndexMat4f(&translation, 2, 3) = -position.z;

    Mat4f rotation = IdMat4f;
    rotation.e[0][0] = xaxis.x;
    rotation.e[1][0] = xaxis.y;
    rotation.e[2][0] = xaxis.z;
    rotation.e[0][1] = yaxis.x;
    rotation.e[1][1] = yaxis.y;
    rotation.e[2][1] = yaxis.z;
    rotation.e[0][2] = zaxis.x;
    rotation.e[1][2] = zaxis.y;
    rotation.e[2][2] = zaxis.z;

    // Return lookAt matrix as combination of translation and rotation matrix
    return MultiplyMat4f(&rotation, &translation); // Remember to read from right to left (first translation then rotation)
}

Mat4f CreateVulkanPerspectiveMat4f(float rads, float aspect, float near, float far)
{
    Mat4f mat = CreatePerspectiveMat4f(rads, aspect, near, far);
    mat.e[1][1] *= -1;
    return mat;
}
