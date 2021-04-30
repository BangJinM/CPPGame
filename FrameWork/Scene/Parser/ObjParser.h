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

#include "BoundingBox.h"
#include "Config.h"
#include "GameObject.h"
#include "IParser.h"
#include "Mesh.h"
#include "ObjLoader.h"

#include "../NewRender/Core/GERBuffer.h"
#include "../NewRender/Core/GERDevice.h"
#include "../NewRender/Core/GERInputAssembler.h"
#include "../NewRender/Core/GERObject.h"

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
            ger::Device *device = ger::Device::getInstance();
            SharedMesh m_mesh = std::make_shared<Mesh>();

            int index = 0;
            BoundingBox boundingBox;
            m_mesh->meshNewDataList.resize(shapes.size());

            for (auto &shape : shapes)
            {
                std::vector<float> vertex;

                auto mesh = shape.mesh;
                ger::Attribute attr;
                attr.size = 3;
                ger::AttributeList attrs;
                if (mesh.positions.size())
                {
                    attr.type = ger::Type::FLOAT;
                    attr.stride = attr.size * sizeof(float);
                    attrs.push_back(attr);
                }
                bool hasnormal = false, hastex = false;
                if (mesh.normals.size())
                {
                    hasnormal = true;
                    attr.type = ger::Type::FLOAT;
                    attr.stride = attr.size * sizeof(float);
                    attrs.push_back(attr);
                }
                if (mesh.texcoords.size())
                {
                    hastex = true;
                    attr.size = 2;
                    attr.type = ger::Type::FLOAT;
                    attr.stride = attr.size * sizeof(float);
                    attrs.push_back(attr);
                }

                auto vertexNum = mesh.positions.size() / 3;
                for (unsigned int k = 0; k < vertexNum; ++k)
                {
                    vertex.push_back(mesh.positions[k * 3]);
                    vertex.push_back(mesh.positions[k * 3 + 1]);
                    vertex.push_back(mesh.positions[k * 3 + 2]);

                    if (hasnormal)
                    {
                        vertex.push_back(mesh.normals[k * 3]);
                        vertex.push_back(mesh.normals[k * 3 + 1]);
                        vertex.push_back(mesh.normals[k * 3 + 2]);
                    }

                    if (hastex)
                    {
                        vertex.push_back(mesh.texcoords[k * 2]);
                        vertex.push_back(mesh.texcoords[k * 2 + 1]);
                    }
                }
                boundingBox.Set(mesh.positions.data(), vertexNum, sizeof(float) * 3);
                m_mesh->SetBoundingBox(boundingBox);

                ger::BufferInfo info;
                info.usage = ger::BufferUsage::INDEX;
                info.size = mesh.indices.size() * sizeof(float);
                ger::GERBuffer *bufferIndex = device->CreateBuffer(info);
                device->p_GERCommandBuffer->UpdateBuffer(bufferIndex, &mesh.indices);

                info.usage = ger::BufferUsage::VERTEX;
                info.size = vertex.size() * sizeof(float);
                ger::GERBuffer *bufferVertex = device->CreateBuffer(info);
                device->p_GERCommandBuffer->UpdateBuffer(bufferVertex, &vertex);

                m_mesh->SetData(bufferIndex, bufferVertex, attrs, index);
                index++;
            }
            return m_mesh;
        }

    }; // namespace GameEngine
} // namespace GameEngine