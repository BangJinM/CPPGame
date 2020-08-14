#include "AssetManager.h"
#include <algorithm>
#include "AssetLoader.h"
#include "TextureParser.h"
#include "ObjParser.h"
#include "Material.h"
#include "MaterialParser.h"
namespace GameEngine
{
	extern AssetLoader *g_pAssetLoader;
	static std::map<std::string, std::shared_ptr<Object>> g_cache;
	int AssetManager::Initialize()
	{
		return 0;
	}

	void AssetManager::Finalize()
	{
		g_cache.clear();
	}

	void AssetManager::Tick()
	{
	}

	std::shared_ptr<GameObject> AssetManager::LoadGameObject(const std::string &path)
	{
		std::shared_ptr<GameObject> obj;
		// if (g_pAssetLoader->FileExists(path.c_str()))
		// {

		// 	obj = ReadGameObject(ms, std::shared_ptr<GameObject>());
		// }
		return obj;
	}

	std::shared_ptr<Material> AssetManager::LoadMaterial(const std::string &path)
	{
		std::shared_ptr<Material> obj;
		if (g_cache.find(path) != g_cache.end())
		{
			return std::dynamic_pointer_cast<Material>(g_cache[path]);
		}
		obj = MaterialParser::Parse(path);
		if (obj)
			g_cache[path] = obj;
		return obj;
	}

	std::shared_ptr<Mesh> AssetManager::LoadMesh(const std::string &path)
	{
		if (g_cache.find(path) != g_cache.end())
		{
			return std::dynamic_pointer_cast<Mesh>(g_cache[path]);
		}

		std::shared_ptr<Mesh> mesh = ObjParser::Parse(path);
		if (mesh)
			g_cache[path] = mesh;
		return mesh;
	}

	std::shared_ptr<Image> AssetManager::LoadTexture(const std::string &path)
	{
		std::shared_ptr<Image> image;
		if (g_cache.find(path) != g_cache.end())
		{
			return std::dynamic_pointer_cast<Image>(g_cache[path]);
		}
		Buffer buffer = g_pAssetLoader->SyncOpenAndReadBinary(path.c_str());
		if (buffer.m_szSize > 0)
		{
			image = TextureParser::Parse(buffer);
			g_cache[path] = image;
		}
		return image;
	}

} // namespace GameEngine