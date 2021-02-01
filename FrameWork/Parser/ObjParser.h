//
// Copyright 2012-2015, Syoyo Fujita.
//
// Licensed under 2-clause BSD license.
//
//https://github.com/syoyo/tinyobjloader
#pragma once

#include <map>
#include <string>
#include <vector>

#include "Config.h"
#include "GameObject.h"
#include "IParser.h"
#include "Mesh.h"
#include "ObjLoader.h"

namespace GameEngine
{
    class ObjParser : public IParser
    {
    public:
        virtual SharedObject Parser(const std::string path) override
        {
            std::vector<tinyobj::shape_t> shapes;
            std::vector<tinyobj::material_t> materials;
            tinyobj::LoadObj(shapes, materials, path.c_str(), "");

            return parserMesh(shapes, materials);
        }

        static SharedMesh parserMesh(std::vector<tinyobj::shape_t> shapes, std::vector<tinyobj::material_t> materials)
        {
            SharedMesh m_mesh;
            for (auto &shape : shapes)
            {
                if (!m_mesh)
                    m_mesh = std::make_shared<Mesh>();
                MeshData meshData = MeshData();
                auto mesh = shape.mesh;
                MeshVertexAttrib attrib;
                attrib.size = 3;
                //attrib.type = GL_FLOAT;

                if (mesh.positions.size())
                {
                    attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_POSITION;
                    attrib.attribSizeBytes = attrib.size * sizeof(float);
                    meshData.attribs.push_back(attrib);
                    meshData.vertexSizeInFloat += 3;
                }
                bool hasnormal = false, hastex = false;
                if (mesh.normals.size())
                {
                    hasnormal = true;
                    attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_NORMAL;
                    attrib.attribSizeBytes = attrib.size * sizeof(float);
                    meshData.attribs.push_back(attrib);
                    meshData.vertexSizeInFloat += 3;
                }
                if (mesh.texcoords.size())
                {
                    hastex = true;
                    attrib.size = 2;
                    attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_TEX_COORD;
                    attrib.attribSizeBytes = attrib.size * sizeof(float);
                    meshData.attribs.push_back(attrib);
                    meshData.vertexSizeInFloat += 2;
                }

                auto vertexNum = mesh.positions.size() / 3;
                for (unsigned int k = 0; k < vertexNum; ++k)
                {
                    meshData.vertex.push_back(mesh.positions[k * 3]);
                    meshData.vertex.push_back(mesh.positions[k * 3 + 1]);
                    meshData.vertex.push_back(mesh.positions[k * 3 + 2]);

                    if (hasnormal)
                    {
                        meshData.vertex.push_back(mesh.normals[k * 3]);
                        meshData.vertex.push_back(mesh.normals[k * 3 + 1]);
                        meshData.vertex.push_back(mesh.normals[k * 3 + 2]);
                    }

                    if (hastex)
                    {
                        meshData.vertex.push_back(mesh.texcoords[k * 2]);
                        meshData.vertex.push_back(mesh.texcoords[k * 2 + 1]);
                    }
                }

                meshData.indices = mesh.indices;
                m_mesh->pushMeshData(meshData);
            }
            return m_mesh;
        }

    };  // namespace GameEngine
}  // namespace GameEngine