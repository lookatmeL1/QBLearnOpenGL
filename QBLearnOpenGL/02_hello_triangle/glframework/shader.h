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

	void begin();//��ʼʹ�õ�ǰshader

	void end();

private:
	void checkShderErrors(GLuint target, CheckType type);

private:
	GLuint mProgram{ 0 };

};

