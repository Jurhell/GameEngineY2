#pragma once
#include <GL/glew.h>
class VertexArray;
class IndexBuffer;
class Shader;

#define ASSERT(x) if(!(x)) __debugbreak()

void GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

void GLFWErrorCallback(int error, const char* description);

class Renderer
{
public:
	void clear();
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};