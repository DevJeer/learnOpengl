#include <glfw-3.3.bin.WIN32\include\GLFW\glfw3.h>
#include <glad\include\glad\glad.h>

#include "MyShader.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
	//初始化glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建window窗口
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Work Work OWO", NULL, NULL);

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glad 是用来管理opengl里面的函数指针的  所以在调用任何opengl的函数之前都得初始化加载glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//创建和编译Shader
	Shader ourShader("E:/vs2015project/01_OpenglProjectTest/Assets/Shaders/3.3.shader.vs", "E:/vs2015project/01_OpenglProjectTest/Assets/Shaders/3.3.shader.fs");

	//三角形顶点  带颜色
	float vertices[] = {
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	unsigned int VAO, VBO;
	//生成顶点数组对象  顶点的属性调用会储存到VAO中
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//绑定顶点数组对象
	glBindVertexArray(VAO);
	//绑定缓冲区
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//设置顶点属性指针
	//位置
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//颜色
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//释放buffer  但是VAO里面已经有原来的顶点数据了
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//主循环
	while (!glfwWindowShouldClose(window))
	{
		//to do
		processInput(window);

		//填充屏幕颜色
		glClearColor(0.4f, 0.7f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//使用shaderprogram
		ourShader.use();
		//绑定VAO  不需要每帧都绑定
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
//事件触发
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

//每帧回调的方法
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}