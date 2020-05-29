#ifndef CPPGAME_Common_Scene_Material_H
#define CPPGAME_Common_Scene_Material_H

#include <string>
#include "MyMath.h"
using namespace myMath;
namespace GameEngine
{

    enum TextureType
    {
        aiTextureType_NONE = 0,

        aiTextureType_DIFFUSE = 1,

        aiTextureType_SPECULAR = 2,

        aiTextureType_AMBIENT = 3,

        aiTextureType_EMISSIVE = 4,

        aiTextureType_HEIGHT = 5,

        aiTextureType_NORMALS = 6,

        aiTextureType_SHININESS = 7,

        aiTextureType_OPACITY = 8,

        aiTextureType_DISPLACEMENT = 9,

        aiTextureType_LIGHTMAP = 10,

        aiTextureType_REFLECTION = 11,

        aiTextureType_BASE_COLOR = 12,

        aiTextureType_NORMAL_CAMERA = 13,

        aiTextureType_EMISSION_COLOR = 14,

        aiTextureType_METALNESS = 15,

        aiTextureType_DIFFUSE_ROUGHNESS = 16,

        aiTextureType_AMBIENT_OCCLUSION = 17,

        aiTextureType_UNKNOWN = 18,

    };

    enum TextureMapMode
    {
        aiTextureMapMode_Wrap = 0x0,

        aiTextureMapMode_Clamp = 0x1,

        aiTextureMapMode_Decal = 0x3,

        aiTextureMapMode_Mirror = 0x2,

        _aiTextureMapMode_Force32Bit = INT_MAX
    };

    enum TextureOp
    {
        /** T = T1 * T2 */
        aiTextureOp_Multiply = 0x0,

        /** T = T1 + T2 */
        aiTextureOp_Add = 0x1,

        /** T = T1 - T2 */
        aiTextureOp_Subtract = 0x2,

        /** T = T1 / T2 */
        aiTextureOp_Divide = 0x3,

        /** T = (T1 + T2) - (T1 * T2) */
        aiTextureOp_SmoothAdd = 0x4,
        /** T = T1 + (T2-0.5) */
        aiTextureOp_SignedAdd = 0x5,

        _aiTextureOp_Force32Bit = INT_MAX
    };

    enum aiTextureMapping
    {
        aiTextureMapping_UV = 0x0,

        aiTextureMapping_SPHERE = 0x1,

        aiTextureMapping_CYLINDER = 0x2,

        aiTextureMapping_BOX = 0x3,

        aiTextureMapping_PLANE = 0x4,

        aiTextureMapping_OTHER = 0x5,

        _aiTextureMapping_Force32Bit = INT_MAX
    };

    enum PropertyTypeInfo
    {
        aiPTI_Float = 0x1,

        aiPTI_Double = 0x2,

        aiPTI_String = 0x3,

        aiPTI_Integer = 0x4,

        aiPTI_Buffer = 0x5,
    };

    struct MaterialProperty
    {
        char *mKey;

        unsigned int mSemantic;

        unsigned int mIndex;

        unsigned int mDataLength;

        PropertyTypeInfo mType;

        char *mData;

        MaterialProperty();
        ~MaterialProperty();
    };

    struct UVTransform
    {

        glm::vec<2, float, glm::defaultp> mTranslation;

        glm::vec<2, float, glm::defaultp> mScaling;

        float mRotation;

        UVTransform()
            : mTranslation(0.0, 0.0), mScaling(1.0, 1.0), mRotation(0.0)
        {
            // nothing to be done here ...
        }
    };

    struct Material
    {
    public:
        Material();
        ~Material();

        std::string GetName();

        template <typename Type>
        bool Get(const char *pKey, unsigned int type,
                 unsigned int idx, Type *pOut, unsigned int *pMax) const;

        bool Get(const char *pKey, unsigned int type,
                 unsigned int idx, int *pOut, unsigned int *pMax) const;

