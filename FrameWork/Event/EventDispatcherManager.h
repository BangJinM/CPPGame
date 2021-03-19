#pragma once

#include <list>
#include <map>

#include "EventID.h"
#include "IEventDispatcher.h"
#include "IRuntimeModule.h"
#include "KeyEventDispatcher.h"

namespace EventSystem
{
    class EventDispatcherManager : public GameEngine::IRuntimeModule
    {
    public:
        virtual int Initialize()
        {
            AddDispatcher(new KeyEventDispatcher());
            return 0;
        }
        virtual void Finalize() {}
        virtual void Tick(float deltaTime)
        {
            if (eventDataList.size() > 0)
            {
                for (auto eventData : eventDataList)
                {
                    SendEventImp(eventData.id, eventData.data);
                }
                eventDataList.clear();
            }
        }

        template <typename EventType>
        void SendEvent(const EventType* event)
        {
            EventItemData data;
            data.id = GetEventID<EventType>();
            data.data = event;
            eventDataList.push_back(data);
        }

        void AddDispatcher(IEventDispatcher* listener)
        {
            auto find = eventListenerMap.find(listener->GetCurrentEventID());
            if (find != eventListenerMap.end())
            {
                return;
            }
            eventListenerMap[listener->GetCurrentEventID()] = listener;
        }
        void RemoveDispatcher(IEventDispatcher* listener)
        {
            auto find = eventListenerMap.find(listener->GetCurrentEventID());
            if (find != eventListenerMap.end())
            {
                eventListenerMap.erase(listener->GetCurrentEventID());
            }
        }
        template <typename EventType>
        void AddEventListener(EventCallBack& func)
        {
            auto find = eventListenerMap.find(GetEventID<EventType>());
            if (find != eventListenerMap.end())
            {
                find->second->AddLitener(func);
            }
        }

        template <typename EventType>
        void RemoveListener(void* func)
        {
            auto find = eventListenerMap.find(GetEventID<EventType>());
            if (find != eventListenerMap.end())
            {
                find->second->AddLitener(func);
            }
        }

        template <typename EventType>
        bool SendEventImp(const EventType* pEvent)
        {
            return SendEventImp(GetEventID<EventType>(), pEvent);
        }

    private:
        bool SendEventImp(const EventID& eventID, const void* event)
        {
            auto find = eventListenerMap.find(eventID);
            if (find != eventListenerMap.end())
            {
                find->second->OnEvent(eventID, event);
            }
            return true;
        }

    private:
        struct EventItemData
        {
            EventID id;
            const void* data;
        };

        std::map<EventID, IEventDispatcher*> eventListenerMap;
        std::list<EventItemData> eventDataList;
    };
    extern EventDispatcherManager* g_pEventDispatcherManager;
}  // namespace EventSystem