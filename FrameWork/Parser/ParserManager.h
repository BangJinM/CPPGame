#pragma once

#include <map>
#include <string>

#include "Config.h"
#include "IParser.h"
#include "IRuntimeModule.h"
using namespace std;
namespace GameEngine
{
    enum ParserExtType
    {
        IMAGE = 0,
        OBJ,
        SCENE,
        MTL,
    };

    class ParserManager : public IRuntimeModule
    {
        typedef map<ParserExtType, IParser*> ParserMap;

    public:
        virtual int Initialize() override;
        virtual void Finalize() override;
        virtual void Tick() override;

        void AddParser(ParserExtType type, IParser* parser);
        void RemoveParser(ParserExtType type);
        SharedObject ExecuteParser(ParserExtType type, string path);

    private:
        ParserMap m_ParserMaps;
    };

}  // namespace GameEngine