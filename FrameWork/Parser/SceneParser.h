//
// Copyright 2012-2015, Syoyo Fujita.
//
// Licensed under 2-clause BSD license.
//
//https://github.com/syoyo/tinyobjloader
#pragma once

#include <map>
#include <string>
#include <vector>

#include "AssetLoader.h"
#include "AssetManager.h"
#include "Camera.h"
#include "Config.h"
#include "GameObject.h"
#include "IParser.h"
#include "Light.h"
#include "MeshRenderer.h"
#include "MyMath.h"
#include "Scene.h"
#include "UI/Image.h"
#include "cjson/cJSON.h"

namespace GameEngine
{
    extern AssetLoader *g_pAssetLoader;
    extern AssetManager *g_pAssetManager;
}  // namespace GameEngine

namespace GameEngine
{
    class SceneParser : public IParser
    {
    public:
        virtual SharedObject Parser(const std::string scenePath) override
        {
            SharedScene scene = make_shared<Scene>();
            std::string sceneStr = g_pAssetLoader->SyncOpenAndReadTextFileToString(scenePath.c_str());
            SharedGameObject gameobject = GameObject::createGameObject();
            auto json = cJSON_Parse(sceneStr.c_str());

            for (int i = 0; i < cJSON_GetArraySize(json); i++)  //遍历最外层json键值对
            {
                cJSON *item = cJSON_GetArrayItem(json, i);
                SharedObject object;
                if (cJSON_Object == item->type)  //如果对应键的值仍为cJSON_Object就递归调用printJson
                    object = parser(item);

                auto tempObject = std::dynamic_pointer_cast<GameObject>(object);
                if (tempObject)
                {
                    if (tempObject->GetParentFileID() > 0)
                    {
                        auto parentOject = gameobject->getChildByID(tempObject->GetParentFileID());
                        parentOject->addChild(tempObject);
                    }
                    else
                    {
                        gameobject->addChild(tempObject);
                    }
                }
                else
                {
                    auto tempComponent = std::dynamic_pointer_cast<Component>(object);
                    auto fatherID = tempComponent->GetParentFileID();
                    if (fatherID > 0)
                    {
                        auto parentTemp = gameobject->getChildByID(fatherID);
                        parentTemp->addComponent(tempComponent);
                    }
                }
            }
            auto children = gameobject->getChildren();
            for (auto i = children.begin(); i != children.end(); i++)
            {
                scene->AddGameObject(i->second);
            }
            delete json;
            return scene;
        }

        static vecterFloat3 GetVF3(string name, cJSON *node)
        {
            vecterFloat3 vec3(vecterFloat3(cJSON_GetArrayItem(node, 0)->valuedouble, cJSON_GetArrayItem(node, 1)->valuedouble, cJSON_GetArrayItem(node, 2)->valuedouble));
            return vec3;
        }

        static SharedObject compareGameObject(cJSON *root)
        {
            SharedGameObject gameobject = GameObject::createGameObject();
            auto paramsNode = cJSON_GetObjectItem(root, "name");
            if (paramsNode)
            {
                gameobject->setName(paramsNode->valuestring);
            }
            return gameobject;
        }

        static SharedObject compareTransform(cJSON *root)
        {
            SharePtr<Transform> gameobject = std::make_shared<Transform>();
            auto paramsNode = cJSON_GetObjectItem(root, "scale");
            if (paramsNode)
            {
                gameobject->setScale(GetVF3("scale", paramsNode));
            }
            paramsNode = cJSON_GetObjectItem(root, "position");
            if (paramsNode)
            {
                gameobject->setPosition(GetVF3("position", paramsNode));
            }
            paramsNode = cJSON_GetObjectItem(root, "rotation");
            if (paramsNode)
            {
                gameobject->setRotation(GetVF3("rotation", paramsNode));
            }
            return gameobject;
        }

        static SharedObject compareCamera(cJSON *root)
        {
            SharePtr<Camera> gameobject = std::make_shared<Camera>();
            return gameobject;
        }

        static SharedObject compareMeshRenderer(cJSON *root)
        {
            SharePtr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>();
            auto paramsNode = cJSON_GetObjectItem(root, "m_Materials");
            if (paramsNode)
            {
                auto count = cJSON_GetArraySize(paramsNode);
                for (int i = 0; i < count; i++)
                {
                    cJSON *item = cJSON_GetArrayItem(paramsNode, i);
                    meshRenderer->AddMaterial(g_pAssetManager->LoadMaterial(item->valuestring));
                }
            }
            paramsNode = cJSON_GetObjectItem(root, "m_Mesh");
            if (paramsNode)
            {
                meshRenderer->SetMesh(g_pAssetManager->LoadMesh(paramsNode->valuestring));
            }
            return meshRenderer;
        }

        static SharedObject compareImage(cJSON *root)
        {
            SharePtr<Image> meshRenderer = std::make_shared<Image>();
            auto paramsNode = cJSON_GetObjectItem(root, "Texture");
            if (paramsNode)
            {
                meshRenderer->setTexture(g_pAssetManager->LoadTexture(paramsNode->valuestring));
            }
            return meshRenderer;
        }

        static SharedObject compareLight(cJSON *root)
        {
            SharePtr<Light> light;

            auto typeNode = cJSON_GetObjectItem(root, "Type");
            if (typeNode)
            {
                if (typeNode->valueint == Light::LightType::DirectionalLight)
                    light = make_shared<DirectionalLight>();
                else if (typeNode->valueint == Light::LightType::PointLight)
                    light = make_shared<PointLight>();
                else if (typeNode->valueint == Light::LightType::AreaLight)
                    light = make_shared<AreaLight>();
                else if (typeNode->valueint == Light::LightType::SpotLight)
                    light = make_shared<SpotLight>();
            }
            return light;
        }

        static bool strCompare(const char *str1, const char *str2)
        {
            std::string str = str1;
            return str.compare(str2) == 0;
        }

        static SharedObject parser(cJSON *root)  //以递归的方式打印json的最内层键值对
        {
            static const struct
            {
                const char *name;
                std::function<SharedObject(cJSON *root)> func;
            } attribute_locations[] =
                {
                    {"GameObject", compareGameObject},
                    {"Transform", compareTransform},
                    {"MeshRenderer", compareMeshRenderer},
                    {"Image", compareImage},
                    {"Light", compareLight},
                    {"Camera", compareCamera}};
            const int size = sizeof(attribute_locations) / sizeof(attribute_locations[0]);
            int i = 0;
            SharedObject object;
            auto type = root->string;
            for (size_t i = 0; i < size; i++)
            {
                if (strCompare(type, attribute_locations[i].name))
                {
                    object = attribute_locations[i].func(root);
                    break;
                }
            }

            auto paramsNode = cJSON_GetObjectItem(root, "fileID");
            if (paramsNode && object)
            {
                object->SetFileID(paramsNode->valueint);
            }
            paramsNode = cJSON_GetObjectItem(root, "m_GameObject");
            if (paramsNode && object)
            {
                object->SetParentFileID(paramsNode->valueint);
            }

            return object;
        }

    };  // namespace GameEngine

}  // namespace GameEngine