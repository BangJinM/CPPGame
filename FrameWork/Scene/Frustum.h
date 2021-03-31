//https://developer.nvidia.com/gpugems/gpugems3/contributors
#pragma once

#include <glm/glm.hpp>
#include "BoundingBox.h"
/** */
namespace GameEngine
{
    /** */
    class Frustum
    {
    public:
        glm::vec3 m_pPoints[8];
        BoundingBox m_AABB;

        inline void CalculateAABB();
    };
    // computes AABB vectors from corner points
    inline void Frustum::CalculateAABB(void)
    {
        float points[8 * 3];
        for (size_t i = 0; i < 8; i++)
        {
            points[3 * i] = m_pPoints[i].x;
            points[3 * i + 1] = m_pPoints[i].y;
            points[3 * i + 2] = m_pPoints[i].z;
        }

        m_AABB.Set(points, 8, sizeof(float) * 3);
    }

}  // namespace GameEngine
