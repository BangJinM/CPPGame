#include "Material.h"

namespace GameEngine
{
    static const unsigned int DefaultNumAllocated = 5;  

    MaterialProperty::MaterialProperty() :mKey(nullptr), mSemantic(0), mIndex(0), mDataLength(0), mType(PropertyTypeInfo::aiPTI_Float), mData(nullptr)
    {
    }

    MaterialProperty::~MaterialProperty()
    {
        delete[] mData;
		delete[] mKey;
        mData = nullptr;
		mKey = nullptr;
    }

    bool Material::AddBinaryProperty(const void *pInput, unsigned int pSizeInBytes, const char *pKey, unsigned int type, unsigned int index, PropertyTypeInfo pType)
    {
        if (0 == pSizeInBytes)
        {
            return false;
        }

        // first search the list whether there is already an entry with this key
        unsigned int iOutIndex(UINT_MAX);
        for (unsigned int i = 0; i < mNumProperties; ++i)
        {
            MaterialProperty *prop(mProperties[i]);

            if (prop /* just for safety */ && !strcmp(prop->mKey, pKey) &&
                prop->mSemantic == type && prop->mIndex == index)
            {

                delete mProperties[i];
                iOutIndex = i;
            }
        }

        // Allocate a new material property
        MaterialProperty *pcNew = new MaterialProperty();

        // .. and fill it
        pcNew->mType = pType;
        pcNew->mSemantic = type;
        pcNew->mIndex = index;

        pcNew->mDataLength = pSizeInBytes;
        pcNew->mData = new char[pSizeInBytes];
        memcpy(pcNew->mData, pInput, pSizeInBytes);
		pcNew->mKey = new char[sizeof(pKey)];
        memcpy(pcNew->mKey, pKey, sizeof(pKey));

        if (UINT_MAX != iOutIndex)
        {
            mProperties[iOutIndex] = pcNew;
            return true;
        }

        // resize the array ... double the storage allocated
        if (mNumProperties == mNumAllocated)
        {
            const unsigned int iOld = mNumAllocated;
            mNumAllocated *= 2;

            MaterialProperty **ppTemp;
            try
            {
                ppTemp = new MaterialProperty *[mNumAllocated];
            }
            catch (std::bad_alloc &)
            {
                delete pcNew;
                return false;
            }

            // just copy all items over; then replace the old array
            memcpy(ppTemp, mProperties, iOld * sizeof(void *));

            delete[] mProperties;
            mProperties = ppTemp;
        }
        // push back ...
        mProperties[mNumProperties++] = pcNew;

        return true;
    }
    bool Material::AddProperty(const std::string *pInput, const char *pKey, unsigned int type, unsigned int index)
    {
        return false;
    }
    bool Material::AddProperty(const glm::vec<3, float, glm::defaultp> *pInput, unsigned int pNumValues, const char *pKey, unsigned int type, unsigned int index)
    {
        return false;
    }
    bool Material::AddProperty(const int *pInput, unsigned int pNumValues, const char *pKey, unsigned int type, unsigned int index)
    {
        return false;
    }
    bool Material::AddProperty(const float *pInput, unsigned int pNumValues, const char *pKey, unsigned int type, unsigned int index)
    {
        return AddBinaryProperty((const void *)pInput,pNumValues * sizeof(float),pKey, type, index, aiPTI_Float);
    }
    bool Material::AddProperty(const double *pInput, unsigned int pNumValues, const char *pKey, unsigned int type, unsigned int index)
    {
        return false;
    }
    bool Material::AddProperty(const UVTransform *pInput, unsigned int pNumValues, const char *pKey, unsigned int type, unsigned int index)
    {

        return false;
    }
    bool Material::RemoveProperty(const char *pKey, unsigned int type, unsigned int index)
    {
        return false;
    }
    void Material::Clear()
    {
    }
    void Material::CopyPropertyList(Material *pcDest, const Material *pcSrc)
    {
    }
    Material::Material(): mProperties( nullptr ), mNumProperties( 0 ), mNumAllocated( DefaultNumAllocated )
    {
        mProperties = new MaterialProperty*[ DefaultNumAllocated ];
    }
    Material::~Material()
    {
    }
    std::string Material::GetName()
    {
        return std::string();
    }
    bool Material::Get(const char *pKey, unsigned int type, unsigned int idx, int *pOut, unsigned int *pMax) const
    {
        return false;
    }
    bool Material::Get(const char *pKey, unsigned int type, unsigned int idx, float *pOut, unsigned int *pMax) const
    {
        return false;
    }
    bool Material::Get(const char *pKey, unsigned int type, unsigned int idx, int &pOut) const
    {
        return false;
    }
    bool Material::Get(const char *pKey, unsigned int type, unsigned int idx, float &pOut) const
    {
        return false;
    }
    bool Material::Get(const char *pKey, unsigned int type, unsigned int idx, std::string &pOut) const
    {
        return false;
    }
    bool Material::Get(const char *pKey, unsigned int type, unsigned int idx, glm::vec<3, float, glm::defaultp> &pOut) const
    {
        return false;
    }
    bool Material::Get(const char *pKey, unsigned int type, unsigned int idx, UVTransform &pOut) const
    {
        return false;
    }
    unsigned int Material::GetTextureCount(TextureType type) const
    {
        return 0;
    }
    bool Material::GetTexture(TextureType type, unsigned int index, std::string *path, aiTextureMapping *mapping, unsigned int *uvindex, float *blend, TextureOp *op, TextureMapMode *mapmode) const
    {
        return false;
    }
} // namespace GameEngine