        bool Get(const char *pKey, unsigned int type,
                 unsigned int idx, float *pOut, unsigned int *pMax) const;

        template <typename Type>
        bool Get(const char *pKey, unsigned int type,
                 unsigned int idx, Type &pOut) const;

        bool Get(const char *pKey, unsigned int type,
                 unsigned int idx, int &pOut) const;

        bool Get(const char *pKey, unsigned int type,
                 unsigned int idx, float &pOut) const;

        bool Get(const char *pKey, unsigned int type,
                 unsigned int idx, std::string &pOut) const;

        bool Get(const char *pKey, unsigned int type,
                 unsigned int idx, vecterFloat3 &pOut) const;

        bool Get(const char *pKey, unsigned int type,
                 unsigned int idx, vecterFloat4 &pOut) const;

        bool Get(const char *pKey, unsigned int type,
                 unsigned int idx, UVTransform &pOut) const;

        static bool getMaterialProperty(const Material* pMat, const char *pKey, unsigned int type, unsigned int index, const MaterialProperty **pPropOut);

        unsigned int GetTextureCount(TextureType type) const;

        bool GetTexture(TextureType type,
                        unsigned int index,
                        std::string *path,
                        aiTextureMapping *mapping = NULL,
                        unsigned int *uvindex = NULL,
                        float *blend = NULL,
                        TextureOp *op = NULL,
                        TextureMapMode *mapmode = NULL) const;

        bool AddBinaryProperty(const void *pInput,
                               unsigned int pSizeInBytes,
                               const char *pKey,
                               unsigned int type,
                               unsigned int index,
                               PropertyTypeInfo pType);

        bool AddProperty(const std::string *pInput,
                         const char *pKey,
                         unsigned int type = 0,
                         unsigned int index = 0);

        template <typename Type>
        bool AddProperty(const Type *pInput,
                         unsigned int pNumValues,
                         const char *pKey,
                         unsigned int type = 0,
                         unsigned int index = 0);

        bool AddProperty(const vecterFloat3 *pInput,
                         unsigned int pNumValues,
                         const char *pKey,
                         unsigned int type = 0,
                         unsigned int index = 0);

        bool AddProperty(const vecterFloat4 *pInput,
                         unsigned int pNumValues,
                         const char *pKey,
                         unsigned int type = 0,
                         unsigned int index = 0);

        bool AddProperty(const int *pInput,
                         unsigned int pNumValues,
                         const char *pKey,
                         unsigned int type = 0,
                         unsigned int index = 0);

        bool AddProperty(const float *pInput,
                         unsigned int pNumValues,
                         const char *pKey,
                         unsigned int type = 0,
                         unsigned int index = 0);

        bool AddProperty(const double *pInput,
                         unsigned int pNumValues,
                         const char *pKey,
                         unsigned int type = 0,
                         unsigned int index = 0);

        bool AddProperty(const UVTransform *pInput,
                         unsigned int pNumValues,
                         const char *pKey,
                         unsigned int type = 0,
                         unsigned int index = 0);

        bool RemoveProperty(const char *pKey,
                            unsigned int type = 0,
                            unsigned int index = 0);

        void Clear();

        static void CopyPropertyList(Material *pcDest,
                                     const Material *pcSrc);

        MaterialProperty **mProperties;

        unsigned int mNumProperties;

        unsigned int mNumAllocated;
    };

    template <typename Type>
    inline bool Material::Get(const char *pKey, unsigned int type, unsigned int idx, Type *pOut, unsigned int *pMax) const
    {
        return false;
    }

    template <typename Type>
    inline bool Material::Get(const char *pKey, unsigned int type, unsigned int idx, Type &pOut) const
    {
        return false;
    }

    template <typename Type>
    inline bool Material::AddProperty(const Type *pInput, unsigned int pNumValues, const char *pKey, unsigned int type, unsigned int index)
    {
        return false;
    }

} // namespace GameEngine

#endif //MAENGINE_IAPPLICATION_H
