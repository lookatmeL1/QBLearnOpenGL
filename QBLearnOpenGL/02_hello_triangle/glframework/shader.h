#pragma once
#include "core.h"

enum CheckType
{
	  COMPILE,
	  LINK,
};

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmenPath);
	~Shader();

	void begin();//开始使用当前shader

	void end();

private:
	void checkShderErrors(GLuint target, CheckType type);

private:
	GLuint mProgram{ 0 };

};

