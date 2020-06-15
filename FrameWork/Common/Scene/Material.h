#ifndef CPPGAME_Common_Scene_Material_H
#define CPPGAME_Common_Scene_Material_H

#include <string>
#include "MyMath.h"
#include "Component.h"
#include <map>
#include "MyMath.h"
#include <vector>
#include <string>

namespace GameEngine
{

    struct material_t
    {
        material_t()
        {
            name = "";
            ambient_texname = "";
            diffuse_texname = "";
            specular_texname = "";
            normal_texname = "";
            ambient = vecterFloat3();
            diffuse = vecterFloat3();
            specular = vecterFloat3();
            transmittance = vecterFloat3();
            emission = vecterFloat3();
            illum = 0;
            dissolve = 1.f;
            shininess = 1.f;
            ior = 1.f;
            unknown_parameter.clear();
        }
        ~material_t() {}

        std::string name;
        vecterFloat3 ambient;
        vecterFloat3 diffuse;
        vecterFloat3 specular;
        vecterFloat3 transmittance;
        vecterFloat3 emission;
        float shininess;
        float ior;      // index of refraction
        float dissolve; // 1 == opaque; 0 == fully transparent
        // illumination model (see http://www.fileformat.info/format/material/)
        int illum;

        std::string ambient_texname;
        std::string diffuse_texname;
        std::string specular_texname;
        std::string normal_texname;
        std::map<std::string, std::string> unknown_parameter;
    };
} // namespace GameEngine

#endif //MAENGINE_IAPPLICATION_H
