#ifndef GameEngine_Common_Scene_Mesh_H
#define GameEngine_Common_Scene_Mesh_H

#include "ClassIDs.h"
#include "Component.h"
#include <glad/glad.h>
#include <vector>
#include "Material.h"

namespace GameEngine
{
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
        std::vector<unsigned int> indices;
        int vertexSizeInFloat;
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

    //https://learnopengl-cn.github.io/03%20Model%20Loading/02%20Mesh
    class Mesh
    {
    public:
        /*  网格数据  */
        MeshData *m_MeshData;
        /*  函数  */
        Mesh(MeshData *meshData);
        void Draw();

    private:
        /*  渲染数据  */
        unsigned int VAO, VBO, EBO;
        /*  函数  */
        void setupMesh();
    };

} // namespace GameEngine
#endif