#pragma once
#include "core.h"
#include<string>

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

	GLuint getLocation(char* name);

	void setUniform1f(const std::string& variableName, float value);

private:
	void checkShderErrors(GLuint target, CheckType type);

private:
	GLuint mProgram{ 0 };

};

