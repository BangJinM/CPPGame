#pragma once

#include <string>
#include <vector>

#include "MyMath.h"
#include "cjson/cJSON.h"
namespace GameEngine
{
    class SerializableHelper
    {
    public:
#pragma region SERIALIZATION_HELPERS
        static void Seserialize(cJSON* root, const std::string& p_name, const float value);
        static void Seserialize(cJSON* root, const std::string& p_name, const int value);
        static void Seserialize(cJSON* root, const std::string& p_name, const std::string value);
        static void Seserialize(cJSON* root, const std::string& p_name, const VecterFloat2 value);
        static void Seserialize(cJSON* root, const std::string& p_name, const VecterFloat3 value);
        static void Seserialize(cJSON* root, const std::string& p_name, const VecterFloat4 value);
        static void Seserialize(cJSON* root, const std::string& p_name, const std::vector<std::string> values);
#pragma endregion

#pragma region DESERIALIZATION_HELPERS
        static float DeserializeFloat(cJSON* root, const std::string& p_name);
        static int DeserializeInt(cJSON* root, const std::string& p_name);
        static std::string DeserializeString(cJSON* root, const std::string& p_name);
        static VecterFloat2 DeserializeVecterFloat2(cJSON* root, const std::string& p_name);
        static VecterFloat3 DeserializeVecterFloat3(cJSON* root, const std::string& p_name);
        static VecterFloat4 DeserializeVecterFloat4(cJSON* root, const std::string& p_name);
        static std::vector<std::string> DeserializeVectorString(cJSON* root, const std::string& p_name);
#pragma endregion
    };
}  // namespace GameEngine