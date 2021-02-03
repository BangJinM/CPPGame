
#pragma once
#include "cjson/cJSON.h"
namespace GameEngine
{
    class ISerializable
    {
    public:
        virtual void OnSerialize(cJSON *root) = 0;
        virtual void OnDeserialize(cJSON *root) = 0;
    };
}  // namespace GameEngine