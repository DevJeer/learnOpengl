#define GLEW_STATIC
#include <glew.1.9.0.1/build/native/include/GL/glew.h>
#include <glfw-3.3.bin.WIN32/include/GLFW/glfw3.h>
#include "Game.h"
#include "resource_manager.h"
//���̰��·���������
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
	//��������
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BreakOut", nullptr, nullptr);
	glfwMakeContextCurrent(window);//��ϵ������

	glewExperimental = GL_TRUE;
	glewInit(); //��ʼ��glew
	glGetError(); //��ȡ����

	glfwSetKeyCallback(window, key_callback);
	//�ӿ�
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);//�������޳�
	glEnable(GL_BLEND); //�������
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//������Ϸ�ĳ�ʼ��
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
		//�����û�������
		BreakOut.ProcessInput(deltaTime);
		//ÿ֡������Ϸ״̬
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
//���̰���ʱ���õķ���
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	//����̧����߰���
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