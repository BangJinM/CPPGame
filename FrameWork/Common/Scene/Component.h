#pragma once

#include <memory>

#include "Config.h"
#include "Object.h"
#include "ClassIDs.h"
#include "ClassIDs.h"

GameEngineBegin 

class GameObject;
class Component : public Object
{
    friend class GameObject;

public:
    ClassIDType getClassID()
    {
        if (m_ClassID > 0)
            return m_ClassID;
        return ClassIDType::CLASS_Undefined;
    }
    ClassIDType m_ClassID = ClassIDType::CLASS_Undefined;

    virtual ~Component()
    {
    }
    Component(ClassIDType classID) : m_ClassID(classID) {}

    void setParent(SharedGameObject host)
    {
        if (m_Parent.lock() != host)
        {
            m_Parent = host;
        }
    }

    SharedGameObject getParent()
    {
        return m_Parent.lock();
    }

public:
    virtual void Start()
    {
        if (m_Started)
            return;
        m_Started = true;
    }
    virtual void Update() {}
    virtual void LateUpdate() {}
    virtual void OnEnable(bool enable) { m_Enable = enable; }
    virtual void InitComponent(SharedGameObject host)
    {
        setParent(host);
    }

public:
    std::weak_ptr<GameObject> m_Parent;   //寄主
    std::weak_ptr<Component> m_Component; //自己

    bool m_Enable = true;
    bool m_Started = false;
};
GameEngineEnd