//https://developer.nvidia.com/gpugems/gpugems3/contributors

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "BoundingBox.h"
#include "MyMath.h"
// AABB vs AABB test, returns true if objects intersect
//
//
namespace GameEngine
{
    inline bool IntersectionTest(const BoundingBox &objectBB, const BoundingBox &frustumBB)
    {
        // min and max vectors
        const glm::vec3 &vFrustumMin = frustumBB.m_vMin;
        const glm::vec3 &vFrustumMax = frustumBB.m_vMax;
        const glm::vec3 &vObjectMin = objectBB.m_vMin;
        const glm::vec3 &vObjectMax = objectBB.m_vMax;

        // test all axes
        //
        if (vObjectMin.x > vFrustumMax.x || vFrustumMin.x > vObjectMax.x)
            return false;
        if (vObjectMin.y > vFrustumMax.y || vFrustumMin.y > vObjectMax.y)
            return false;
        if (vObjectMin.z > vFrustumMax.z || vFrustumMin.z > vObjectMax.z)
            return false;

        // all tests passed - intersection occurs
        return true;
    }

    // AABB vs AABB sweep test, returns true if intersection can occur if object is translated along given direction
    //
    //
    inline bool SweepIntersectionTest(const BoundingBox &objectBB, const BoundingBox &frustumBB, const glm::vec3 &vSweepDir)
    {
        // min and max vectors of object
        const glm::vec3 &vFrustumMin = frustumBB.m_vMin;
        const glm::vec3 &vFrustumMax = frustumBB.m_vMax;
        const glm::vec3 &vObjectMin = objectBB.m_vMin;
        const glm::vec3 &vObjectMax = objectBB.m_vMax;

        // calculate projections along sweep direction
        //

        // project AABB center point
        glm::vec3 vFrustumCenter = (vFrustumMin + vFrustumMax) * 0.5f;
        glm::vec3 vFrustumHalfSize = (vFrustumMax - vFrustumMin) * 0.5f;
        float fFrustumCenterProj = glm::dot(vFrustumCenter, vSweepDir);
        // project AABB half-size
        float fFrustumHalfSizeProj = vFrustumHalfSize.x * fabs(vSweepDir.x) +
                                     vFrustumHalfSize.y * fabs(vSweepDir.y) +
                                     vFrustumHalfSize.z * fabs(vSweepDir.z);
        float fFrustumProjMin = fFrustumCenterProj - fFrustumHalfSizeProj;
        float fFrustumProjMax = fFrustumCenterProj + fFrustumHalfSizeProj;

        // project AABB center poin
        glm::vec3 vObjectCenter = (vObjectMin + vObjectMax) * 0.5f;
        glm::vec3 vObjectHalfSize = (vObjectMax - vObjectMin) * 0.5f;
        float fObjectCenterProj = glm::dot(vObjectCenter, vSweepDir);
        // project AABB half-size
        float fObjectHalfSizeProj = vObjectHalfSize.x * fabs(vSweepDir.x) +
                                    vObjectHalfSize.y * fabs(vSweepDir.y) +
                                    vObjectHalfSize.z * fabs(vSweepDir.z);
        float fObjectProjMin = fObjectCenterProj - fObjectHalfSizeProj;
        float fObjectProjMax = fObjectCenterProj + fObjectHalfSizeProj;

        // find the distance in sweep direction
        // where intersection occurs on all axis.
        //

        // sweep direction intersection
        // starts: fObjectProjMax + fDist = fFrustumProjMin
        //   ends: fObjectProjMin + fDist = fFrustumProjMax
        float fDistMin = fFrustumProjMin - fObjectProjMax;
        float fDistMax = fFrustumProjMax - fObjectProjMin;
        if (fDistMin > fDistMax)
            Swap(fDistMin, fDistMax);

        // only intersects in opposite of sweep direction
        if (fDistMax < 0)
            return false;

        // intersection on an axis:
        // starts: vObjectMax.x + fDist*vSweepDir.x = vFrustumMin.x
        //   ends: vObjectMin.x + fDist*vSweepDir.x = vFrustumMax.x

        // test x-axis:
        if (vSweepDir.x == 0)
        {
            // there is never an intersection on this axis
            if (vFrustumMin.x > vObjectMax.x || vObjectMin.x > vFrustumMax.x)
                return false;
        }
        else
        {
            float fDistMinNew = (vFrustumMin.x - vObjectMax.x) / vSweepDir.x;
            float fDistMaxNew = (vFrustumMax.x - vObjectMin.x) / vSweepDir.x;
            if (fDistMinNew > fDistMaxNew)
                Swap(fDistMinNew, fDistMaxNew);

            // distance ranges don't overlap
            if (fDistMin > fDistMaxNew || fDistMinNew > fDistMax)
                return false;
            // otherwise merge ranges
            fDistMin = Max(fDistMin, fDistMinNew);
            fDistMax = Min(fDistMax, fDistMaxNew);
        }

        // test y-axis:
        if (vSweepDir.y == 0)
        {
            // there is never an intersection on this axis
            if (vFrustumMin.y > vObjectMax.y || vObjectMin.y > vFrustumMax.y)
                return false;
        }
        else
        {
            float fDistMinNew = (vFrustumMin.y - vObjectMax.y) / vSweepDir.y;
            float fDistMaxNew = (vFrustumMax.y - vObjectMin.y) / vSweepDir.y;
            if (fDistMinNew > fDistMaxNew)
                Swap(fDistMinNew, fDistMaxNew);

            // distance ranges don't overlap
            if (fDistMin > fDistMaxNew || fDistMinNew > fDistMax)
                return false;
            // otherwise merge ranges
            fDistMin = Max(fDistMin, fDistMinNew);
            fDistMax = Min(fDistMax, fDistMaxNew);
        }

        // test z-axis:
        if (vSweepDir.z == 0)
        {
            // there is never an intersection on this axis
            if (vFrustumMin.z > vObjectMax.z || vObjectMin.z > vFrustumMax.z)
                return false;
        }
        else
        {
            float fDistMinNew = (vFrustumMin.z - vObjectMax.z) / vSweepDir.z;
            float fDistMaxNew = (vFrustumMax.z - vObjectMin.z) / vSweepDir.z;
            if (fDistMinNew > fDistMaxNew)
                Swap(fDistMinNew, fDistMaxNew);

            // distance ranges don't overlap
            if (fDistMin > fDistMaxNew || fDistMinNew > fDistMax)
                return false;
        }

        // all tests passed - intersection occurs
        return true;
    }

