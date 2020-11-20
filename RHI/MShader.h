#pragma once

#include <vector>

#include "Object.h"
#include "Config.h"
#include "glm/glm.hpp"

GameEngineBegin

class MShader : public Object
{
public:


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

    char *m_SourceCode;
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

	bool Use();

    void RemoveAllShaders();

    int ProgramId() const;

    void BindPredefinedVertexAttribs();

	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const std::string &name, bool value) const;
	// ------------------------------------------------------------------------
	void setInt(const std::string &name, int value) const;
	// ------------------------------------------------------------------------
	void setFloat(const std::string &name, float value) const;
	// ------------------------------------------------------------------------
	void setVec2(const std::string &name, const glm::vec2 &value) const;
	void setVec2(const std::string &name, float x, float y) const;
	// ------------------------------------------------------------------------
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	// ------------------------------------------------------------------------
	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setVec4(const std::string &name, float x, float y, float z, float w);
	// ------------------------------------------------------------------------
	void setMat2(const std::string &name, const glm::mat2 &mat) const;
	// ------------------------------------------------------------------------
	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	// ------------------------------------------------------------------------
	void setMat4(const std::string &name, const float *value) const;


    std::vector<MShader *> m_Shaders;

    int m_ProgramID;
};

GameEngineEnd