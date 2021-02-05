
#pragma once

#include <string>

#include "Config.h"
#include "ISerializable.h"
#include "Utils/SerializableHelper.h"

namespace GameEngine
{
    class Object : public ISerializable
    {
    public:
        Object()
        {
            static uint32_t s_id = 0;
            m_id = ++s_id;
            m_FileID = 0;
            m_ParentFileID = 0;
        }
        virtual ~Object() {}

        const std::string& GetName() const { return m_name; }
        void SetName(const std::string& name) { m_name = name; }

        uint32_t GetId() const { return m_id; }
        
        uint32_t GetFileID() const { return m_FileID; }
        void SetFileID(uint32_t fileID) { m_FileID = fileID; }

        uint32_t GetParentFileID() const { return m_ParentFileID; }
        void SetParentFileID(uint32_t fileID) { m_ParentFileID = fileID; }

        virtual void OnSerialize(cJSON* root) override
        {
            SerializableHelper::Seserialize(root, "name", m_name);
            SerializableHelper::Seserialize(root, "fileID", (int)m_FileID);
            SerializableHelper::Seserialize(root, "m_GameObject", (int)m_ParentFileID);
        }
        virtual void OnDeserialize(cJSON* root) override
        {
            m_name = SerializableHelper::DeserializeString(root, "name");
            m_FileID = SerializableHelper::DeserializeInt(root, "fileID");
            m_ParentFileID = SerializableHelper::DeserializeInt(root, "m_GameObject");
        }

    private:
        std::string m_name;
        uint32_t m_id;
        uint32_t m_FileID;
        uint32_t m_ParentFileID;
    };
}  // namespace GameEngine
