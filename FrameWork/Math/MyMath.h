#ifndef GameEngine_Math_H
#define GameEngine_Math_H

#include <glm/glm.hpp>
namespace myMath{
    typedef glm::vec<4, uint8_t, glm::defaultp> R8G8B8A8Unorm;
    typedef glm::vec<3, float, glm::defaultp> vecterFloat3;
    typedef glm::vec<4, float, glm::defaultp> vecterFloat4;
    typedef glm::vec<2, float, glm::defaultp> vecterFloat2;
}
#endif