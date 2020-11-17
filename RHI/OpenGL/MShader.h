#pragma once

#include <list>

#include "Object.h"
#include "Config.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

GameEngineBegin

    class MShader : public Object
{
public:
    const char *COCOS2D_VERTEX_SHADER_UNIFORMS =
        "#version 330 core\n"
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

    enum ShaderType
    {
        Vertex = 0x0001,
        Fragment = 0x0002,
        Geometry = 0x0004,
    };

    explicit MShader(MShader::ShaderType type);
    ~MShader();

    ShaderType GetShaderType() const;

    bool CompileSourceCode(const char *source);

    char *m_SourceCode() const;
    ShaderType m_ShaerType;
    int m_CompileID;
};

class MShaderProgram : public Object
{
public:
    explicit MShaderProgram();

    bool AddShaderFromSourceCode(MShader::ShaderType type, const char *source);
    bool AddShaderFromFilePath(MShader::ShaderType type, const char *path);

    bool Link();
    bool IsLinked() const;

    void RemoveAllShaders();

    GLuint ProgramId() const;

    void BindPredefinedVertexAttribs();

    std::list<MShader *> m_Shaders() const;

    GLuint m_ProgramID;
};

GameEngineEnd