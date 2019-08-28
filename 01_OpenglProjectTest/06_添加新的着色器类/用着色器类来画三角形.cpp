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
	//��ʼ��glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//����window����
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Work Work OWO", NULL, NULL);

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glad ����������opengl����ĺ���ָ���  �����ڵ����κ�opengl�ĺ���֮ǰ���ó�ʼ������glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//�����ͱ���Shader
	Shader ourShader("E:/vs2015project/01_OpenglProjectTest/Assets/Shaders/3.3.shader.vs", "E:/vs2015project/01_OpenglProjectTest/Assets/Shaders/3.3.shader.fs");

	//�����ζ���  ����ɫ
	float vertices[] = {
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	unsigned int VAO, VBO;
	//���ɶ����������  ��������Ե��ûᴢ�浽VAO��
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//�󶨶����������
	glBindVertexArray(VAO);
	//�󶨻�����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//���ö�������ָ��
	//λ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//��ɫ
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//�ͷ�buffer  ����VAO�����Ѿ���ԭ���Ķ���������
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//��ѭ��
	while (!glfwWindowShouldClose(window))
	{
		//to do
		processInput(window);

		//�����Ļ��ɫ
		glClearColor(0.4f, 0.7f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//ʹ��shaderprogram
		ourShader.use();
		//��VAO  ����Ҫÿ֡����
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
//�¼�����
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

//ÿ֡�ص��ķ���
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}