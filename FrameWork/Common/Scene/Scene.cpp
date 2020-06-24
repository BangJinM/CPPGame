#include "Scene.h"
#include "Mesh.h"

//һ�²���
#include "ObjParser.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Camera.h"
#include "GameObject.h"
#include "Shader.h"
#include "ObjMaterialParser.h"
#include "stb_image.h"
#include "AssetLoader.h"

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

		//int width, height, nrChannels;
		Buffer buffer = g_pAssetLoader->SyncOpenAndReadBinary("Textures/arm_dif.png");
		unsigned char *picData = reinterpret_cast<unsigned char *>(buffer.m_pData);
		data = stbi_load_from_memory(picData, buffer.m_szSize, &width, &height, &nrChannels, 0);

		Material material = Material(&shader);

		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		tinyobj::LoadObj(shapes, materials, "Scene/model.obj", "Materials/");
		ObjParser parser;
		gameobject = parser.Parse(shapes);
		gameobject->addComponent(&material);
		ObjMaterialParser omp;
		omp.Parse(materials);
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