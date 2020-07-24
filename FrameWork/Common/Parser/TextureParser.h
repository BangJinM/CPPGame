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
        static Image *Parse(const Buffer &buf)
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
                image->id = getTextureID(image);
                stbi_image_free(data);
                return image;
            }
            return nullptr;
        }

        static int getTextureID(Image *image)
        {
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            // Ϊ��ǰ�󶨵������������û��ơ����˷�ʽ
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            if (image)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->Width, image->Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                printf("Failed to load texture");
            }
            return texture;
        }
    };

} // namespace GameEngine

#endif