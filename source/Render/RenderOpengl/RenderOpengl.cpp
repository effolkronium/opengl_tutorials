#include "RenderOpengl.h"

#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include <iostream>

class RenderOpengl::Impl
{
public:
	Impl()
	{
		if (!glfwInit())
			throw std::runtime_error{ "glfwInit has failed" };

		glfwSetErrorCallback(errorCcallback);

		m_window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
		if (!m_window)
			throw std::runtime_error{ "glfwCreateWindow has failed" };

		glfwMakeContextCurrent(m_window);

		if(!gladLoadGL(glfwGetProcAddress))
			throw std::runtime_error{ "gladLoadGL has failed" };

		glfwSwapInterval(1);
	}

	~Impl()
	{
		glfwTerminate();
	}

	void run()
	{
        while (!glfwWindowShouldClose(m_window))
        {
            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
	}

	static void errorCcallback(int error, const char* description)
	{
		std::cerr << "glfwError #" << error << " ; desc: " << description << std::endl;
	}
private:
	GLFWwindow* m_window = nullptr;
};

RenderOpengl::RenderOpengl()
	: m_impl{ std::make_unique< RenderOpengl::Impl>() }
{

}

RenderOpengl::~RenderOpengl() = default;

void RenderOpengl::run()
{
	m_impl->run();
}
