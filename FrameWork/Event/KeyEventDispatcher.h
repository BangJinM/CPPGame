#pragma once

#include "DataEventDispatcher.h"

namespace EventSystem
{
    struct KeyEventData
    {
        int key;
        int scancode;
        int action;
        int mods;
    };
    
    class KeyEventDispatcher : public DataEventDispatcher<KeyEventData>
    {
    public:
        bool OnEvent(const EventID& eventID, const void* event)
        {
            const KeyEventData* pEvent = reinterpret_cast<const KeyEventData*>(event);
            for (auto listener : listeners)
            {
                listener(event);
            }
            return true;
        }
    };
}  // namespace EventSystem