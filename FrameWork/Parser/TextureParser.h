#pragma once
#include <cstdint>
#include <memory>

#include "Config.h"
#include "stb_image.h"
#include "Texture.h"
#include "AssetLoader.h"

GameEngineBegin

    extern GameEngineFile::AssetLoader *g_pAssetLoader;

class TextureParser
{
public:
    static SharedTexture Parse(const Buffer &buf)
    {
        unsigned char *data;
        unsigned char *picData = reinterpret_cast<unsigned char *>(buf.m_pData);

        int width, height, nrComponents;
        data = stbi_load_from_memory(picData, buf.m_szSize, &width, &height, &nrComponents, 0);
        if (data)
        {
            SharedTexture image = std::make_shared<Texture>();
            image->Height = height;
            image->Width = width;
            image->data = data;
            image->formate = nrComponents;
            return image;
        }
        return SharedTexture();
    }
    static SharedTexture bindTexture(int format, int width, int height, unsigned char *data)
    {
        data += '\0';
        SharedTexture image = std::make_shared<Texture>();
        image->Height = height;
        image->Width = width;
        image->data = data;
		image->id = -1;
        image->formate = format;
        return image;
    }
};

GameEngineEnd