#include "MShader.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

GameEngineBegin

MShader::MShader(MShader::ShaderType type)
    : m_ShaerType(type)
{
}

MShader::~MShader()
{
    if (m_CompileID <= 0)
        return;
    GLsizei length;
    glGetShaderiv(m_CompileID, GL_SHADER_SOURCE_LENGTH, &length);
    GLchar *src = (GLchar *)malloc(sizeof(GLchar) * length);
    glGetShaderSource(m_CompileID, length, nullptr, src);
    free(src);
}

MShader::ShaderType MShader::GetShaderType() const { return m_ShaerType; }

bool MShader::CompileSourceCode(const char *source)
{
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
    GLint status;
    GLenum shaderType = GL_VERTEX_SHADER;
    const GLchar *sources[] = {COCOS2D_VERTEX_SHADER_UNIFORMS, source};
    if (m_ShaerType == MShader::ShaderType::Vertex)
    {
        shaderType = GL_VERTEX_SHADER;
    }
    else if (m_ShaerType == MShader::ShaderType::Fragment)
    {
        shaderType = GL_FRAGMENT_SHADER;
    }
    else if (m_ShaerType == MShader::ShaderType::Geometry)
    {
        shaderType = GL_GEOMETRY_SHADER;
    }
    m_CompileID = glCreateShader(shaderType);

    glShaderSource(m_CompileID, sizeof(sources) / sizeof(*sources), sources,
                   nullptr);
    glCompileShader(m_CompileID);

    glGetShaderiv(m_CompileID, GL_COMPILE_STATUS, &status);

    if (!status)
    {
        GLsizei length;
        glGetShaderiv(m_CompileID, GL_SHADER_SOURCE_LENGTH, &length);
        GLchar *src = (GLchar *)malloc(sizeof(GLchar) * length);

        glGetShaderSource(m_CompileID, length, nullptr, src);
        free(src);

        return false;
    }
    return (status == GL_TRUE);
}

MShaderProgram::MShaderProgram() { RemoveAllShaders(); }

bool MShaderProgram::AddShaderFromSourceCode(MShader::ShaderType type,
                                             const char *source)
{
    MShader *mShader = new MShader(type);
    mShader->CompileSourceCode(source);
    m_Shaders.push_back(mShader);
    return true;
}
bool MShaderProgram::AddShaderFromFilePath(MShader::ShaderType type,
                                           const char *path)
{
    return true;
}

bool MShaderProgram::Link()
{
    m_ProgramID = glCreateProgram();
    for (int i = 0; i < m_Shaders.size(); i++)
    {
        glAttachShader(m_ProgramID, m_Shaders[i]->m_CompileID);
    }
    BindPredefinedVertexAttribs();
    glLinkProgram(m_ProgramID);
    return true;
}

void MShaderProgram::RemoveAllShaders()
{
    for (size_t i = 0; i < m_Shaders.size(); i++)
    {
        delete m_Shaders[i];
    }
    m_Shaders.clear();
}

int MShaderProgram::ProgramId() const { return m_ProgramID; }

bool MShaderProgram::Use()
{
    glUseProgram(m_ProgramID);
    return true;
}

void MShaderProgram::BindPredefinedVertexAttribs()
{
    static const struct
    {
        const char *attributeName;
        int location;
    } attribute_locations[] = {
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
        glBindAttribLocation(m_ProgramID, attribute_locations[i].location,
                             attribute_locations[i].attributeName);
    }
}

// utility uniform functions
// ------------------------------------------------------------------------
void MShaderProgram::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void MShaderProgram::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void MShaderProgram::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_ProgramID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void MShaderProgram::setVec2(const std::string &name,
                             const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, &value[0]);
}
void MShaderProgram::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_ProgramID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void MShaderProgram::setVec3(const std::string &name,
                             const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, &value[0]);
}
void MShaderProgram::setVec3(const std::string &name, float x, float y,
                             float z) const
{
    glUniform3f(glGetUniformLocation(m_ProgramID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void MShaderProgram::setVec4(const std::string &name,
                             const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, &value[0]);
}
void MShaderProgram::setVec4(const std::string &name, float x, float y, float z,
                             float w)
{
    glUniform4f(glGetUniformLocation(m_ProgramID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void MShaderProgram::setMat2(const std::string &name,
                             const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1,
                       GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void MShaderProgram::setMat3(const std::string &name,
                             const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1,
                       GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void MShaderProgram::setMat4(const std::string &name,
                             const float *value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1,
                       GL_FALSE, value);
}

GameEngineEnd