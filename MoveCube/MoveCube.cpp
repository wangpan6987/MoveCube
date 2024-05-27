// MoveCube.cpp: 定义应用程序的入口点。
//

/* 引入相应的库 */
#include <iostream>
using namespace std;

#include "Shader.h"
#include <GL\glew.h>					// 注：这一部分要根据个人情况进行设定
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// 深度测试

/* 编写各顶点位置 */
float vertices_1[] = {
	// x、y、z 坐标				// color
	-0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	// red 红色面
	 0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,	// green 绿色面
	 0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,	// blue 蓝色面
	-0.5f,  0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,

	 0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,	// yellow 黄色面
	 0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	// purple 紫色面
	 0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,	// cyan 青色面
	 0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,
};


const GLint WIDTH = 600, HEIGHT = 600;

int main()
{
	/* 初始化 */
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// 告诉系统 版本是为了opengl画图准备的  支持3.0以后的版本 是新的  3.3
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);			// must for Mac(Windows可不加) 启动兼容
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);						// 缩放关闭

	/* 窗口捕获与处理 */
	GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "NJUPT_Learn OpenGL Earth-moon System", nullptr, nullptr);
	int screenWidth_1, screenHeight_1;
	glfwGetFramebufferSize(window_1, &screenWidth_1, &screenHeight_1);
	cout << "screenWidth_1 = " << screenWidth_1 << ", screenHeight = " << screenHeight_1 << endl;
	glewExperimental = GL_TRUE;
	glfwMakeContextCurrent(window_1);
	glewInit();

	/* 开启深度测试 */
	glEnable(GL_DEPTH_TEST);

	/* 将我们自己设置的着色器文本传进来 */
	Shader ourShader = Shader("shader_v.txt", "shader_f.txt");		// 相对路径

	/* 设置顶点缓冲对象(VBO) + 设置顶点数组对象(VAO) */
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);

	/* 设置链接顶点属性 */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);	// 通道 0 打开
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);	// 通道 1 打开

	/* draw loop 画图循环 */
	while (!glfwWindowShouldClose(window_1))
	{
		/* 视口 + 时间 */
		glViewport(0, 0, screenWidth_1, screenHeight_1);
		glfwPollEvents();

		/* 渲染 + 清除颜色缓冲 */
		glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* 绘制图形 */
		ourShader.Use();
		glBindVertexArray(VAO);
		for (int i = 0; i < 2; i++)
		{
			GLfloat time = glfwGetTime();	// 获取时间
			//glm::mat4 transform_1;		//不会默认初始化单位矩阵，被坑惨了
			glm::mat4 transform_1 = glm::mat4(1.0f); // 初始化为单位矩阵
			if (i == 0)					// 大立方体
			{
				transform_1 = glm::scale(transform_1, glm::vec3(0.6f, 0.6f, 0.6f));
				transform_1 = glm::rotate(transform_1, time, glm::vec3(0.2f, 1.0f, 0.0f));
			}
			else							// 小立方体
			{
				transform_1 = glm::translate(transform_1, glm::vec3(0.8f * cos(time), 0.8f * sin(time), 0.0f));
				transform_1 = glm::scale(transform_1, glm::vec3(0.15f, 0.15f, 0.15f));
				transform_1 = glm::rotate(transform_1, time, glm::vec3(0.5f, 0.5f, 0.0f));
			}

			int transform_1_Location = glGetUniformLocation(ourShader.Program, "transform_1");
			glUniformMatrix4fv(transform_1_Location, 1, GL_FALSE, glm::value_ptr(transform_1));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);				// 解绑定 VAO
		/* 交换缓冲 */
		glfwSwapBuffers(window_1);
	}

	/* 释放资源 */
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();	// 结束
	return 0;
}
