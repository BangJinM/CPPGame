#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>

#include "MyMath.h"
namespace GameEngine
{
    class Object;
    class GameObject;
    class ShaderProgramBase;
    class Material;
    class Mesh;
    class Texture;
    class GameObject;
    class ShaderProgramBase;
    class Material;
    class Mesh;
    class Texture;
    class Widget;
    class Renderer;
    class Scene;
    class Cube;

#define SharePtr std::shared_ptr
#define SharedObject SharePtr<Object>
#define SharedGameObject SharePtr<GameObject>
#define SharedMaterial SharePtr<Material>
#define SharedMesh SharePtr<Mesh>
#define SharedTexture SharePtr<Texture>
#define SharedShaderProgramBase SharePtr<ShaderProgramBase>
#define SharedScene SharePtr<Scene>
#define SharedComponent SharePtr<Component>
#define SharedCube SharePtr<Cube>

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

    struct ViewInfos
    {
        static constexpr const char *VIEW_MATRIX = "u_view_matrix";
        static constexpr const char *PROJECTION_MATRIX = "u_projection_matrix";
        static constexpr const char *CAMERA_POS = "u_camera_pos";

        VecterFloat3 u_camera_pos;
        glm::mat4 u_projection_matrix;
        glm::mat4 u_view_matrix;
    };

    struct ModelInfos
    {
        glm::mat4 modelPos;
    };

    struct RendererCammand
    {
        SharedMaterial material;
        SharedMesh mesh;
        ViewInfos viewInfos;
        ModelInfos modelInfos;
        int index;
    };
    
    enum CubeDir
    {
        RIGHT = 1,
        LEFT,
        TOP,
        BOTTOM,
        BACK,
        FRONT
    };
    struct CubeValue
    {
        std::string path;
        CubeDir dir;
    };

}  // namespace GameEngine