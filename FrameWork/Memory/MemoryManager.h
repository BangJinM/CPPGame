#pragma once
#include <new>

#include "Allocator.h"
#include "Config.h"
#include "IRuntimeModule.h"

namespace GameEngine
{
    class MemoryManager : public IRuntimeModule
    {
    public:
        template <class T, typename... Arguments>
        T *New(Arguments... parameters)
        {
            return new (Allocate(sizeof(T))) T(parameters...);
        }

        template <class T>
        void Delete(T *p)
        {
            p->~T();
            Free(p, sizeof(T));
        }

    public:
        virtual ~MemoryManager() {}

        virtual int Initialize();
        virtual void Finalize();
        virtual void Tick(float deltaTime);

        void *Allocate(size_t size);
        void *Allocate(size_t size, size_t alignment);
        void Free(void *p, size_t size, size_t alignment);

    private:
        static size_t *m_pBlockSizeLookup;
        static Allocator *m_pAllocators;
        static bool m_bInitialized;

    private:
        static Allocator *LookUpAllocator(size_t size);
    };

    extern MemoryManager *g_pMemoryManager;
}  // namespace GameEngine
