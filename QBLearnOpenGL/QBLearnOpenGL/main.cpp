#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
//ע��ص������������ڴ�С������ʱ����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

int main()
{
	//��ʼ��glfw
	glfwInit();
	//����OpenGL���汾�ʹΰ汾�Ŷ�Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	//ʹ�õ��Ǻ���ģʽ(Core-profile) ��ֻ��ʹ��OpenGL���ܵ�һ���Ӽ���û�������Ѳ�����Ҫ�����������ԣ�
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Mac os xϵͳר��
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//�������崰�� ���������ڿ����ڸߣ����ڱ��⣬��ʱ���ԣ���ʱ����
	GLFWwindow* window = glfwCreateWindow(800,600,"LearnOpendGL",NULL,NULL);
	if (window == NULL)
	{
		std::cout << "����GLFW����ʧ�ܣ���" << std::endl;
		//�����߳�
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//��ʼ��GLAD������OpenGL�ĺ���ָ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "��ʼ�� GLAD ʧ�ܣ���" << std::endl;
		return -1;
	}

	//��Ⱦ���ڣ���Ⱦ���ڿ���С�����崰�ڣ� ���������½�λ�ã�X��Y��������
	glViewport(0, 0, 800, 600);

	//��������ص�
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//�������û�б��ر����ѭ����Ⱦ����
	while (!glfwWindowShouldClose(window))
	{
		//�������
		processInput(window);

		//��Ⱦָ��TODO
		
		glClearColor(0.2f,0.3f,0.3f,1.0f);	  //��Ⱦ��ɫ
		glClear(GL_COLOR_BUFFER_BIT);//�����һ֡����ɫ

		//�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
		glfwSwapBuffers(window);
		//���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã���
		glfwPollEvents();
	}

	//����Ⱦѭ���������Ƿ�������Դ
	glfwTerminate();

	return 0;
}

void  framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//������ʱ������Ⱦ�����Ĵ���
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	//�������ESC����رճ���
	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,true);
	}
}
