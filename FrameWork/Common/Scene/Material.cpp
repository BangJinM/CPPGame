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
		int size = strlen(pKey) * sizeof(char);
		pcNew->mKey = new char[size + 1];
        memset(pcNew->mKey, '\0', size + 1);
        memcpy(pcNew->mKey, pKey, size);
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
        return AddBinaryProperty((const void *)pInput, pInput->length(), pKey, type, index, aiPTI_String);
    }

    bool Material::AddProperty(const vecterFloat3 *pInput, unsigned int pNumValues, const char *pKey, unsigned int type, unsigned int index)
    {
		return AddBinaryProperty((const void *)pInput, pNumValues * sizeof(vecterFloat4), pKey, type, index, aiPTI_Buffer);
    }

    bool Material::AddProperty(const vecterFloat4 *pInput, unsigned int pNumValues, const char *pKey, unsigned int type, unsigned int index)
    {
		return AddBinaryProperty((const void *)pInput, pNumValues * sizeof(vecterFloat4), pKey, type, index, aiPTI_Buffer);
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
        const MaterialProperty* prop;
        getMaterialProperty(this, pKey,type,idx, (const MaterialProperty**) &prop);
		if (prop) {
			string* p = (std::string*)prop->mData;
			pOut = *p;
			return true;
		}
        return false;
        return false;
    }
    bool Material::Get(const char *pKey, unsigned int type, unsigned int idx, vecterFloat3 &pOut) const
    {
        const MaterialProperty* prop;
        getMaterialProperty(this, pKey,type,idx, (const MaterialProperty**) &prop);
		if (prop) {
			vecterFloat3* p = (vecterFloat3*)prop->mData;
			pOut = *p;
			return true;
		}
        return false;
    }
    bool Material::Get(const char *pKey, unsigned int type, unsigned int idx, vecterFloat4 &pOut) const
    {
		const MaterialProperty* prop;
		getMaterialProperty(this, pKey, type, idx, (const MaterialProperty**)&prop);
		if (prop) {
			vecterFloat4* p = (vecterFloat4*)prop->mData;
			pOut = *p;
			return true;
		}
        return false;
    }
    bool Material::Get(const char *pKey, unsigned int type, unsigned int idx, UVTransform &pOut) const
    {
		const MaterialProperty* prop;
		getMaterialProperty(this, pKey, type, idx, (const MaterialProperty**)&prop);
		if (prop) {
			UVTransform* p = (UVTransform*)prop->mData;
			pOut = *p;
			return true;
		}
		return false;
    }

	bool Material::getMaterialProperty(const Material* pMat, const char * pKey, unsigned int type, unsigned int index, const MaterialProperty ** pPropOut)
	{
		for (unsigned int i = 0; i < pMat->mNumProperties; ++i) {
			MaterialProperty* prop = pMat->mProperties[i];

			if (prop /* just for safety ... */
				&& 0 == strcmp(prop->mKey, pKey)
				&& (UINT_MAX == type || prop->mSemantic == type) /* UINT_MAX is a wild-card, but this is undocumented :-) */
				&& (UINT_MAX == index || prop->mIndex == index))
			{
				*pPropOut = pMat->mProperties[i];
				return true;
			}
		}
		*pPropOut = NULL;
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