    // Helper function for AABB vs frustum test
    //
    //
    inline bool ProjectedIntersection(const glm::vec3 &vHalfSize, const glm::vec3 &vCenter,
                                      const glm::vec3 *pFrustumPoints,
                                      const glm::vec3 &vDir)
    {
        // project AABB center point to vector
        float fCenter = glm::dot(vCenter, vDir);
        // project AABB half-size to vector
        float fHalfSize = vHalfSize.x * fabs(vDir.x) +
                          vHalfSize.y * fabs(vDir.y) +
                          vHalfSize.z * fabs(vDir.z);

        float fMin1 = fCenter - fHalfSize;
        float fMax1 = fCenter + fHalfSize;

        // project frustum points
        float fProj2 = glm::dot(pFrustumPoints[0], vDir);
        float fMin2 = fProj2;
        float fMax2 = fProj2;
        for (int i = 1; i < 8; i++)
        {
            fProj2 = glm::dot(pFrustumPoints[i], vDir);
            fMin2 = Min(fProj2, fMin2);
            fMax2 = Max(fProj2, fMax2);
        }

        // test for overlap
        if (fMin1 > fMax2 || fMax1 < fMin2)
            return false;

        return true;
    }

    // AABB vs Frustum test, returns true if objects intersect
    //
    //
    inline bool IntersectionTest(const BoundingBox &objectBB, const Frustum &frustum)
    {
        // Note that this code is very unoptimal
        //
        //
        glm::vec3 vHalfSize = (objectBB.m_vMax - objectBB.m_vMin) * 0.5f;
        glm::vec3 vCenter = (objectBB.m_vMin + objectBB.m_vMax) * 0.5f;

        // AABB face normals
        if (!ProjectedIntersection(vHalfSize, vCenter, frustum.m_pPoints, glm::vec3(1, 0, 0)))
            return false;
        if (!ProjectedIntersection(vHalfSize, vCenter, frustum.m_pPoints, glm::vec3(0, 1, 0)))
            return false;
        if (!ProjectedIntersection(vHalfSize, vCenter, frustum.m_pPoints, glm::vec3(0, 0, 1)))
            return false;

        // frustum face normals
        //

        // front and back faces:
        glm::vec3 vNorm1 = glm::normalize(Cross(frustum.m_pPoints[1] - frustum.m_pPoints[0],
                                                frustum.m_pPoints[3] - frustum.m_pPoints[0]));
        if (!ProjectedIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm1))
            return false;

