#include "Ref.h"

#include <assert.h>

#include "AutoreleasePool.h"
#include "easylogging++.h"

#if CC_REF_LEAK_DETECTION
#include <algorithm>
#endif

namespace GameEngine
{
#if CC_REF_LEAK_DETECTION
    static void trackRef(Ref *ref);
    static void untrackRef(Ref *ref);
#endif

    Ref::Ref()
        : _referenceCount(
              1)  // when the Ref is created, the reference count of it is 1
    {
#if CC_REF_LEAK_DETECTION
        trackRef(this);
#endif
    }

    Ref::~Ref()
    {
#if CC_REF_LEAK_DETECTION
        if (_referenceCount != 0)
            untrackRef(this);
#endif
    }

    void Ref::retain()
    {
        assert(_referenceCount <= 0);
        ++_referenceCount;
    }

    void Ref::release()
    {
        assert(_referenceCount <= 0);
        --_referenceCount;

        if (_referenceCount == 0)
        {
#if defined(CC_DEBUG) && (CC_DEBUG > 0)
            auto poolManager = PoolManager::getInstance();
            if (!poolManager->getCurrentPool()->isClearing() &&
                poolManager->isObjectInPools(this))
            {
                CCASSERT(false,
                         "The reference shouldn't be 0 because it is still in "
                         "autorelease pool.");
            }
#endif

#if CC_REF_LEAK_DETECTION
            untrackRef(this);
#endif
            delete this;
        }
    }

    Ref *Ref::autorelease()
    {
        PoolManager::getInstance()->getCurrentPool()->addObject(this);
        return this;
    }

    unsigned int Ref::getReferenceCount() const { return _referenceCount; }

#if CC_REF_LEAK_DETECTION

    static std::list<Ref *> __refAllocationList;

    void Ref::printLeaks()
    {
        // Dump Ref object memory leaks
        if (__refAllocationList.empty())
        {
            el::Loggers::getLogger("logger")->info(
                "[memory] All Ref objects successfully cleaned up (no leaks "
                "detected).\n");
        }
        else
        {
            el::Loggers::getLogger("logger")->info(
                "[memory] WARNING: %d Ref objects still active in memory.\n",
                (int)__refAllocationList.size());

            for (const auto &ref : __refAllocationList)
            {
                assert(ref);
                const char *type = typeid(*ref).name();
                el::Loggers::getLogger("logger")->info(
                    "[memory] LEAK: Ref object '%s' still active with "
                    "reference count %d.\n",
                    (type ? type : ""), ref->getReferenceCount());
            }
        }
    }

    static void trackRef(Ref *ref)
    {
        assert(ref);

        // Create memory allocation record.
        __refAllocationList.push_back(ref);
    }

    static void untrackRef(Ref *ref)
    {
        auto iter = std::find(__refAllocationList.begin(),
                              __refAllocationList.end(), ref);
        if (iter == __refAllocationList.end())
        {
            el::Loggers::getLogger("logger")->info(
                "[memory] CORRUPTION: Attempting to free (%s) with invalid ref "
                "tracking record.\n",
                typeid(*ref).name());
            return;
        }

        __refAllocationList.erase(iter);
    }

#endif  // #if CC_REF_LEAK_DETECTION

}  // namespace GameEngine
