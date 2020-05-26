
#ifndef CPPGAME_Common_Scene_MaterialManager_H
#define CPPGAME_Common_Scene_MaterialManager_H
#include "Material.h"
namespace GameEngine
{
    uint32_t ComputeMaterialHash(const Material *mat, bool includeMatName = false);

    bool aiGetMaterialFloatArray(const Material *pMat, const char *pKey, unsigned int type, unsigned int index, float *pOut, unsigned int *pMax);

    bool aiGetMaterialProperty(const Material *pMat, const char *pKey, unsigned int type, unsigned int index, const MaterialProperty **pPropOut);
} // namespace GameEngine

#endif