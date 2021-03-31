#include "BoundingBox.h"

#include <glm/glm.hpp>

namespace GameEngine
{
    BoundingBox::BoundingBox()
    {
        m_vMin = VecterFloat3(FLT_MAX, FLT_MAX, FLT_MAX);
        m_vMax = VecterFloat3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    }

    // compute union of two bounding boxes
    BoundingBox BoundingBox::Union(const BoundingBox &bb1, const BoundingBox &bb2)
    {
        VecterFloat3 vMin, vMax;
        vMin.x = Min(bb1.m_vMin.x, bb2.m_vMin.x);
        vMin.y = Min(bb1.m_vMin.y, bb2.m_vMin.y);
        vMin.z = Min(bb1.m_vMin.z, bb2.m_vMin.z);
        vMax.x = Max(bb1.m_vMax.x, bb2.m_vMax.x);
        vMax.y = Max(bb1.m_vMax.y, bb2.m_vMax.y);
        vMax.z = Max(bb1.m_vMax.z, bb2.m_vMax.z);
        return BoundingBox(vMin, vMax);
    }

    // create from minimum and maximum vectors
    BoundingBox::BoundingBox(const VecterFloat3 &vMin, const VecterFloat3 &vMax)
    {
        Set(vMin, vMax);
    }

    // create from set of points
    BoundingBox::BoundingBox(const void *pPoints, int iNumPoints, int iStride)
    {
        Set(pPoints, iNumPoints, iStride);
    }

    // create from minimum and maximum vectors
    void BoundingBox::Set(const VecterFloat3 &vMin, const VecterFloat3 &vMax)
    {
        // calculate points
        m_pPoints[0] = VecterFloat3(vMin.x, vMin.y, vMin.z);
        m_pPoints[1] = VecterFloat3(vMax.x, vMin.y, vMin.z);
        m_pPoints[2] = VecterFloat3(vMin.x, vMin.y, vMax.z);
        m_pPoints[3] = VecterFloat3(vMax.x, vMin.y, vMax.z);
        m_pPoints[4] = VecterFloat3(vMin.x, vMax.y, vMin.z);
        m_pPoints[5] = VecterFloat3(vMax.x, vMax.y, vMin.z);
        m_pPoints[6] = VecterFloat3(vMin.x, vMax.y, vMax.z);
        m_pPoints[7] = VecterFloat3(vMax.x, vMax.y, vMax.z);
        m_vMin = vMin;
        m_vMax = vMax;
    }

    // create from set of points
    void BoundingBox::Set(const void *pPoints, int iNumPoints, int iStride)
    {
        // calculate min and max vectors
        m_vMin = VecterFloat3(FLT_MAX, FLT_MAX, FLT_MAX);
        m_vMax = VecterFloat3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
        char *pData = (char *)pPoints;
        for (int i = 0; i < iNumPoints; i++)
        {
            const Vec3 &vPoint = *(Vec3 *)pData;
            if (vPoint.x < m_vMin.x)
                m_vMin.x = vPoint.x;
            if (vPoint.y < m_vMin.y)
                m_vMin.y = vPoint.y;
            if (vPoint.z < m_vMin.z)
                m_vMin.z = vPoint.z;

            if (vPoint.x > m_vMax.x)
                m_vMax.x = vPoint.x;
            if (vPoint.y > m_vMax.y)
                m_vMax.y = vPoint.y;
            if (vPoint.z > m_vMax.z)
                m_vMax.z = vPoint.z;

            // next position
            pData += iStride;
        }
        // create from vectors
        Set(m_vMin, m_vMax);
    }
}  // namespace GameEngine