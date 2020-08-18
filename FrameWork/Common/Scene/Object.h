
#pragma once

#include <string>

namespace GameEngine
{
    class Object
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
        const std::string &GetName() const { return m_name; }
        void SetName(const std::string &name) { m_name = name; }
        uint32_t GetId() const { return m_id; }
        uint32_t GetFileID() const { return m_FileID; }
        void SetFileID(uint32_t fileID) { m_FileID = fileID; }

        uint32_t GetParentFileID() const { return m_ParentFileID; }
        void SetParentFileID(uint32_t fileID) { m_ParentFileID = fileID; }

    private:
        std::string m_name;
        uint32_t m_id;
        uint32_t m_FileID;
        uint32_t m_ParentFileID;
    };
} // namespace GameEngine
