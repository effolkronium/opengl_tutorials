#include "RenderOpengl.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include <string>
#include <iostream>

class RenderOpengl::Impl
{
public:
	Impl()
	{
		if (!glfwInit())
			throw std::runtime_error{ "glfwInit has failed" };

		glfwSetErrorCallback(errorCcallback);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(800, 600, "My Title", NULL, NULL);
		if (!m_window)
			throw std::runtime_error{ "glfwCreateWindow has failed" };

		glfwMakeContextCurrent(m_window);

		// Unlimited fps
		//glfwSwapInterval(0);

		glfwSetWindowUserPointer(m_window, this);

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
			throw std::runtime_error{ "gladLoadGLLoader has failed" };

		glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

		enableLogging();
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

        while (!glfwWindowShouldClose(m_window))
        {
			render();
            glfwPollEvents();
        }

		glDeleteVertexArrays(1, &VAO1);
		glDeleteBuffers(1, &VBO1);
		glDeleteBuffers(1, &EBO);
		glDeleteProgram(shaderProgram);
		glDeleteProgram(shaderProgram2);
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

			glfwSetWindowTitle(m_window, (std::string( "FPS: " ) + std::to_string(fps)).c_str());
			lastTime = currentTime;

			nbFrames = 0;
		}
	}

	void render()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		showFPS();
	
		glUseProgram(shaderProgram);

		glBindVertexArray(VAO1);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glUseProgram(shaderProgram2);

		glBindVertexArray(VAO2);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(m_window);
	}

	void prepareTriangle()
	{
		// Vertex shader

		auto vertexShaderSource = 
R"(#version 460 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
})";

		unsigned int vertexShader = 0;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		int success = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);


		if (!success)
		{
			char infoLog[512] = { 0 };
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			throw std::runtime_error{ std::string("ERROR::SHADER::VERTEX::COMPILATION_FAILED: ") + infoLog };
		}


		// Fragment shader

		auto fragmentShaderSource = 
R"(#version 460 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
})";

		unsigned int fragmentShader = 0;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);


		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);


		if (!success)
		{
			char infoLog[512] = { 0 };
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);

			throw std::runtime_error{ std::string("ERROR::SHADER::VERTEX::COMPILATION_FAILED: ") + infoLog };
		}

		// Fragment shader

		auto fragmentShaderSource2 =
R"(#version 460 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.0f, 0.5f, 0.8f, 1.0f);
})";

		unsigned int fragmentShader2 = 0;
		fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
		glCompileShader(fragmentShader2);


		glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);


		if (!success)
		{
			char infoLog[512] = { 0 };
			glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);

			throw std::runtime_error{ std::string("ERROR::SHADER::VERTEX::COMPILATION_FAILED: ") + infoLog };
		}

		// Link shaders

		shaderProgram = glCreateProgram();
		
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512] = { 0 };
			glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);

			throw std::runtime_error{ std::string("ERROR::SHADER::VERTEX::LINKING_FAILED: ") + infoLog };
		}

		shaderProgram2 = glCreateProgram();

		glAttachShader(shaderProgram2, vertexShader);
		glAttachShader(shaderProgram2, fragmentShader2);
		glLinkProgram(shaderProgram2);

		glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512] = { 0 };
			glGetShaderInfoLog(shaderProgram2, 512, NULL, infoLog);

			throw std::runtime_error{ std::string("ERROR::SHADER::VERTEX::LINKING_FAILED: ") + infoLog };
		}
		
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteShader(fragmentShader2);


		GLfloat vertices[] = {
			-1.0f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.0f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			 1.0f, -0.5f, 0.0f,
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

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);


		// Second
		glGenVertexArrays(1, &VAO2);
		glGenBuffers(1, &VBO2);
		//glGenBuffers(1, &EBO2);

		glBindVertexArray(VAO2);


		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)-6, vertices + 6, GL_STATIC_DRAW);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	static void errorCcallback(int error, const char* description)
	{
		std::cerr << "glfwError #" << error << " ; desc: " << description << std::endl;
	}

	void enableLogging()
	{
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(logCallback, this);
	}

	static void APIENTRY logCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
	{
		auto source_str = [source]() -> std::string {
			switch (source)
			{
			case GL_DEBUG_SOURCE_API: return "API";
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
			case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
			case GL_DEBUG_SOURCE_THIRD_PARTY:  return "THIRD PARTY";
			case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
			case GL_DEBUG_SOURCE_OTHER: return "OTHER";
			default: return "UNKNOWN";
			}
		}();

		auto type_str = [type]() {
			switch (type)
			{
			case GL_DEBUG_TYPE_ERROR: return "ERROR";
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
			case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
			case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
			case GL_DEBUG_TYPE_MARKER:  return "MARKER";
			case GL_DEBUG_TYPE_OTHER: return "OTHER";
			default: return "UNKNOWN";
			}
		}();

		auto severity_str = [severity]() {
			switch (severity) {
			case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
			case GL_DEBUG_SEVERITY_LOW: return "LOW";
			case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
			case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
			default: return "UNKNOWN";
			}
		}();

		std::cout << source_str << ", "
			<< type_str << ", "
			<< severity_str << ", "
			<< id << ": "
			<< message << std::endl;
	}
private:
	GLFWwindow* m_window = nullptr;

	GLuint VBO1 = 0, VAO1 = 0, EBO = 0, shaderProgram = 0;
	GLuint VBO2 = 0, VAO2 = 0, shaderProgram2;
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
