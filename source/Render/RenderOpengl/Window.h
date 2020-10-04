#include "GLFW/glfw3.h"
#include <functional>

class Window
{
public:
	Window();
	~Window();

	using resizeCallback_t = std::function<void(GLFWwindow*, int, int)>;

	GLFWwindow* get();

	void setResizeCallback(resizeCallback_t resizeCallback);
	const resizeCallback_t& getResizeCallback();
private:
	GLFWwindow* m_window = nullptr;
	resizeCallback_t m_resizeCallback = [] (auto...) { };
};