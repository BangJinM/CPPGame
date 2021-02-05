
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
        }
        virtual ~Object() {}

        uint32_t GetID() const { return m_id; }

        virtual void OnSerialize(cJSON* root) override
        {
        }
        virtual void OnDeserialize(cJSON* root) override
        {
        }

    private:
        uint32_t m_id;
    };
}  // namespace GameEngine
