//
// Copyright 2012-2015, Syoyo Fujita.
//
// Licensed under 2-clause BSD license.
//
//https://github.com/syoyo/tinyobjloader
#ifndef _GameEngine_Common_Scene_OBJ_LOADER_H
#define _GameEngine_Common_Scene_OBJ_LOADER_H

#include <string>
#include <vector>
#include <map>

#include "ObjMaterialLoader.h"
#include "ISceneParser.h"
#include "Mesh.h"
#include "ObjUtils.h"

using namespace GameEngine;

namespace tinyobj
{
#define TINYOBJ_SSCANF_BUFFER_SIZE (4096)

	static unsigned int updateVertex(std::map<vertex_index, unsigned int> &vertexCache,
		std::vector<float> &positions, std::vector<float> &normals,
		std::vector<float> &texcoords,
		const std::vector<float> &in_positions,
		const std::vector<float> &in_normals,
		const std::vector<float> &in_texcoords, const vertex_index &i)
	{
		const std::map<vertex_index, unsigned int>::iterator it = vertexCache.find(i);

		if (it != vertexCache.end())
		{
			// found cache
			return it->second;
		}

		assert(in_positions.size() > (unsigned int)(3 * i.v_idx + 2));

		positions.push_back(in_positions[3 * i.v_idx + 0]);
		positions.push_back(in_positions[3 * i.v_idx + 1]);
		positions.push_back(in_positions[3 * i.v_idx + 2]);

		if (i.vn_idx >= 0)
		{
			normals.push_back(in_normals[3 * i.vn_idx + 0]);
			normals.push_back(in_normals[3 * i.vn_idx + 1]);
			normals.push_back(in_normals[3 * i.vn_idx + 2]);
		}

		if (i.vt_idx >= 0)
		{
			texcoords.push_back(in_texcoords[2 * i.vt_idx + 0]);
			texcoords.push_back(in_texcoords[2 * i.vt_idx + 1]);
		}

		unsigned int idx = static_cast<unsigned int>(positions.size() / 3 - 1);
		vertexCache[i] = idx;

		return idx;
	}

	static bool exportFaceGroupToShape(
		shape_t &shape, std::map<vertex_index, unsigned int> vertexCache,
		const std::vector<float> &in_positions,
		const std::vector<float> &in_normals,
		const std::vector<float> &in_texcoords,
		const std::vector<std::vector<vertex_index>> &faceGroup,
		const int material_id, const std::string &name, bool clearCache)
	{
		if (faceGroup.empty())
		{
			return false;
		}

		// Flatten vertices and indices
		for (size_t i = 0, size = faceGroup.size(); i < size; ++i)
		{
			const std::vector<vertex_index> &face = faceGroup[i];

			vertex_index i0 = face[0];
			vertex_index i1(-1);
			vertex_index i2 = face[1];

			size_t npolys = face.size();

			// Polygon -> triangle fan conversion
			for (size_t k = 2; k < npolys; k++)
			{
				i1 = i2;
				i2 = face[k];

				unsigned int v0 = updateVertex(
					vertexCache, shape.mesh.positions, shape.mesh.normals,
					shape.mesh.texcoords, in_positions, in_normals, in_texcoords, i0);
				unsigned int v1 = updateVertex(
					vertexCache, shape.mesh.positions, shape.mesh.normals,
					shape.mesh.texcoords, in_positions, in_normals, in_texcoords, i1);
				unsigned int v2 = updateVertex(
					vertexCache, shape.mesh.positions, shape.mesh.normals,
					shape.mesh.texcoords, in_positions, in_normals, in_texcoords, i2);

				shape.mesh.indices.push_back(v0);
				shape.mesh.indices.push_back(v1);
				shape.mesh.indices.push_back(v2);
				if (material_id >= 0)
					shape.mesh.material_ids.push_back(material_id);
			}
		}

		shape.name = name;

		if (clearCache)
			vertexCache.clear();

		return true;
	}

