//
// Copyright 2012-2015, Syoyo Fujita.
//
// Licensed under 2-clause BSD license.
//
//https://github.com/syoyo/tinyobjloader
#ifndef _GameEngine_Common_Scene_OBJ_Parser_H
#define _GameEngine_Common_Scene_OBJ_Parser_H

#include <string>
#include <vector>
#include <map>

#include "ObjLoader.h"
#include "GameObject.h"

namespace GameEngine
{

	

	class ObjParser
	{

	public:
		static void Parse(std::string modelPath, GameObject* gameObject)
		{

			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> materials;
			tinyobj::LoadObj(shapes, materials, modelPath.c_str(), "");

			parserMesh(shapes, materials, gameObject);
		}

		static void parserMesh(std::vector<tinyobj::shape_t> shapes, std::vector<tinyobj::material_t> materials, GameObject *parent)
		{
			for (auto &shape : shapes)
			{
				auto mesh = shape.mesh;
				MeshData *meshdata = new MeshData();
				MeshVertexAttrib attrib;
				attrib.size = 3;
				attrib.type = GL_FLOAT;

				if (mesh.positions.size())
				{
					attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_POSITION;
					attrib.attribSizeBytes = attrib.size * sizeof(float);
					meshdata->attribs.push_back(attrib);
					meshdata->vertexSizeInFloat += 3;
				}
				bool hasnormal = false, hastex = false;
				if (mesh.normals.size())
				{
					hasnormal = true;
					attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_NORMAL;
					attrib.attribSizeBytes = attrib.size * sizeof(float);
					meshdata->attribs.push_back(attrib);
					meshdata->vertexSizeInFloat += 3;
				}
				if (mesh.texcoords.size())
				{
					hastex = true;
					attrib.size = 2;
					attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_TEX_COORD;
					attrib.attribSizeBytes = attrib.size * sizeof(float);
					meshdata->attribs.push_back(attrib);
					meshdata->vertexSizeInFloat += 2;
				}

				auto vertexNum = mesh.positions.size() / 3;
				for (unsigned int k = 0; k < vertexNum; ++k)
				{
					meshdata->vertex.push_back(mesh.positions[k * 3]);
					meshdata->vertex.push_back(mesh.positions[k * 3 + 1]);
					meshdata->vertex.push_back(mesh.positions[k * 3 + 2]);

					if (hasnormal)
					{
						meshdata->vertex.push_back(mesh.normals[k * 3]);
						meshdata->vertex.push_back(mesh.normals[k * 3 + 1]);
						meshdata->vertex.push_back(mesh.normals[k * 3 + 2]);
					}

					if (hastex)
					{
						meshdata->vertex.push_back(mesh.texcoords[k * 2]);
						meshdata->vertex.push_back(mesh.texcoords[k * 2 + 1]);
					}
				}

				std::map<int, std::vector<unsigned short>> subMeshMap;
				meshdata->indices = mesh.indices;
				Mesh *m_Mesh = new Mesh(meshdata);
				parent->m_Meshs.push_back(m_Mesh);
			}
		}

	}; // namespace GameEngine

} // namespace GameEngine

#endif // _TINY_OBJ_LOADER_H
