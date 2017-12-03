// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "gl_warp.h"
#include "Shader.h"
#include "stb_image.h"

typedef int *iptr;

const char *vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;"
"layout (location = 1) in vec3 aColor;"
"layout (location = 2) in vec2 aTexCoord;"
"out vec3 ourColor;"
"out vec2 TexCoord;"
"void main() {"
"	gl_Position = vec4(aPos, 1.0);"
"	ourColor = aColor;"
"	TexCoord = aTexCoord;"
"}";

const char *fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;"
"in vec3 ourColor;"
"in vec2 TexCoord;"
"uniform sampler2D ourTexture;"
"void main() {"
"	FragColor = texture(ourTexture, TexCoord);"
"}";

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {
	float vertices[] = {
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3,
	};

	GLFWwindow *window = gl_warp_init();
	Shader ourShader(vertexShaderSource, fragmentShaderSource, true);

	unsigned int vbo, vao, ebo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int texture = texture_load("resources/textures/container.jpg");

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(.2, .3, .3, 1.);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture);
		ourShader.use();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glfwTerminate();
	return EXIT_SUCCESS;
}
