#include "MShader.h"

GameEngineBegin

MShader::MShader(MShader::ShaderType type) : m_ShaerType(type)
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

MShader::ShaderType MShader::GetShaderType() const
{
    return m_ShaerType;
}

bool MShader::CompileSourceCode(const char *source)
{
    GLint status;
    GLenum shaderType = GL_VERTEX_SHADER;
    const GLchar *sources[] = {
        COCOS2D_VERTEX_SHADER_UNIFORMS,
        source};
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

    glShaderSource(m_CompileID, sizeof(sources) / sizeof(*sources), sources, nullptr);
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

MShaderProgram::MShaderProgram() {}

bool MShaderProgram::AddShaderFromSourceCode(MShader::ShaderType type, const char *source)
{
    MShader *mShader = new MShader(type);
    mShader->CompileSourceCode(source);
    m_Shaders.insert(mShader);
}
bool MShaderProgram::AddShaderFromFilePath(MShader::ShaderType type, const char *path)
{
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
}

void MShaderProgram::BindPredefinedVertexAttribs()
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
        glBindAttribLocation(m_ProgramID, attribute_locations[i].location, attribute_locations[i].attributeName);
    }
}

GameEngineEnd