#pragma once
#include <functional>
#include <vector>

#include "EventID.h"
#include "IEventDispatcher.h"
namespace EventSystem
{
    template <typename EventType>
    class DataEventDispatcher : public IEventDispatcher
    {
    public:
        DataEventDispatcher() : IEventDispatcher() {}

        virtual EventID GetCurrentEventID() override
        {
            return GetEventID<EventType>();
        }

        virtual void AddLitener(EventCallBack& func) override
        {
            listeners.push_back(func);
        }
        virtual void RemoveListener(EventCallBack& func) override
        {
            // listeners.remove(func);
        }

    protected:
        std::vector<std::function<void(const void*)>> listeners;
    };
}  // namespace EventSystem