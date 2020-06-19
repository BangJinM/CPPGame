#ifndef GameEngine_Common_Scene_Mesh_H
#define GameEngine_Common_Scene_Mesh_H

#include "ClassIDs.h"
#include "Component.h"
#include <glad/glad.h>
#include <vector>
namespace GameEngine
{

    enum MeshValueType
    {
        /**Index 0 will be used as Position.*/
        VERTEX_ATTRIB_POSITION,
        /**Index 1 will be used as Color.*/
        VERTEX_ATTRIB_COLOR,
        /**Index 2 will be used as Tex coord unit 0.*/
        VERTEX_ATTRIB_TEX_COORD,
        /**Index 3 will be used as Tex coord unit 1.*/
        VERTEX_ATTRIB_TEX_COORD1,
        /**Index 4 will be used as Tex coord unit 2.*/
        VERTEX_ATTRIB_TEX_COORD2,
        /**Index 5 will be used as Tex coord unit 3.*/
        VERTEX_ATTRIB_TEX_COORD3,
        /**Index 6 will be used as Normal.*/
        VERTEX_ATTRIB_NORMAL,
        /**Index 7 will be used as Blend weight for hardware skin.*/
        VERTEX_ATTRIB_BLEND_WEIGHT,
        /**Index 8 will be used as Blend index.*/
        VERTEX_ATTRIB_BLEND_INDEX,
        /**Index 9 will be used as tangent.*/
        VERTEX_ATTRIB_TANGENT,
        /**Index 10 will be used as Binormal.*/
        VERTEX_ATTRIB_BINORMAL,
        VERTEX_ATTRIB_MAX,

        // backward compatibility
        VERTEX_ATTRIB_TEX_COORDS = VERTEX_ATTRIB_TEX_COORD,
    };

    struct MeshVertexAttrib
    {
        //attribute size
        GLint size;
        //GL_FLOAT
        GLenum type;
        //VERTEX_ATTRIB_POSITION,VERTEX_ATTRIB_COLOR,VERTEX_ATTRIB_TEX_COORD,VERTEX_ATTRIB_NORMAL, VERTEX_ATTRIB_BLEND_WEIGHT, VERTEX_ATTRIB_BLEND_INDEX, GLProgram for detail
        int vertexAttrib;
        //size in bytes
        int attribSizeBytes;
    };
    struct MeshData
    {
        typedef std::vector<unsigned short> IndexArray;
        std::vector<float> vertex;
        int vertexSizeInFloat;
        std::vector<IndexArray> subMeshIndices;
        std::vector<std::string> subMeshIds; //subMesh Names (since 3.3)
        int numIndex;
        std::vector<MeshVertexAttrib> attribs;
        int attribCount;

    public:
        /**
     * Get per vertex size
     * @return return the sum of each vertex's all attribute size.
     */
        int getPerVertexSize() const
        {
            int vertexsize = 0;
            for (const auto &attrib : attribs)
            {
                vertexsize += attrib.attribSizeBytes;
            }
            return vertexsize;
        }

        /**
     * Reset the data
     */
        void resetData()
        {
            vertex.clear();
            subMeshIndices.clear();
            attribs.clear();
            vertexSizeInFloat = 0;
            numIndex = 0;
            attribCount = 0;
        }
        MeshData()
            : vertexSizeInFloat(0), numIndex(0), attribCount(0)
        {
        }
        ~MeshData()
        {
            resetData();
        }
    };

    struct MeshDatas : public Component
    {
        std::vector<MeshData *> meshDatas;

        MeshDatas() : Component(ClassID(MeshDatas))
        {
        }

        void resetData()
        {
            for (auto &it : meshDatas)
            {
                delete it;
            }
            meshDatas.clear();
        }
        ~MeshDatas()
        {
            resetData();
        }
    };
} // namespace GameEngine
#endif