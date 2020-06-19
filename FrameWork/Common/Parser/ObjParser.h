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

#include "ISceneParser.h"

namespace GameEngine
{

	class ObjParser : public ISceneParser
	{

	public:
		virtual std::unique_ptr<GameObject> Parse(std::vector<tinyobj::shape_t> shapes)
		{
			parserMesh(shapes);
			return std::unique_ptr<GameObject>();
		}

		void parserMesh(std::vector<tinyobj::shape_t> shapes)
		{
			for (auto &shape : shapes)
			{
				auto mesh = shape.mesh;
				MeshData *meshdata = new (std::nothrow) MeshData();
				MeshVertexAttrib attrib;
				attrib.size = 3;
				attrib.type = GL_FLOAT;

				if (mesh.positions.size())
				{
					attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_POSITION;
					attrib.attribSizeBytes = attrib.size * sizeof(float);
					meshdata->attribs.push_back(attrib);
				}
				bool hasnormal = false, hastex = false;
				if (mesh.normals.size())
				{
					hasnormal = true;
					attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_NORMAL;
					attrib.attribSizeBytes = attrib.size * sizeof(float);
					meshdata->attribs.push_back(attrib);
				}
				if (mesh.texcoords.size())
				{
					hastex = true;
					attrib.size = 2;
					attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_TEX_COORD;
					attrib.attribSizeBytes = attrib.size * sizeof(float);
					meshdata->attribs.push_back(attrib);
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

				//split into submesh according to material
				std::map<int, std::vector<unsigned short>> subMeshMap;
				for (size_t k = 0, size = mesh.material_ids.size(); k < size; ++k)
				{
					int id = mesh.material_ids[k];
					size_t idx = k * 3;
					subMeshMap[id].push_back(mesh.indices[idx]);
					subMeshMap[id].push_back(mesh.indices[idx + 1]);
					subMeshMap[id].push_back(mesh.indices[idx + 2]);
				}

				auto node = std::unique_ptr<GameObject>();
				//node->setName(shape.name);
			}
		}
	}; // namespace GameEngine
} // namespace GameEngine

#endif // _TINY_OBJ_LOADER_H
