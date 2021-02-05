#include "ParserManager.h"

#include "MaterialParser.h"
#include "ObjParser.h"
#include "TextureParser.h"
#include "easylogging++.h"
namespace GameEngine
{
    int
    ParserManager::Initialize()
    {
        AddParser(ParserExtType::MTL, new MaterialParser());
        AddParser(ParserExtType::IMAGE, new TextureParser());
        AddParser(ParserExtType::OBJ, new ObjParser());
        return 0;
    }

    void ParserManager::Finalize()
    {
        ParserMap::iterator iter = m_ParserMaps.begin();

        while (iter != m_ParserMaps.end())
        {
            delete iter->second;
            iter->second = nullptr;
            iter = m_ParserMaps.erase(iter);
        }

        m_ParserMaps.clear();
    }

    void ParserManager::Tick(float deltaTime) {}

    void ParserManager::AddParser(ParserExtType type, IParser *parser)
    {
        m_ParserMaps[type] = parser;
    }

    void ParserManager::RemoveParser(ParserExtType type)
    {
        auto pf = m_ParserMaps.find(type);
        if (pf != m_ParserMaps.end())
        {
            m_ParserMaps.erase(type);
            return;
        }
        return;
    }

    SharedObject ParserManager::ExecuteParser(ParserExtType type, string path)
    {
        LOG(INFO) << "ExecuteParser   type:" << type << "      path:" << path;
        auto pf = m_ParserMaps.find(type);
        if (pf == m_ParserMaps.end())
            return nullptr;
        return pf->second->Parser(path);
    }

}  // namespace GameEngine
