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
		static std::vector<std::shared_ptr<Mesh>> Parse(std::string modelPath)
		{
			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> materials;
			tinyobj::LoadObj(shapes, materials, modelPath.c_str(), "");

			return parserMesh(shapes, materials);
		}

		static std::vector<std::shared_ptr<Mesh>>  parserMesh(std::vector<tinyobj::shape_t> shapes, std::vector<tinyobj::material_t> materials)
		{
			std::vector<std::shared_ptr<Mesh>> meshs;
			for (auto &shape : shapes)
			{
				std::shared_ptr<Mesh> m_Mesh = std::make_shared<Mesh>();
				auto mesh = shape.mesh;
				MeshVertexAttrib attrib;
				attrib.size = 3;
				attrib.type = GL_FLOAT;

				if (mesh.positions.size())
				{
					attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_POSITION;
					attrib.attribSizeBytes = attrib.size * sizeof(float);
					m_Mesh->attribs.push_back(attrib);
					m_Mesh->vertexSizeInFloat += 3;
				}
				bool hasnormal = false, hastex = false;
				if (mesh.normals.size())
				{
					hasnormal = true;
					attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_NORMAL;
					attrib.attribSizeBytes = attrib.size * sizeof(float);
					m_Mesh->attribs.push_back(attrib);
					m_Mesh->vertexSizeInFloat += 3;
				}
				if (mesh.texcoords.size())
				{
					hastex = true;
					attrib.size = 2;
					attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_TEX_COORD;
					attrib.attribSizeBytes = attrib.size * sizeof(float);
					m_Mesh->attribs.push_back(attrib);
					m_Mesh->vertexSizeInFloat += 2;
				}

				auto vertexNum = mesh.positions.size() / 3;
				for (unsigned int k = 0; k < vertexNum; ++k)
				{
					m_Mesh->vertex.push_back(mesh.positions[k * 3]);
					m_Mesh->vertex.push_back(mesh.positions[k * 3 + 1]);
					m_Mesh->vertex.push_back(mesh.positions[k * 3 + 2]);

					if (hasnormal)
					{
						m_Mesh->vertex.push_back(mesh.normals[k * 3]);
						m_Mesh->vertex.push_back(mesh.normals[k * 3 + 1]);
						m_Mesh->vertex.push_back(mesh.normals[k * 3 + 2]);
					}

					if (hastex)
					{
						m_Mesh->vertex.push_back(mesh.texcoords[k * 2]);
						m_Mesh->vertex.push_back(mesh.texcoords[k * 2 + 1]);
					}
				}

				m_Mesh->indices = mesh.indices;
				m_Mesh->setupMesh();
				meshs.push_back(m_Mesh);
			}
			return meshs;
		}

	}; // namespace GameEngine

} // namespace GameEngine

#endif // _TINY_OBJ_LOADER_H
