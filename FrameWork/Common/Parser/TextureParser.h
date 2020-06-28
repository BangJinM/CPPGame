#ifndef CPPGAME_INTERFACE_TextureParser_H
#define CPPGAME_INTERFACE_TextureParser_H


#include <cstdint>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Image.h"
#include "AssetLoader.h"

namespace GameEngine
{
    extern AssetLoader *g_pAssetLoader;

    class TextureParser 
    {
    public:
        static Image Parse(const Buffer &buf)
        {
            int width, height, nrChannels;
            unsigned char *data;
            unsigned char *picData = reinterpret_cast<unsigned char *>(buf.m_pData);
            data = stbi_load_from_memory(picData, buf.m_szSize, &width, &height, &nrChannels, 0);
            Image image;
            image.Width = width;
            image.Height = height;
            image.data_size = buf.m_szSize;
            image.data = data;
            return image;
        }

        static Image getTextureByPath(std::string path){
			auto buf = g_pAssetLoader->SyncOpenAndReadBinary(path.c_str());
            return Parse(buf);
		}
    };

} // namespace GameEngine

#endif