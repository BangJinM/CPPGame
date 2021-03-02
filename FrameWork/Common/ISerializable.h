
#pragma once
#include "cjson/cJSON.h"
namespace GameEngine
{
    class ISerializable
    {
    public:
        ///////////////////////////////////
        //序列化
        // @param root 根节点
        ///////////////////////////////////
        virtual void OnSerialize(cJSON *root) = 0;

        ///////////////////////////////////
        //反序列化
        // @param root 根节点
        ///////////////////////////////////
        virtual void OnDeserialize(cJSON *root) = 0;
    };
}  // namespace GameEngine