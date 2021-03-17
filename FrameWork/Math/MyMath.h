#ifndef GameEngine_Math_H
#define GameEngine_Math_H

#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>
namespace GameEngine
{
    typedef glm::vec4 ColorRGBA;
    typedef glm::vec3 VecterFloat3;
    typedef glm::vec4 VecterFloat4;
    typedef glm::vec2 VecterFloat2;
    typedef glm::mat4 GlmMat4;

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
}  // namespace GameEngine
#endif