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
#include "easylogging++.h"

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
                else if(object)
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

        static bool strCompare(const char *str1, const char *str2)
        {
            std::string str = str1;
            return str.compare(str2) == 0;
        }

        static SharedObject parser(cJSON *root)  //以递归的方式打印json的最内层键值对
        {
            SharedObject object = nullptr;
            auto type = root->string;

            if (strCompare(type, "Transform"))
            {
                object = make_shared<Transform>();
                object->OnDeserialize(root);
            }
            //else if (strCompare(type, "Image"))
            //{
            //    object = make_shared<Image>();
            //    object->OnDeserialize(root);
            //}
            //else if (strCompare(type, "Light"))
            //{
            //    object = make_shared<Light>();
            //    object->OnDeserialize(root);
            //}
            else if (strCompare(type, "Camera"))
            {
                object = make_shared<Camera>();
                object->OnDeserialize(root);
            }
            else if (strCompare(type, "MeshRenderer"))
            {
                object = make_shared<MeshRenderer>();
                object->OnDeserialize(root);
            }
            else if (strCompare(type, "GameObject"))
            {
                object = GameObject::createGameObject();
                object->OnDeserialize(root);
            }
            else
            {
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
            }

            return object;
        }

    };  // namespace GameEngine

}  // namespace GameEngine