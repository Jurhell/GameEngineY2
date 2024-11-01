#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& filepath) : m_filePath(filepath), m_rendererID(0)
{
	ShaderProgramSource source = parseShader(filepath);
	m_rendererID = createShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	glDeleteShader(m_rendererID);
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();

	return 0;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
	return 0;
}

ShaderProgramSource Shader::parseShader(const std::string& filepath)
{
	return ShaderProgramSource();
}

void Shader::bind() const
{

}

void Shader::unBind() const
{

}

void Shader::setUniform1i(const std::string& name, float value)
{

}

void Shader::setUniform1f(const std::string& name, float value)
{

}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{

}

int Shader::getUniformLocation(const std::string& name)
{
	return 0;
}
