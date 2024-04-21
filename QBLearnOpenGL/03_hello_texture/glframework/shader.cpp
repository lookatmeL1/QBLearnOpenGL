#include "shader.h"
#include "shader.h"
#include "shader.h"
#include "shader.h"
#include "shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	//声明转入shader代码字符串的两个string
	std::string vertexCode;
	std::string fragmentCode;
	//声明用于读取vs和fs文件的inFileStream
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	//保证ifstream遇到问题的时候可以抛出异常
	vShaderFile.exceptions(std::ifstream::failbit | std:: ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std:: ifstream::badbit);
	try
	{
		//打开文件
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		//将文件输入流当中的字符串输入到stringStream里面
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//关闭文件
		vShaderFile.close();
		fShaderFile.close();

		//读取字符串，转化到CodeStream
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	}
	catch (const std::ifstream::failure& e)
	{
		std::cout << "shader文件读取出错：" << e.what() <<std::endl;
	}

	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	//创建顶点着色器
	unsigned int vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//附加着色器代码
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//编译顶点着色器代码
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	//检测是否编译成功
	checkShderErrors(vertexShader,CheckType::COMPILE);
	checkShderErrors(fragmentShader, CheckType::COMPILE);

	//创建程序对象
	mProgram = glCreateProgram();
	//将着色器附加到程序对象上
	glAttachShader(mProgram, vertexShader);
	glAttachShader(mProgram, fragmentShader);

	//链接着色器
	glLinkProgram(mProgram);
	checkShderErrors(mProgram, CheckType::LINK);

	//使用着色器程序
	glUseProgram(mProgram);

	//删除着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
}

void Shader::begin()//开始使用当前shader
{
	glUseProgram(mProgram);
}

void Shader::end()
{
	glUseProgram(0);
}

GLuint Shader::getLocation(char* name)
{
	return glGetAttribLocation(mProgram,name);
}

void Shader::setUniform1f(const std::string& variableName, float value)
{
	GLint location = glGetUniformLocation(mProgram, variableName.c_str());
	glUniform1f(location, value);
}


void Shader::checkShderErrors(GLuint target, CheckType type)
{
	int success;
	char infoLog[512];

	switch (type)
	{
	case COMPILE:
		glGetShaderiv(target, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(target, 512, NULL, infoLog);
			std::cout << "着色器编译失败：\n" << infoLog << std::endl;
		}
		break;
	case LINK:
		glGetProgramiv(target, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(target, 512, NULL, infoLog);
			std::cout << "链接着色器失败！！" << infoLog << std::endl;
		}
		break;
	default:
		std::cout << "type 不对劲！！小老弟" << std::endl;
		break;	
	}
}
