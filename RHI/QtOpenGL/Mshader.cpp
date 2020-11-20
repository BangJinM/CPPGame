#include "MShader.h"
#include <QVector2D>

GameEngine::MShaderProgram::MShaderProgram()
{
    m_QOpenGLShaderProgram = new QOpenGLShaderProgram();
}

bool GameEngine::MShaderProgram::AddShaderFromSourceCode(GameEngine::MShader::ShaderType type, const char *source)
{
    QString str =
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
    str += source;
    if(type == MShader::ShaderType::Vertex)
        m_QOpenGLShaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, str);
    else if(type == MShader::ShaderType::Fragment)
        m_QOpenGLShaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, str);
    else if (type == MShader::ShaderType::Geometry)
        m_QOpenGLShaderProgram->addShaderFromSourceCode(QOpenGLShader::Geometry, str);
    return true;
}

bool GameEngine::MShaderProgram::Link()
{
    BindPredefinedVertexAttribs();
    m_QOpenGLShaderProgram->link();
    return true;
}

bool GameEngine::MShaderProgram::Use()
{
    m_QOpenGLShaderProgram->bind();
    return true;
}

void GameEngine::MShaderProgram::BindPredefinedVertexAttribs()
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
        m_QOpenGLShaderProgram->bindAttributeLocation(attribute_locations[i].attributeName, attribute_locations[i].location);
    }
}

void GameEngine::MShaderProgram::setBool(const std::string &name, bool value) const
{
    m_QOpenGLShaderProgram->setUniformValue(m_QOpenGLShaderProgram->uniformLocation(name.c_str()), value);
}

void GameEngine::MShaderProgram::setInt(const std::string &name, int value) const
{
    m_QOpenGLShaderProgram->setUniformValue(m_QOpenGLShaderProgram->uniformLocation(name.c_str()), value);
}

void GameEngine::MShaderProgram::setFloat(const std::string &name, float value) const
{
    m_QOpenGLShaderProgram->setUniformValue(m_QOpenGLShaderProgram->uniformLocation(name.c_str()), value);
}

void GameEngine::MShaderProgram::setVec2(const std::string &name, const float *value) const
{
    m_QOpenGLShaderProgram->setAttributeArray(m_QOpenGLShaderProgram->uniformLocation(name.c_str()), value, 2);
}

void GameEngine::MShaderProgram::setVec2(const std::string &name, float x, float y) const
{
    QVector2D vec(x,y);
    m_QOpenGLShaderProgram->setAttributeArray(m_QOpenGLShaderProgram->uniformLocation(name.c_str()), &vec);
}

void GameEngine::MShaderProgram::setVec3(const std::string &name, const float *value) const
{
    m_QOpenGLShaderProgram->setAttributeArray(m_QOpenGLShaderProgram->uniformLocation(name.c_str()), value, 3);
}

void GameEngine::MShaderProgram::setVec3(const std::string &name, float x, float y, float z) const
{
    QVector3D vec(x,y,z);
    m_QOpenGLShaderProgram->setAttributeArray(m_QOpenGLShaderProgram->uniformLocation(name.c_str()), &vec);
}

void GameEngine::MShaderProgram::setVec4(const std::string &name, const float *value) const
{
    m_QOpenGLShaderProgram->setAttributeArray(m_QOpenGLShaderProgram->uniformLocation(name.c_str()), value, 4);
}

void GameEngine::MShaderProgram::setVec4(const std::string &name, float x, float y, float z, float w)
{
    QVector4D vec(x,y,z,w);
    m_QOpenGLShaderProgram->setAttributeArray(m_QOpenGLShaderProgram->uniformLocation(name.c_str()), &vec);
}

void GameEngine::MShaderProgram::setMat2(const std::string &name, const float *value) const
{
    m_QOpenGLShaderProgram->setAttributeArray(m_QOpenGLShaderProgram->uniformLocation(name.c_str()), value, 4);
}

void GameEngine::MShaderProgram::setMat3(const std::string &name, const float *value) const
{
    m_QOpenGLShaderProgram->setAttributeArray(m_QOpenGLShaderProgram->uniformLocation(name.c_str()), value, 9);
}

void GameEngine::MShaderProgram::setMat4(const std::string &name, const float *value) const
{
    m_QOpenGLShaderProgram->setAttributeArray(m_QOpenGLShaderProgram->uniformLocation(name.c_str()), value, 16);
}

int GameEngine::MShaderProgram::uniformLocation(const char *name)
{
    return m_QOpenGLShaderProgram->uniformLocation(name);
}