        // left face:
        glm::vec3 vNorm2 = glm::normalize(Cross(frustum.m_pPoints[1] - frustum.m_pPoints[0],
                                                frustum.m_pPoints[4] - frustum.m_pPoints[0]));
        if (!ProjectedIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm2))
            return false;

        // right face:
        glm::vec3 vNorm3 = glm::normalize(Cross(frustum.m_pPoints[2] - frustum.m_pPoints[3],
                                                frustum.m_pPoints[7] - frustum.m_pPoints[3]));
        if (!ProjectedIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm3))
            return false;

        // top face:
        glm::vec3 vNorm4 = glm::normalize(Cross(frustum.m_pPoints[2] - frustum.m_pPoints[1],
                                                frustum.m_pPoints[5] - frustum.m_pPoints[1]));
        if (!ProjectedIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm4))
            return false;

        // bottom face:
        glm::vec3 vNorm5 = glm::normalize(Cross(frustum.m_pPoints[3] - frustum.m_pPoints[0],
                                                frustum.m_pPoints[4] - frustum.m_pPoints[0]));
        if (!ProjectedIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm5))
            return false;

        // edge cross edge cases
        //
        glm::vec3 pBoxEdges[3] = {glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)};
        for (int i = 0; i < 3; i++)
        {
            // edge up-down
            glm::vec3 vNorm1 = glm::normalize(Cross(frustum.m_pPoints[1] - frustum.m_pPoints[0], pBoxEdges[i]));
            if (!ProjectedIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm1))
                return false;

            // edge left-right
            glm::vec3 vNorm2 = glm::normalize(Cross(frustum.m_pPoints[3] - frustum.m_pPoints[0], pBoxEdges[i]));
            if (!ProjectedIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm2))
                return false;

            // edge bottom left
            glm::vec3 vNorm3 = glm::normalize(Cross(frustum.m_pPoints[4] - frustum.m_pPoints[0], pBoxEdges[i]));
            if (!ProjectedIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm3))
                return false;

            // edge top left
            glm::vec3 vNorm4 = glm::normalize(Cross(frustum.m_pPoints[5] - frustum.m_pPoints[1], pBoxEdges[i]));
            if (!ProjectedIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm4))
                return false;

            // edge top right
            glm::vec3 vNorm5 = glm::normalize(Cross(frustum.m_pPoints[6] - frustum.m_pPoints[2], pBoxEdges[i]));
            if (!ProjectedIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm5))
                return false;

            // edge bottom right
            glm::vec3 vNorm6 = glm::normalize(Cross(frustum.m_pPoints[7] - frustum.m_pPoints[3], pBoxEdges[i]));
            if (!ProjectedIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm6))
                return false;
        }

        // all tests passed - intersection occurs
        return true;
    }

    // Helper function for AABB vs Frustum sweep test
    //
    //
    inline bool ProjectedSweepIntersection(const glm::vec3 &vHalfSize, const glm::vec3 &vCenter,
                                           const glm::vec3 *pFrustumPoints,
                                           const glm::vec3 &vDir,
                                           float &fDistMin, float &fDistMax, const glm::vec3 &vSweepDir)
    {
        // project sweep direction
        float fSweepDir = glm::dot(vSweepDir, vDir);

        // project AABB center point to vector
        float fCenter = glm::dot(vCenter, vDir);
        // project AABB half-size to vector
        float fHalfSize = vHalfSize.x * fabs(vDir.x) +
                          vHalfSize.y * fabs(vDir.y) +
                          vHalfSize.z * fabs(vDir.z);

        float fMin1 = fCenter - fHalfSize;
        float fMax1 = fCenter + fHalfSize;

        // project frustum points
        float fProj2 = glm::dot(pFrustumPoints[0], vDir);
        float fMin2 = fProj2;
        float fMax2 = fProj2;
        for (int i = 1; i < 8; i++)
        {
            fProj2 = glm::dot(pFrustumPoints[i], vDir);
            fMin2 = Min(fProj2, fMin2);
            fMax2 = Max(fProj2, fMax2);
        }

        // sweep can affect intersection
        if (fSweepDir != 0)
        {
            // intersection starts when fMax1 + fSweepDir * t >= fMin2
            //
            float fIntersectionStart = (fMin2 - fMax1) / fSweepDir;

            // intersection ends when fMin1 + fSweepDir * t >= fMax2
            //
            float fIntersectionEnd = (fMax2 - fMin1) / fSweepDir;

            // ranges must be in right order
            if (fIntersectionStart > fIntersectionEnd)
                Swap(fIntersectionStart, fIntersectionEnd);

            // distance ranges don't overlap
            if (fDistMin > fIntersectionEnd || fIntersectionStart > fDistMax)
            {
                return false;
            }

            // otherwise merge ranges
            fDistMin = Max(fDistMin, fIntersectionStart);
            fDistMax = Min(fDistMax, fIntersectionEnd);
        }
        // sweep doesn't affect intersection
        else
        {
            // no intersectection ever
            if (fMin1 > fMax2 || fMin2 > fMax1)
            {
                return false;
            }
        }

        return true;
    }

    // AABB vs Frustum sweep test, returns true if intersection can occur if object is translated along given direction
    //
    //
    inline bool SweepIntersectionTest(const BoundingBox &objectBB, const Frustum &frustum, const glm::vec3 &vSweepDir)
    {
        // Note that this code is very unoptimal
        //
        //

        glm::vec3 vHalfSize = (objectBB.m_vMax - objectBB.m_vMin) * 0.5f;
        glm::vec3 vCenter = (objectBB.m_vMin + objectBB.m_vMax) * 0.5f;

        float fDistMin = 0.0f;
        float fDistMax = FLT_MAX;

        // find potential intersection range in sweep direction
        if (!ProjectedSweepIntersection(vHalfSize, vCenter, frustum.m_pPoints, vSweepDir, fDistMin, fDistMax, vSweepDir))
            return false;

        // AABB face normals
        if (!ProjectedSweepIntersection(vHalfSize, vCenter, frustum.m_pPoints, glm::vec3(1, 0, 0), fDistMin, fDistMax, vSweepDir))
            return false;
        if (!ProjectedSweepIntersection(vHalfSize, vCenter, frustum.m_pPoints, glm::vec3(0, 1, 0), fDistMin, fDistMax, vSweepDir))
            return false;
        if (!ProjectedSweepIntersection(vHalfSize, vCenter, frustum.m_pPoints, glm::vec3(0, 0, 1), fDistMin, fDistMax, vSweepDir))
            return false;

        // frustum face normals
        //

        // front and back faces:
        glm::vec3 vNorm1 = glm::normalize(Cross(frustum.m_pPoints[1] - frustum.m_pPoints[0],
                                                frustum.m_pPoints[3] - frustum.m_pPoints[0]));
        if (!ProjectedSweepIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm1, fDistMin, fDistMax, vSweepDir))
            return false;

        // left face:
        glm::vec3 vNorm2 = glm::normalize(Cross(frustum.m_pPoints[1] - frustum.m_pPoints[0],
                                                frustum.m_pPoints[4] - frustum.m_pPoints[0]));
        if (!ProjectedSweepIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm2, fDistMin, fDistMax, vSweepDir))
            return false;

        // right face:
        glm::vec3 vNorm3 = glm::normalize(Cross(frustum.m_pPoints[2] - frustum.m_pPoints[3],
                                                frustum.m_pPoints[7] - frustum.m_pPoints[3]));
        if (!ProjectedSweepIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm3, fDistMin, fDistMax, vSweepDir))
            return false;

        // top face:
        glm::vec3 vNorm4 = glm::normalize(Cross(frustum.m_pPoints[2] - frustum.m_pPoints[1],
                                                frustum.m_pPoints[5] - frustum.m_pPoints[1]));
        if (!ProjectedSweepIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm4, fDistMin, fDistMax, vSweepDir))
            return false;

        // bottom face:
        glm::vec3 vNorm5 = glm::normalize(Cross(frustum.m_pPoints[3] - frustum.m_pPoints[0],
                                                frustum.m_pPoints[4] - frustum.m_pPoints[0]));
        if (!ProjectedSweepIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm5, fDistMin, fDistMax, vSweepDir))
            return false;

        // edge cross edge cases
        //
        glm::vec3 pBoxEdges[3] = {glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)};
        for (int i = 0; i < 3; i++)
        {
            // edge up-down
            glm::vec3 vNorm1 = glm::normalize(Cross(frustum.m_pPoints[1] - frustum.m_pPoints[0], pBoxEdges[i]));
            if (!ProjectedSweepIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm1, fDistMin, fDistMax, vSweepDir))
                return false;

            // edge left-right
            glm::vec3 vNorm2 = glm::normalize(Cross(frustum.m_pPoints[3] - frustum.m_pPoints[0], pBoxEdges[i]));
            if (!ProjectedSweepIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm2, fDistMin, fDistMax, vSweepDir))
                return false;

            // edge bottom left
            glm::vec3 vNorm3 = glm::normalize(Cross(frustum.m_pPoints[4] - frustum.m_pPoints[0], pBoxEdges[i]));
            if (!ProjectedSweepIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm3, fDistMin, fDistMax, vSweepDir))
                return false;

            // edge top left
            glm::vec3 vNorm4 = glm::normalize(Cross(frustum.m_pPoints[5] - frustum.m_pPoints[1], pBoxEdges[i]));
            if (!ProjectedSweepIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm4, fDistMin, fDistMax, vSweepDir))
                return false;

            // edge top right
            glm::vec3 vNorm5 = glm::normalize(Cross(frustum.m_pPoints[6] - frustum.m_pPoints[2], pBoxEdges[i]));
            if (!ProjectedSweepIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm5, fDistMin, fDistMax, vSweepDir))
                return false;

            // edge bottom right
            glm::vec3 vNorm6 = glm::normalize(Cross(frustum.m_pPoints[7] - frustum.m_pPoints[3], pBoxEdges[i]));
            if (!ProjectedSweepIntersection(vHalfSize, vCenter, frustum.m_pPoints, vNorm6, fDistMin, fDistMax, vSweepDir))
                return false;
        }

        // all tests passed - intersection occurs
        return true;
    }
}  // namespace GameEngine