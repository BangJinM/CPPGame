#include "Scene.h"
#include "Mesh.h"

//һ�²���
#include "ObjParser.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Camera.h"
#include "GameObject.h"
#include "Shader.h"
#include "AssetLoader.h"
#include "TextureParser.h"

namespace GameEngine
{
	extern AssetLoader *g_pAssetLoader;

	Scene::Scene()
	{
		Camera *camera = new Camera();

		std::string vert = g_pAssetLoader->SyncOpenAndReadTextFileToString("Shaders/default.vert");
		std::string flag = g_pAssetLoader->SyncOpenAndReadTextFileToString("Shaders/default.flag");
		Shader shader(vert, flag);

		int width, height, nrChannels;
		unsigned char *data;
		auto image = TextureParser::getTextureByPath("Textures/arm_dif.png");
		gameobject = ObjParser::Parse("Scene/model.obj", "Materials/");
	}

	Scene::~Scene()
	{
	}

	GameObject *Scene::getFirstGameObject()
	{
		return gameobject;
	}

	void Scene::Draw()
	{
		gameobject->Draw();
	}
} // namespace GameEngine