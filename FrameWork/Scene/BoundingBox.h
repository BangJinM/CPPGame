//https://developer.nvidia.com/gpugems/gpugems3/contributors
#pragma once

#include "MyMath.h"

namespace GameEngine
{
    struct Vec3
    {
        float x;
        float y;
        float z;
    };
    

    class BoundingBox
    {
    public:
        BoundingBox();


        BoundingBox Union(const BoundingBox &bb1, const BoundingBox &bb2);

        // create from minimum and maximum vectors
        BoundingBox(const VecterFloat3 &vMin, const VecterFloat3 &vMax);

        // create from set of points
        BoundingBox(const void *pPoints, int iNumPoints, int iStride);

        // set from minimum and maximum vectors
        void Set(const VecterFloat3 &vMin, const VecterFloat3 &vMax);

        // set from set of points
        void Set(const void *pPoints, int iNumPoints, int iStride);

        // returns size of bounding box
        VecterFloat3 GetSize(void) const { return m_vMax - m_vMin; }

        VecterFloat3 m_pPoints[8];
        VecterFloat3 m_vMin, m_vMax;
    };


}  // namespace GameEngine