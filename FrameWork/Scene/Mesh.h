
#pragma once

#include <vector>

#include "BoundingBox.h"
#include "Config.h"
#include "Object.h"

#include "../NewRender/Core/GERBuffer.h"
#include "../NewRender/Core/GERDevice.h"
#include "../NewRender/Core/GERInputAssembler.h"
#include "../NewRender/Core/GERObject.h"

namespace GameEngine
{
    struct MeshVertexAttrib
    {
        //attribute size
        unsigned int size;
        //GL_FLOAT
        unsigned int type;
        //VERTEX_ATTRIB_POSITION,VERTEX_ATTRIB_COLOR,VERTEX_ATTRIB_TEX_COORD,VERTEX_ATTRIB_NORMAL, VERTEX_ATTRIB_BLEND_WEIGHT, VERTEX_ATTRIB_BLEND_INDEX, GLProgram for detail
        int vertexAttrib;
        //size in bytes
        int attribSizeBytes;
    };

    class MeshData
    {
    public:
        std::vector<float> vertex;
        std::vector<int> indices;
        int vertexSizeInFloat;
        int numIndex;
        std::vector<MeshVertexAttrib> attribs;
        int attribCount;
        /*  渲染数据  */
        unsigned int VAO, VBO, EBO;

    public:
        //////////////////////////////
        //  * Get per vertex size
        //  * @return return the sum of each vertex's all attribute size.
        //////////////////////////////
        int getPerVertexSize() const
        {
            int vertexsize = 0;
            for (const auto &attrib : attribs)
            {
                vertexsize += attrib.attribSizeBytes;
            }
            return vertexsize;
        }
        //////////////////////////////
        //  * Reset the data
        ///////////////////////////////
        void ResetData()
        {
            vertex.clear();
            attribs.clear();
            vertexSizeInFloat = 0;
            numIndex = 0;
            attribCount = 0;
        }

        MeshData() : vertexSizeInFloat(0), numIndex(0), attribCount(0)
        {
            ResetData();
        }

        ~MeshData()
        {
            ResetData();
        }
    };

    struct MeshNewData
    {
        ger::AttributeList attributeList;
        ger::GERBuffer *bufferIndex;
        ger::GERBuffer *bufferVertex;
        ger::InputAssembler *input;
    };
    typedef std::vector<MeshNewData> MeshNewDataList;

    class Mesh : public Object
    {
    public:
        //////////////////////////////////
        // * 渲染数据
        // * @param meshData 数据
        //////////////////////////////////
        void PushMeshData(MeshData &meshData)
        {
            m_MeshDatas.push_back(meshData);
        }

        void SetBoundingBox(BoundingBox oobb)
        {
            m_OOBB = oobb;
        }

        void SetData(ger::GERBuffer *bufferIndex, ger::GERBuffer *bufferVertex, ger::AttributeList attrs, int index)
        {
            ger::Device *device = ger::Device::getInstance();
            ger::InputAssemblerInfo inputInfo;
            inputInfo.indexBuffer = bufferIndex;
            inputInfo.vertexBuffers = bufferVertex;
            inputInfo.attributes = attrs;
            ger::InputAssembler *input = device->CreateInputAssembler(inputInfo);
            meshNewDataList.push_back({attrs, bufferIndex, bufferVertex, input});
        }

    public:
        //////////////////////////////////
        // * 渲染数据
        //////////////////////////////////
        std::vector<MeshData> m_MeshDatas;
        BoundingBox m_OOBB;
        bool isPrepare = false;

        MeshNewDataList meshNewDataList;
    };

} // namespace GameEngine