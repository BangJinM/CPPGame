#include "AssetManager.h"
#include <algorithm>
#include "AssetLoader.h"
#include "TextureParser.h"
namespace GameEngine
{
	extern AssetLoader *g_pAssetLoader;
	int AssetManager::Initialize()
	{
		return 0;
	}

	void AssetManager::Finalize()
	{
		for (auto iter = m_Images.begin(); iter != m_Images.end(); iter++)
		{
			delete iter->second;
		}
		m_Images.clear();
	}

	void AssetManager::Tick()
	{
	}

	void AssetManager::addImage(std::string path, Image *image)
	{
		if (m_Images.find(path) != m_Images.end())
		{
			return;
		}
		m_Images.insert(std::pair<std::string, Image *>(path, image));
	}

	Image *AssetManager::getImage(std::string path)
	{
		auto image = m_Images.find(path);
		if (image == m_Images.end())
		{
			Buffer buffer = g_pAssetLoader->SyncOpenAndReadBinary(path.c_str());
			if (buffer.m_szSize > 0)
			{
				Image *image = TextureParser::Parse(buffer);
				addImage(path, image);
				return getImage(path);
			}
			return nullptr;
		}
		return image->second;
	}
} // namespace GameEngine