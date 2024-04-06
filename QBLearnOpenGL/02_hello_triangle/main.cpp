//第一次提交，欧耶！！！
#include "glframework/core.h"
#include "glframework/shader.h"
#include <iostream>
//注册回调函数，当窗口大小被调整时调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

Shader* shader = nullptr;

char* vertexPath = "assets/shaders/vertex.glsl";
char* fragmentPath = "assets/shaders/fragment.glsl";

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

	//定义顶点数组
	float vertices[] = {
	0.5f, 0.5f, 0.0f,   // 右上角
	0.5f, -0.5f, 0.0f,  // 右下角
	-0.5f, -0.5f, 0.0f, // 左下角
	-0.5f, 0.5f, 0.0f   // 左上角
	};

	unsigned int indices[] = {
		// 注意索引从0开始! 
		// 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
		// 这样可以由下标代表顶点组合成矩形

		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};

	//VBO（顶点缓冲对象）、VAO（顶点数组对象） 、EBO（索引缓冲对象）
	unsigned int VBO, VAO,EBO;

 //创建VBO对象
 //glBufferData（）
//在缓冲区填充数据 参数：它的第一个参数是目标缓冲的类型：顶点缓冲对象当前绑定到GL_ARRAY_BUFFER目标上。
//第二个参数指定传输数据的大小(以字节为单位)；用一个简单的sizeof计算出顶点数据大小就行。
//第三个参数是我们希望发送的实际数据。
//第四个参数指定了我们希望显卡如何管理给定的数据。它有三种形式：
//GL_STATIC_DRAW ：数据不会或几乎不会改变。
//GL_DYNAMIC_DRAW：数据会被改变很多。
//GL_STREAM_DRAW ：数据每次绘制时都会改变。
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	 //绑定缓冲
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//创建EBO对象
	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

   //创建VAO对象
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);


	//绑定vbo
	glBindBuffer(1, VBO);
	//设置顶点属性指针
	/*第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(Location)吗？它可以把顶点属性的位置值设置为0。
		因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。
	第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
	第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec * 都是由浮点数值组成的)。
	第四个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是 - 1）到1之间。我们把它设置为GL_FALSE。
	第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在3个float之后，我们把步长设置为3 * sizeof(float)。
		要注意的是由于我们知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。
		一旦我们有更多的顶点属性，我们就必须更小心地定义每个顶点属性之间的间隔，我们在后面会看到更多的例子
		（译注: 这个参数的意思简单说就是从这个属性第二次出现的地方到整个数组0位置之间有多少字节）。
	最后一个参数的类型是void * ，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。
	由于位置数据在数组的开头，所以这里是0。我们会在后面详细解释这个参数。*/
	glEnableVertexAttribArray(0);//激活 VAO 0号位置
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//将EBO加入当前VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glEnableVertexAttribArray(0);//激活 VAO 0号位置

	 //读取shader
	shader = new Shader(vertexPath,fragmentPath);

	//线框绘制模式
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	//如果窗口没有被关闭则会循环渲染窗口
	while (!glfwWindowShouldClose(window))
	{
		//按键监控
		processInput(window);

		//渲染指令
		glClearColor(0.2f,0.3f,0.3f,1.0f);	  //渲染颜色
		glClear(GL_COLOR_BUFFER_BIT); //清除上一帧的颜色

		shader->begin();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,0);		 //DrawCall
		glBindVertexArray(0);
		shader->end();

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
