SET(FRAMEWORK_MEMORY_HEADER 
Memory/Allocator.h
Memory/MemoryManager.h
Memory/Buffer.h
)

SET(FRAMEWORK_MEMORY_SRC 
Memory/Allocator.cpp
Memory/MemoryManager.cpp
)

list(APPEND FRAMEWORK_HEADER ${FRAMEWORK_MEMORY_HEADER})
list(APPEND FRAMEWORK_SRC ${FRAMEWORK_MEMORY_SRC})


