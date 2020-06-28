#ifndef CPPGAME_INTERFACE_TextureParser_H
#define CPPGAME_INTERFACE_TextureParser_H


#include <cstdint>
#include "ImageParser.h"
#include "stb_image.h"

namespace GameEngine
{
    class TextureParser : public ImageParser
    {
    private:
        /* data */
    public:
        virtual Image Parse(const Buffer &buf)
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
    };

} // namespace GameEngine

#endif