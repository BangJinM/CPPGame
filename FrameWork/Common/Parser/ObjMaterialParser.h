#ifndef GameEngine_Common_Parser_ObjMaterialParser_H
#define GameEngine_Common_Parser_ObjMaterialParser_H

#include <string>

#include "Material.h"
#include "ObjLoader.h"

namespace GameEngine
{
    class ObjMaterialParser
    {
    public:
        Material Parse(std::vector<tinyobj::material_t> materials)
        {
            int i = 0;
            char str[20];
            std::string dir = "";
            for (auto &material : materials)
            {
                NMaterialData materialdata;

                NTextureData tex;
                tex.filename = material.diffuse_texname.empty() ? material.diffuse_texname : dir + material.diffuse_texname;
                tex.type = NTextureData::Usage::Diffuse;
                tex.wrapS = GL_CLAMP_TO_EDGE;
                tex.wrapT = GL_CLAMP_TO_EDGE;

                sprintf(str, "%d", ++i);
                materialdata.textures.push_back(tex);
                materialdata.id = str;
                material.name = str;
            }
			return nullptr;
        }
    };

} // namespace GameEngine

#endif