#pragma once
#include <new>
#include "IRuntimeModule.h"
#include "Allocator.h"

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
        virtual void Tick();

        void *Allocate(size_t size);
        void *Allocate(size_t size, size_t alignment);
        void Free(void *p, size_t size);

    private:
        static size_t *m_pBlockSizeLookup;
        static Allocator *m_pAllocators;

    private:
        static Allocator *LookUpAllocator(size_t size);
    };
} // namespace GameEngine
