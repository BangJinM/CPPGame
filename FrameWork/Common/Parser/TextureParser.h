#ifndef CPPGAME_INTERFACE_TextureParser_H
#define CPPGAME_INTERFACE_TextureParser_H

#include <cstdint>
#include <memory>

#include "stb_image.h"
#include "Image.h"
#include "AssetLoader.h"

#include "glad/glad_wgl.h"
#include "OpenGLDebugger.h"
namespace GameEngine
{
    extern AssetLoader *g_pAssetLoader;

    class TextureParser
    {
    public:
        static std::shared_ptr<Image> Parse(const Buffer &buf)
        {
            unsigned char *data;
            unsigned char *picData = reinterpret_cast<unsigned char *>(buf.m_pData);

            int width, height, nrComponents;
            data = stbi_load_from_memory(picData, buf.m_szSize, &width, &height, &nrComponents, 0);
            if (data)
            {
                GLenum format;
                if (nrComponents == 1)
                    format = GL_RED;
                else if (nrComponents == 3)
                    format = GL_RGB;
                else if (nrComponents == 4)
                    format = GL_RGBA;
                return bindTexture(format, width, height, data);
            }

            return std::shared_ptr<Image>();
        }
        static std::shared_ptr<Image> bindTexture(int format, int width, int height, unsigned char *data)
        {
			data += '\0';
            OpenGLDebugger::glCheckError();
            unsigned int textureID;
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);
            OpenGLDebugger::glCheckError();
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            OpenGLDebugger::glCheckError();
            glGenerateMipmap(GL_TEXTURE_2D);
            OpenGLDebugger::glCheckError();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            OpenGLDebugger::glCheckError();
            std::shared_ptr<Image> image = std::make_shared<Image>();
            image->Height = height;
            image->Width = width;
            image->data = data;
            image->id = textureID;
            return image;
        }
    };

} // namespace GameEngine

#endif