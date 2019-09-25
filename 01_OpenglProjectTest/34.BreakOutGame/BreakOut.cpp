#define GLEW_STATIC
#include <glew.1.9.0.1/build/native/include/GL/glew.h>
#include <glfw-3.3.bin.WIN32/include/GLFW/glfw3.h>
#include "Game.h"
#include "resource_manager.h"
//键盘按下方法的声明
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;

Game BreakOut(SCREEN_WIDTH, SCREEN_HEIGHT);
int main(int argc, char* argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//创建窗口
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BreakOut", nullptr, nullptr);
	glfwMakeContextCurrent(window);//联系上下文

	glewExperimental = GL_TRUE;
	glewInit(); //初始化glew
	glGetError(); //获取错误

	glfwSetKeyCallback(window, key_callback);
	//视口
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);//开启面剔除
	glEnable(GL_BLEND); //开启混合
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//进行游戏的初始化
	BreakOut.Init();
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;
	BreakOut.State = GAME_ACTIVE;

	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();
		//管理用户的输入
		BreakOut.ProcessInput(deltaTime);
		//每帧更新游戏状态
		BreakOut.Update(deltaTime);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		BreakOut.Render();

		glfwSwapBuffers(window);

	}
	ResourceManager::Clear();

	glfwTerminate();
	return 0;


}
//键盘按下时调用的方法
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	//键盘抬起或者按下
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			BreakOut.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
		{
			BreakOut.Keys[key] = GL_FALSE;
		}
	}
}