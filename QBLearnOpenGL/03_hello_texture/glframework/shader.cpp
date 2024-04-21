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
	//����ת��shader�����ַ���������string
	std::string vertexCode;
	std::string fragmentCode;
	//�������ڶ�ȡvs��fs�ļ���inFileStream
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	//��֤ifstream���������ʱ������׳��쳣
	vShaderFile.exceptions(std::ifstream::failbit | std:: ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std:: ifstream::badbit);
	try
	{
		//���ļ�
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		//���ļ����������е��ַ������뵽stringStream����
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//�ر��ļ�
		vShaderFile.close();
		fShaderFile.close();

		//��ȡ�ַ�����ת����CodeStream
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

	}
	catch (const std::ifstream::failure& e)
	{
		std::cout << "shader�ļ���ȡ����" << e.what() <<std::endl;
	}

	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	//����������ɫ��
	unsigned int vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//������ɫ������
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//���붥����ɫ������
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	//����Ƿ����ɹ�
	checkShderErrors(vertexShader,CheckType::COMPILE);
	checkShderErrors(fragmentShader, CheckType::COMPILE);

	//�����������
	mProgram = glCreateProgram();
	//����ɫ�����ӵ����������
	glAttachShader(mProgram, vertexShader);
	glAttachShader(mProgram, fragmentShader);

	//������ɫ��
	glLinkProgram(mProgram);
	checkShderErrors(mProgram, CheckType::LINK);

	//ʹ����ɫ������
	glUseProgram(mProgram);

	//ɾ����ɫ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
}

void Shader::begin()//��ʼʹ�õ�ǰshader
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
			std::cout << "��ɫ������ʧ�ܣ�\n" << infoLog << std::endl;
		}
		break;
	case LINK:
		glGetProgramiv(target, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(target, 512, NULL, infoLog);
			std::cout << "������ɫ��ʧ�ܣ���" << infoLog << std::endl;
		}
		break;
	default:
		std::cout << "type ���Ծ�����С�ϵ�" << std::endl;
		break;	
	}
}
