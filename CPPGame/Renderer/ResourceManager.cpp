#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL.h>


// Instantiate static variables
std::map<std::string, Texture2D>			ResourceManager::Textures;
std::map<std::string, Shader>				ResourceManager::Shaders;
std::map<std::string, std::string>			ResourceManager::ShaderFiles;


Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}

Shader* ResourceManager::GetShader(std::string name)
{
	return &Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha)
{
	if(Textures.find(file) == Textures.end())
		Textures[file] = loadTextureFromFile(file, alpha);
	return Textures[file];
}

Texture2D* ResourceManager::GetTexture(std::string name)
{
	return &Textures[name];
}

void ResourceManager::Clear()
{
	// (Properly) delete all shaders	
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);
	// (Properly) delete all textures
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
	Shaders.clear();
	Textures.clear();
	ShaderFiles.clear();
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
	const GLchar *vShaderCode = "";
	const GLchar *fShaderCode = "";
	const GLchar *gShaderCode = "";
	vShaderCode = loadShaderFile(vShaderFile);
	fShaderCode = loadShaderFile(fShaderFile);
	gShaderCode = loadShaderFile(gShaderFile);
	// 2. Now create shader object from source code
	Shader shader ;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

const GLchar * ResourceManager::loadShaderFile(const GLchar *file) {
	if (file == nullptr)
		return nullptr;
	if (ShaderFiles.find(file) == ShaderFiles.end()) {
		std::string code;
		try
		{
			// Open files
			std::ifstream codeFile(file);
			std::stringstream stream;
			stream << codeFile.rdbuf();
			code = stream.str();
		}
		catch (std::exception e)
		{
			std::cout << "ERROR::SHADER: Failed to read shader files:"<< file << std::endl;
		}
		ShaderFiles[file] = code;
	}
	return ShaderFiles[file].c_str();
}


Texture2D ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
	// Create Texture object
	Texture2D texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	// Load image
	int width, height;
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	// Now generate texture
	texture.Generate(width, height, image);
	// And finally free image data
	SOIL_free_image_data(image);
	return texture;
}