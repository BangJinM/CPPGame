#ifndef CPPGAME_INTERFACE_TextureParser_H
#define CPPGAME_INTERFACE_TextureParser_H

#include <cstdint>

#include "stb_image.h"
#include "Image.h"
#include "AssetLoader.h"

#include "glad/glad_wgl.h"

namespace GameEngine
{
    extern AssetLoader *g_pAssetLoader;

    class TextureParser
    {
    public:
        static Image* Parse(const Buffer &buf)
        {
            int width, height, nrChannels;
            unsigned char *data;
            unsigned char *picData = reinterpret_cast<unsigned char *>(buf.m_pData);
            data = stbi_load_from_memory(picData, buf.m_szSize, &width, &height, &nrChannels, 0);

            if (data)
            {
                Image *image = new Image();
                image->Height = height;
                image->Width = width;
                image->data = new char[nrChannels + 1];
                image->data[nrChannels] = '\0';
                memcpy(image->data, data, nrChannels);
                stbi_image_free(data);
                return image;
            }
            return nullptr;
        }
    };

} // namespace GameEngine

#endif