	std::string LoadObj(std::vector<shape_t> &shapes,
		std::vector<material_t> &materials, // [output]
		std::istream &inStream, MaterialReader &readMatFn)
	{
		std::stringstream err;

		std::vector<float> v;
		std::vector<float> vn;
		std::vector<float> vt;
		std::vector<std::vector<vertex_index>> faceGroup;
		std::string name;

		// material
		std::map<std::string, int> material_map;
		std::map<vertex_index, unsigned int> vertexCache;
		int material = -1;

		shape_t shape;

		int maxchars = 8192;             // Alloc enough size.
		std::vector<char> buf(maxchars); // Alloc enough size.
		while (inStream.peek() != -1)
		{
			inStream.getline(&buf[0], maxchars);

			std::string linebuf(&buf[0]);

			// Trim newline '\r\n' or '\n'
			if (linebuf.size() > 0)
			{
				if (linebuf[linebuf.size() - 1] == '\n')
					linebuf.erase(linebuf.size() - 1);
			}
			if (linebuf.size() > 0)
			{
				if (linebuf[linebuf.size() - 1] == '\r')
					linebuf.erase(linebuf.size() - 1);
			}

			// Skip if empty line.
			if (linebuf.empty())
			{
				continue;
			}

			// Skip leading space.
			const char *token = linebuf.c_str();
			token += strspn(token, " \t");

			assert(token);
			if (token[0] == '\0')
				continue; // empty line

			if (token[0] == '#')
				continue; // comment line

			// vertex
			if (token[0] == 'v' && isSpace((token[1])))
			{
				token += 2;
				float x, y, z;
				parseFloat3(x, y, z, token);
				v.push_back(x);
				v.push_back(y);
				v.push_back(z);
				continue;
			}

			// normal
			if (token[0] == 'v' && token[1] == 'n' && isSpace((token[2])))
			{
				token += 3;
				float x, y, z;
				parseFloat3(x, y, z, token);
				vn.push_back(x);
				vn.push_back(y);
				vn.push_back(z);
				continue;
			}

			// texcoord
			if (token[0] == 'v' && token[1] == 't' && isSpace((token[2])))
			{
				token += 3;
				float x, y;
				parseFloat2(x, y, token);
				vt.push_back(x);
				vt.push_back(y);
				continue;
			}

			// face
			if (token[0] == 'f' && isSpace((token[1])))
			{
				token += 2;
				token += strspn(token, " \t");

				std::vector<vertex_index> face;
				auto first = static_cast<int>(v.size() / 3);
				auto second = static_cast<int>(vn.size() / 3);
				auto third = static_cast<int>(vt.size() / 2);
				while (!isNewLine(token[0]))
				{
					vertex_index vi =
						parseTriple(token, first, second, third);
					face.push_back(vi);
					size_t n = strspn(token, " \t\r");
					token += n;
				}

				faceGroup.push_back(face);

				continue;
			}

			// use mtl
			if ((0 == strncmp(token, "usemtl", 6)) && isSpace((token[6])))
			{

				char namebuf[TINYOBJ_SSCANF_BUFFER_SIZE];
				token += 7;
#ifdef _MSC_VER
				sscanf_s(token, "%s", namebuf, _countof(namebuf));
#else
				sscanf(token, "%s", namebuf);
#endif

				// Create face group per material.
				bool ret = exportFaceGroupToShape(shape, vertexCache, v, vn, vt,
					faceGroup, material, name, true);
				if (ret)
				{
					shapes.push_back(shape);
				}
				shape = shape_t();
				faceGroup.clear();

				if (material_map.find(namebuf) != material_map.end())
				{
					material = material_map[namebuf];
				}
				else
				{
					// { error!! material not found }
					material = -1;
				}

				continue;
			}

			// load mtl
			if ((0 == strncmp(token, "mtllib", 6)) && isSpace((token[6])))
			{
				char namebuf[TINYOBJ_SSCANF_BUFFER_SIZE];
				token += 7;
#ifdef _MSC_VER
				sscanf_s(token, "%s", namebuf, _countof(namebuf));
#else
				sscanf(token, "%s", namebuf);
#endif

				std::string err_mtl = readMatFn(namebuf, materials, material_map);
				if (!err_mtl.empty())
				{
					faceGroup.clear(); // for safety
					return err_mtl;
				}

				continue;
			}

			// group name
			if (token[0] == 'g' && isSpace((token[1])))
			{

				// flush previous face group.
				bool ret = exportFaceGroupToShape(shape, vertexCache, v, vn, vt,
					faceGroup, material, name, true);
				if (ret)
				{
					shapes.push_back(shape);
				}

				shape = shape_t();

				// material = -1;
				faceGroup.clear();

				std::vector<std::string> names;
				while (!isNewLine(token[0]))
				{
					std::string str = parseString(token);
					names.push_back(str);
					token += strspn(token, " \t\r"); // skip tag
				}

				assert(names.size() > 0);

				// names[0] must be 'g', so skip the 0th element.
				if (names.size() > 1)
				{
					name = names[1];
				}
				else
				{
					name = "";
				}

				continue;
			}

			// object name
			if (token[0] == 'o' && isSpace((token[1])))
			{

				// flush previous face group.
				bool ret = exportFaceGroupToShape(shape, vertexCache, v, vn, vt,
					faceGroup, material, name, true);
				if (ret)
				{
					shapes.push_back(shape);
				}

				// material = -1;
				faceGroup.clear();
				shape = shape_t();

				// @todo { multiple object name? }
				char namebuf[TINYOBJ_SSCANF_BUFFER_SIZE];
				token += 2;
#ifdef _MSC_VER
				sscanf_s(token, "%s", namebuf, _countof(namebuf));
#else
				sscanf(token, "%s", namebuf);
#endif
				name = std::string(namebuf);

				continue;
			}

			// Ignore unknown command.
		}

		bool ret = exportFaceGroupToShape(shape, vertexCache, v, vn, vt, faceGroup,
			material, name, true);
		if (ret)
		{
			shapes.push_back(shape);
		}
		faceGroup.clear(); // for safety

		return err.str();
	}

} // namespace tinyobj
namespace GameEngine
{

	class ObjParser : public ISceneParser
	{

	public:
		virtual std::unique_ptr<GameObject> Parse(const std::string &buf)
		{
			std::vector<shape_t> shapes;
			std::vector<material_t> materials;
			MaterialFileReader matFileReader("");
			std::istringstream ifs(buf);
			auto ret = tinyobj::LoadObj(shapes, materials, ifs, matFileReader);
			parserMesh(shapes);
			return std::unique_ptr<GameObject>();
		}

		void parserMesh(std::vector<shape_t> shapes)
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
