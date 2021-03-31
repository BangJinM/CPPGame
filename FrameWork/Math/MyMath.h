#ifndef GameEngine_Math_H
#define GameEngine_Math_H

#include <glm/ext/scalar_constants.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>

namespace GameEngine
{
    typedef glm::vec4 ColorRGBA;
    typedef glm::vec3 VecterFloat3;
    typedef glm::vec4 VecterFloat4;
    typedef glm::vec2 VecterFloat2;
    typedef glm::mat4 GlmMat4;

    template <typename Type>
    inline void Swap(Type &A, Type &B)
    {
        Type C = A;
        A = B;
        B = C;
    }

    static VecterFloat3 RotationMatrixToEulerAngles(GlmMat4 &R)
    {
        float sy = (float)sqrt(R[0][0] * R[0][0] + R[1][0] * R[1][0]);

        bool singular = sy < 1e-6;  // If

        float x, y, z;
        if (!singular)
        {
            x = (float)glm::atan(R[2][1], R[2][2]);
            y = (float)glm::atan(-R[2][0], sy);
            z = (float)glm::atan(R[1][0], R[0][0]);
        }
        else
        {
            x = (float)glm::atan(-R[1][2], R[1][1]);
            y = (float)glm::atan(-R[2][0], sy);
            z = 0;
        }
        VecterFloat3 i;
        i.x = (float)(x * (180.0f / glm::pi<float>()));
        i.y = (float)(y * (180.0f / glm::pi<float>()));
        i.z = (float)(z * (180.0f / glm::pi<float>()));
        return i;
    }

    // clamp
    template <typename Type>
    inline Type Clamp(const Type &A, const Type &Min, const Type &Max)
    {
        if (A < Min)
            return Min;
        if (A > Max)
            return Max;
        return A;
    }

    // 取小
    template <typename Type>
    inline Type Min(const Type &A, const Type &B)
    {
        if (A < B)
            return A;
        return B;
    }

    // 取大
    template <typename Type>
    inline Type Max(const Type &A, const Type &B)
    {
        if (A > B)
            return A;
        return B;
    }

    // calculate cross product
    inline VecterFloat3 Cross(const VecterFloat3 &vA, const VecterFloat3 &vB)
    {
        return VecterFloat3((vA.y * vB.z) - (vA.z * vB.y),
                            (vA.z * vB.x) - (vA.x * vB.z),
                            (vA.x * vB.y) - (vA.y * vB.x));
    }

    inline void MatrixCompose(GlmMat4 &matrix, const VecterFloat3 &translation,
                              const VecterFloat3 &scale,
                              const VecterFloat3 &rotation)
    {
        matrix = glm::translate(matrix, translation);
        matrix = glm::scale(matrix, scale);
        matrix = matrix * glm::mat4_cast(glm::qua<float>(glm::radians(rotation)));
    }

}  // namespace GameEngine
#endif