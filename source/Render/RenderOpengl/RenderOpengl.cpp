#include "RenderOpengl.h"

#include "glad/glad.h"
#include "Window.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Shader.h"
#include "Shaders.h"
#include <string>
#include <iostream>

class RenderOpengl::Impl
{
public:
	Impl()
	{
		m_window.setResizeCallback([this] (auto w, int x, int y) {
			glViewport(0, 0, x, y);
			render(); 
		});
	}

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		auto _this = reinterpret_cast<RenderOpengl::Impl*>(glfwGetWindowUserPointer(window));
		glViewport(0, 0, width, height);
		_this->render();
	}

	~Impl()
	{
		glfwTerminate();
	}

	void startRenderLoop()
	{
		prepareTriangle();

        while (!glfwWindowShouldClose(m_window.get()))
        {
			render();
            glfwPollEvents();
        }

		glDeleteVertexArrays(1, &VAO1);
		glDeleteBuffers(1, &VBO1);
		glDeleteBuffers(1, &EBO);
	}

	void showFPS()
	{
		// Measure speed
		double currentTime = glfwGetTime();
		static double lastTime = 0;
		static double nbFrames = 0;
		double delta = currentTime - lastTime;
		
		nbFrames++;

		if (delta >= 1.0) { // If last cout was more than 1 sec ago
			double fps = double(nbFrames) / delta;

			glfwSetWindowTitle(m_window.get(), (std::string( "FPS: " ) + std::to_string(fps)).c_str());
			lastTime = currentTime;

			nbFrames = 0;
		}
	}

	void render()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		showFPS();
	
		
		triangleShader.use();
		
		glBindVertexArray(VAO1);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);


		glBindVertexArray(VAO2);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(m_window.get());
	}

	void prepareTriangle()
	{
		GLfloat vertices[] = {
			-1.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
			 1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		GLuint indices[] = {  // note that we start from 0!
			0, 1, 2,   // first triangle
			//2, 3, 4    // second triangle
		};


		glGenVertexArrays(1, &VAO1);
		glGenBuffers(1, &VBO1);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO1);

		
		glBindBuffer(GL_ARRAY_BUFFER, VBO1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);


		// Second
		glGenVertexArrays(1, &VAO2);
		glGenBuffers(1, &VBO2);
		//glGenBuffers(1, &EBO2);

		glBindVertexArray(VAO2);


		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)-12, vertices + 12, GL_STATIC_DRAW);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
private:
	Window m_window;

	Shader triangleShader{ s_vertex1, s_fragment1 };

	GLuint VBO1 = 0, VAO1 = 0, EBO = 0;
	GLuint VBO2 = 0, VAO2 = 0;
};

RenderOpengl::RenderOpengl()
	: m_impl{ std::make_unique< RenderOpengl::Impl>() }
{

}

RenderOpengl::~RenderOpengl() = default;

void RenderOpengl::startRenderLoop()
{
	m_impl->startRenderLoop();
}
