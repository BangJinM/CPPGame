#pragma once
#include <cstdint>
#include <memory>

#include "AssetLoader.h"
#include "Config.h"
#include "IParser.h"
#include "Texture.h"
#include "stb_image.h"

namespace GameEngine
{
    extern AssetLoader *g_pAssetLoader;

    class TextureParser : public IParser
    {
    public:
        virtual SharedObject Parser(const std::string path) override
        {
            unsigned char *data;
            Buffer buffer = g_pAssetLoader->SyncOpenAndReadBinary(path.c_str());
            unsigned char *picData = reinterpret_cast<unsigned char *>(buffer.GetData());

            int width, height, nrComponents;
            data = stbi_load_from_memory(picData, buffer.GetDataSize(), &width, &height, &nrComponents, 0);
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
    };
}  // namespace GameEngine