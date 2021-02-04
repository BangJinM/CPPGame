#include "SerializableHelper.h"

namespace GameEngine
{
    void SerializableHelper::Seserialize(cJSON* root, const std::string& p_name, const float value)
    {
        cJSON_AddNumberToObject(root, p_name.c_str(), value);
    }
    void SerializableHelper::Seserialize(cJSON* root, const std::string& p_name, const int value)
    {
        cJSON_AddNumberToObject(root, p_name.c_str(), value);
    }
    void SerializableHelper::Seserialize(cJSON* root, const std::string& p_name, const std::string value)
    {
        cJSON_AddStringToObject(root, p_name.c_str(), value.c_str());
    }
    void SerializableHelper::Seserialize(cJSON* root, const std::string& p_name, const VecterFloat2 value)
    {
        auto arrayRoot = cJSON_AddArrayToObject(root, p_name.c_str());
        for (auto index = 0; index < 2; ++index)
        {
            cJSON* node = cJSON_CreateNumber(value[index]);
            cJSON_AddItemToArray(arrayRoot, node);
        }
    }
    void SerializableHelper::Seserialize(cJSON* root, const std::string& p_name, const VecterFloat3 value)
    {
        auto arrayRoot = cJSON_AddArrayToObject(root, p_name.c_str());
        for (auto index = 0; index < 3; ++index)
        {
            cJSON* node = cJSON_CreateNumber(value[index]);
            cJSON_AddItemToArray(arrayRoot, node);
        }
    }
    void SerializableHelper::Seserialize(cJSON* root, const std::string& p_name, const VecterFloat4 value)
    {
        auto arrayRoot = cJSON_AddArrayToObject(root, p_name.c_str());
        for (auto index = 0; index < 4; ++index)
        {
            cJSON* node = cJSON_CreateNumber(value[index]);
            cJSON_AddItemToArray(arrayRoot, node);
        }
    }

	void SerializableHelper::Seserialize(cJSON* root, const std::string& p_name, const std::vector<std::string> values) {
		auto arrayRoot = cJSON_AddArrayToObject(root, p_name.c_str());
		for (auto index = 0; index < values.size(); ++index)
		{
			cJSON* node = cJSON_CreateString(values[index].c_str());
			cJSON_AddItemToArray(arrayRoot, node);
		}
	}

    float SerializableHelper::DeserializeFloat(cJSON* root, const std::string& p_name)
    {
        auto paramsNode = cJSON_GetObjectItem(root, p_name.c_str());
        if (paramsNode)
            return paramsNode->valuedouble;
        return 0;
    }
    int SerializableHelper::DeserializeInt(cJSON* root, const std::string& p_name)
    {
        auto paramsNode = cJSON_GetObjectItem(root, p_name.c_str());
        if (paramsNode)
            return paramsNode->valueint;
        return 0;
    }
    std::string SerializableHelper::DeserializeString(cJSON* root, const std::string& p_name)
    {
        auto paramsNode = cJSON_GetObjectItem(root, p_name.c_str());
        if (paramsNode)
            return paramsNode->valuestring;
        return "";
    }
    VecterFloat2 SerializableHelper::DeserializeVecterFloat2(cJSON* root, const std::string& p_name)
    {
        auto paramsNode = cJSON_GetObjectItem(root, p_name.c_str());
        if (paramsNode)
            return VecterFloat2(cJSON_GetArrayItem(paramsNode, 0)->valuedouble, cJSON_GetArrayItem(paramsNode, 1)->valuedouble);
        return VecterFloat2(0, 0);
    }
    VecterFloat3 SerializableHelper::DeserializeVecterFloat3(cJSON* root, const std::string& p_name)
    {
        auto paramsNode = cJSON_GetObjectItem(root, p_name.c_str());
        if (paramsNode)
            return VecterFloat3(cJSON_GetArrayItem(paramsNode, 0)->valuedouble, cJSON_GetArrayItem(paramsNode, 1)->valuedouble, cJSON_GetArrayItem(paramsNode, 2)->valuedouble);
        return VecterFloat3(0, 0, 0);
    }
    VecterFloat4 SerializableHelper::DeserializeVecterFloat4(cJSON* root, const std::string& p_name)
    {
        auto paramsNode = cJSON_GetObjectItem(root, p_name.c_str());
        if (paramsNode)
            return VecterFloat4(cJSON_GetArrayItem(paramsNode, 0)->valuedouble, cJSON_GetArrayItem(paramsNode, 1)->valuedouble, cJSON_GetArrayItem(paramsNode, 2)->valuedouble, cJSON_GetArrayItem(paramsNode, 3)->valuedouble);
        return VecterFloat4(0, 0, 0, 0);
    }

    std::vector<std::string> SerializableHelper::DeserializeVectorString(cJSON* root, const std::string& p_name)
    {
        auto paramsNode = cJSON_GetObjectItem(root, p_name.c_str());
        if (paramsNode)
        {
            auto count = cJSON_GetArraySize(paramsNode);
            std::vector<std::string> vec;
            for (int i = 0; i < count; i++)
            {
                cJSON* item = cJSON_GetArrayItem(paramsNode, i);
                vec.push_back(item->valuestring);
            }
            return vec;
        }
        return std::vector<std::string>();
    }
}  // namespace GameEngine