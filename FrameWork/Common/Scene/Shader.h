#ifndef GameEngine_Common_Scene_Shader_H
#define GameEngine_Common_Scene_Shader_H

#include <cstdint>
#include <string>
#include <glad/glad.h>
#include "glm/glm.hpp"
#include "MyMath.h"

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
    class Shader
    {
    public:
        const char *COCOS2D_SHADER_UNIFORMS =
            "uniform mat4 CC_PMatrix;\n"
            "uniform mat4 CC_MultiViewPMatrix[4];\n"
            "uniform mat4 CC_MVMatrix;\n"
            "uniform mat4 CC_MVPMatrix;\n"
            "uniform mat4 CC_MultiViewMVPMatrix[4];\n"
            "uniform mat3 CC_NormalMatrix;\n"
            "uniform vec4 CC_Time;\n"
            "uniform vec4 CC_SinTime;\n"
            "uniform vec4 CC_CosTime;\n"
            "uniform vec4 CC_Random01;\n"
            "uniform sampler2D CC_Texture0;\n"
            "uniform sampler2D CC_Texture1;\n"
            "uniform sampler2D CC_Texture2;\n"
            "uniform sampler2D CC_Texture3;\n"
            "//CC INCLUDES END\n\n";
        unsigned int ID = 0;
        // constructor generates the shader on the fly
        // ------------------------------------------------------------------------
        Shader(std::string vertexCode, std::string fragmentCode, std::string geometryCode = "")
        {

            const char *vShaderCode = vertexCode.c_str();
            const char *fShaderCode = fragmentCode.c_str();
            // 2. compile shaders
            unsigned int vertex, fragment;

            if (vShaderCode)
            {
                if (!compileShader(&vertex, GL_VERTEX_SHADER, vShaderCode))
                {
                    return;
                }
            }

            if (fShaderCode)
            {
                if (!compileShader(&fragment, GL_FRAGMENT_SHADER, fShaderCode))
                {
                    return;
                }
            }

            checkCompileErrors(vertex, "VERTEX");
            checkCompileErrors(fragment, "FRAGMENT");

            unsigned int geometry;
            if (geometryCode.size() > 0)
            {
                const char *gShaderCode = geometryCode.c_str();
                if (gShaderCode)
                {
                    if (!compileShader(&geometry, GL_FRAGMENT_SHADER, gShaderCode))
                    {
                        return;
                    }
                }
                checkCompileErrors(geometry, "GEOMETRY");
            }
            // shader Program
            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            if (geometryCode.size() > 0)
                glAttachShader(ID, geometry);
            bindPredefinedVertexAttribs();
            glLinkProgram(ID);
            checkCompileErrors(ID, "PROGRAM");
            // delete the shaders as they're linked into our program now and no longer necessery
            glDeleteShader(vertex);
            glDeleteShader(fragment);
            if (geometryCode.size() > 0)
                glDeleteShader(geometry);
        }

        void bindPredefinedVertexAttribs()
        {
            static const struct
            {
                const char *attributeName;
                int location;
            } attribute_locations[] =
                {
                    {"a_position", MeshValueType::VERTEX_ATTRIB_POSITION},
                    {"a_color", MeshValueType::VERTEX_ATTRIB_COLOR},
                    {"a_texCoord", MeshValueType::VERTEX_ATTRIB_TEX_COORD},
                    {"a_texCoord1", MeshValueType::VERTEX_ATTRIB_TEX_COORD1},
                    {"a_texCoord2", MeshValueType::VERTEX_ATTRIB_TEX_COORD2},
                    {"a_texCoord3", MeshValueType::VERTEX_ATTRIB_TEX_COORD3},
                    {"a_normal", MeshValueType::VERTEX_ATTRIB_NORMAL},
                };

            const int size = sizeof(attribute_locations) / sizeof(attribute_locations[0]);

            for (int i = 0; i < size; i++)
            {
                glBindAttribLocation(ID, attribute_locations[i].location, attribute_locations[i].attributeName);
            }
        }

        // activate the shader
        // ------------------------------------------------------------------------

        bool compileShader(GLuint *shader, GLenum type, const GLchar *source)
        {
            GLint status;

            if (!source)
            {
                return false;
            }

            const GLchar *sources[] = {
                COCOS2D_SHADER_UNIFORMS,
                source};

            *shader = glCreateShader(type);
            glShaderSource(*shader, sizeof(sources) / sizeof(*sources), sources, nullptr);
            glCompileShader(*shader);

            glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);

            if (!status)
            {
                GLsizei length;
                glGetShaderiv(*shader, GL_SHADER_SOURCE_LENGTH, &length);
                GLchar *src = (GLchar *)malloc(sizeof(GLchar) * length);

                glGetShaderSource(*shader, length, nullptr, src);
                free(src);

                return false;
            }

            return (status == GL_TRUE);
        }

        void use()
        {
            glUseProgram(ID);
        }
        // utility uniform functions
        // ------------------------------------------------------------------------
        void set(const std::string &name, bool value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
        }
        // ------------------------------------------------------------------------
        void set(const std::string &name, int value) const
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        }
        // ------------------------------------------------------------------------
        void set(const std::string &name, float value) const
        {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        }
        // ------------------------------------------------------------------------
        void set(const std::string &name, const glm::vec2 &value) const
        {
            glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }
        void set(const std::string &name, float x, float y) const
        {
            glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
        }
        // ------------------------------------------------------------------------
        void set(const std::string &name, const glm::vec3 &value) const
        {
            glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }
        void set(const std::string &name, float x, float y, float z) const
        {
            glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
        }
        // ------------------------------------------------------------------------
        void set(const std::string &name, const glm::vec4 &value) const
        {
            glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }
        void set(const std::string &name, float x, float y, float z, float w)
        {
            glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
        }
        // ------------------------------------------------------------------------
        void set(const std::string &name, const glm::mat2 &mat) const
        {
            glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        // ------------------------------------------------------------------------
        void set(const std::string &name, const glm::mat3 &mat) const
        {
            glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        // ------------------------------------------------------------------------
        void set(const std::string &name, const glm::mat4 &mat) const
        {
            glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

    private:
        // utility function for checking shader compilation/linking errors.
        // ------------------------------------------------------------------------
        void checkCompileErrors(GLuint shader, std::string type)
        {
            GLint success;
            GLchar infoLog[1024];
            if (type != "PROGRAM")
            {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                }
            }
            else
            {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                }
            }
            if (!success)
                printf(infoLog);
        }
    };

} // namespace GameEngine

#endif