#pragma once
#include <functional>

#include "EventID.h"

#define EventCallBack std::function<void(const void*)>

namespace EventSystem
{
    class IEventDispatcher
    {
    public:
        virtual bool OnEvent(const EventID& eventID, const void* event) = 0;
        virtual EventID GetCurrentEventID() = 0;
        virtual void AddLitener(EventCallBack& func) = 0;
        virtual void RemoveListener(EventCallBack& func) = 0;
    };  // namespace IEventDispatcher
}  // namespace EventSystem