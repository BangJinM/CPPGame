#include "Allocator.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

namespace GameEngine
{
    Allocator::Allocator()
        : m_pPageList(nullptr), m_pFreeList(nullptr), m_szDataSize(0), m_szPageSize(0), m_szAlignmentSize(0), m_szBlockSize(0), m_nBlocksPerPage(0)
    {
    }

    Allocator::Allocator(size_t data_size, size_t page_size, size_t alignment)
        : m_pPageList(nullptr), m_pFreeList(nullptr)
    {
        Reset(data_size, page_size, alignment);
    }

    Allocator::~Allocator()
    {
        FreeAll();
    }

    void Allocator::Reset(size_t data_size, size_t page_size, size_t alignment)
    {
        FreeAll();

        m_szDataSize = data_size;
        m_szPageSize = page_size;

        size_t minimal_size = (sizeof(BlockHeader) > m_szDataSize) ? sizeof(BlockHeader) : m_szDataSize;
        // this magic only works when alignment is 2^n, which should general be the case
        // because most CPU/GPU also requires the aligment be in 2^n
        // but still we use a assert to guarantee it
#if defined(_DEBUG)
        assert(alignment > 0 && ((alignment & (alignment - 1))) == 0);
#endif
        m_szBlockSize = ALIGN(minimal_size, alignment);

        m_szAlignmentSize = m_szBlockSize - minimal_size;

        m_nBlocksPerPage = (m_szPageSize - sizeof(PageHeader)) / m_szBlockSize;
    }

    void *Allocator::Allocate()
    {
        if (!m_pFreeList)
        {
            // allocate a new page
            PageHeader *pNewPage = reinterpret_cast<PageHeader *>(new uint8_t[m_szPageSize]);
            ++m_nPages;
            m_nBlocks += m_nBlocksPerPage;
            m_nFreeBlocks += m_nBlocksPerPage;

            if (m_pPageList)
            {
                pNewPage->pNext = m_pPageList;
            }
            else
            {
                pNewPage->pNext = nullptr;
            }

            m_pPageList = pNewPage;

            BlockHeader *pBlock = pNewPage->Blocks();
            // link each block in the page
            for (uint32_t i = 0; i < m_nBlocksPerPage - 1; i++)
            {
                pBlock->pNext = NextBlock(pBlock);
                pBlock = NextBlock(pBlock);
            }
            pBlock->pNext = nullptr;

            m_pFreeList = pNewPage->Blocks();
        }

        BlockHeader *freeBlock = m_pFreeList;
        m_pFreeList = m_pFreeList->pNext;
        --m_nFreeBlocks;

        return reinterpret_cast<void *>(freeBlock);
    }

    void Allocator::Free(void *p)
    {
        BlockHeader *block = reinterpret_cast<BlockHeader *>(p);

        block->pNext = m_pFreeList;
        m_pFreeList = block;
        ++m_nFreeBlocks;
    }

    void Allocator::FreeAll()
    {
        PageHeader *pPage = m_pPageList;
        while (pPage)
        {
            PageHeader *_p = pPage;
            pPage = pPage->pNext;

            delete[] reinterpret_cast<uint8_t *>(_p);
        }

        m_pPageList = nullptr;
        m_pFreeList = nullptr;

        m_nPages = 0;
        m_nBlocks = 0;
        m_nFreeBlocks = 0;
    }

    BlockHeader *Allocator::NextBlock(BlockHeader *pBlock)
    {
        return reinterpret_cast<BlockHeader *>(reinterpret_cast<uint8_t *>(pBlock) + m_szBlockSize);
    }
}  // namespace GameEngine
