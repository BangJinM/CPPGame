#pragma once

#include <map>
#include <string>

#include "Config.h"
#include "IParser.h"
namespace GameEngine
{
    enum ParserExtType
    {
        IMAGE = 0,
        OBJ,
        SCENE,
        MTL,
    };

    class ParserManager
    {
        typedef std::map<ParserExtType, IParser*> ParserMap;

    private:
        ParserManager();

    public:
        ~ParserManager();

        static ParserManager* GetInstance();

        ///////////////////////////////////////////////
        //添加解析器
        ///////////////////////////////////////////////
        void AddParser(ParserExtType type, IParser* parser);

        ///////////////////////////////////////////////
        // 删除
        ///////////////////////////////////////////////
        void RemoveParser(ParserExtType type);

        ///////////////////////////////////////////////
        //执行
        ///////////////////////////////////////////////
        SharedObject ExecuteParser(ParserExtType type, std::string path);

    private:
        static ParserManager* _instance;
        ParserMap m_ParserMaps;
    };

    static SharedObject ObjectParser(ParserExtType type, std::string path)
    {
        return ParserManager::GetInstance()->ExecuteParser(type, path);
    }

}  // namespace GameEngine