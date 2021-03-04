#pragma once

#include <string>

#include "Buffer.h"
#include "Object.h"


using namespace GameEngine;
namespace GameEngine
{
    class IParser
    {
    public:
        virtual SharedObject Parser(const std::string path) { return nullptr; }
    };
}  // namespace GameEngine