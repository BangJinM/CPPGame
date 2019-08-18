#ifndef SRC_RENDERERE_MODEL_H__
#define SRC_RENDERERE_MODEL_H__
#include<string>
#include<vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Mesh.h"

using namespace std;
class Model
{
public:
	/*  ����   */
	Model(char* path)
	{
		loadModel(path);
	}
	void Draw(Shader shader);
private:
	/*  ģ������  */
	vector<Mesh> meshes;
	string directory;
	/*  ����   */
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		string typeName);
};

#endif  //SRC_RENDERERE_MODEL_H__
