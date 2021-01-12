#include "ParserManager.h"
#include "MaterialParser.h"
#include "SceneParser.h"
#include "TextureParser.h"
GameEngineParserBegin

    int
    ParserManager::Initialize()
{
    AddParser(ParserExtType::MTL, new MaterialParser());
    AddParser(ParserExtType::SCENE, new SceneParser());
    AddParser(ParserExtType::IMAGE, new TextureParser());
    return 1;
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

void ParserManager::Tick() {}

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
    auto pf = m_ParserMaps.find(type);
    if (pf == m_ParserMaps.end())
        return nullptr;
    return pf->second->Parser(path);
}

GameEngineParserEnd
