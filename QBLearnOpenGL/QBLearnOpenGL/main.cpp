//第一次提交，欧耶！！！
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
//注册回调函数，当窗口大小被调整时调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

int main()
{
	//初始化glfw
	glfwInit();
	//设置OpenGL主版本和次版本号都为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	//使用的是核心模式(Core-profile) ，只能使用OpenGL功能的一个子集（没有我们已不再需要的向后兼容特性）
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Mac os x系统专用
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//创建整体窗口 参数：窗口宽，窗口高，窗口标题，暂时忽略，暂时忽略
	GLFWwindow* window = glfwCreateWindow(800,600,"LearnOpendGL",NULL,NULL);
	if (window == NULL)
	{
		std::cout << "创建GLFW窗口失败！！" << std::endl;
		//结束线程
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//初始化GLAD来管理OpenGL的函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "初始化 GLAD 失败！！" << std::endl;
		return -1;
	}

	//渲染窗口（渲染窗口可以小于整体窗口） 参数：左下角位置（X，Y），宽，高
	glViewport(0, 0, 800, 600);

	//设置拉伸回调
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//如果窗口没有被关闭则会循环渲染窗口
	while (!glfwWindowShouldClose(window))
	{
		//按键监控
		processInput(window);

		//渲染指令TODO
		
		glClearColor(0.2f,0.3f,0.3f,1.0f);	  //渲染颜色
		glClear(GL_COLOR_BUFFER_BIT);//清除上一帧的颜色

		//函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
		glfwSwapBuffers(window);
		//函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
		glfwPollEvents();
	}

	//当渲染循环结束后是否所有资源
	glfwTerminate();

	return 0;
}

void  framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//被拉伸时重新渲染拉伸后的窗口
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	//如果按下ESC键则关闭程序
	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,true);
	}
}
