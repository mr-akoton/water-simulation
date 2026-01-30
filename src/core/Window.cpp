#include <core/Window.hpp>

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

Window::Window(void): width(0),
											height(0),
											_id(nullptr),
											_isInit(false) {

}

Window::~Window() {
	destroy();
}

/* ========================================================================== */
/*                              GETTER AND SETTER                             */
/* ========================================================================== */

bool	Window::shouldClose(void) const {
	return _isInit and glfwWindowShouldClose(_id);
}

bool	Window::isKeyPressed(int key) const {
	return _isInit and glfwGetKey(_id, key) == GLFW_PRESS;
}

bool	Window::isKeyReleased(int key) const {
	return _isInit and glfwGetKey(_id, key) == GLFW_RELEASE;
}

/* ========================================================================== */
/*                                    INIT                                    */
/* ========================================================================== */

static void frameBufferSizeCallback(GLFWwindow*, int width, int height) {
	glViewport(0, 0, width, height);
}

int	Window::init(unsigned int width, unsigned int height, const char* title) {
	if (_isInit or width < 100 or height < 100 or title == nullptr) {
		return -1;
	}

	this->width = width;
	this->height = height;
	
	_id = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (_id == nullptr) {
		return -1;
	}

	_isInit = true;
	glfwMakeContextCurrent(_id);
	glfwSetFramebufferSizeCallback(_id, frameBufferSizeCallback);

	return 0;
}

/* ========================================================================== */
/*                                   UPDATE                                   */
/* ========================================================================== */

void	Window::update(void) const {
	if (not _isInit) { return; }

	glfwSwapBuffers(_id);
}

/* ========================================================================== */
/*                                  TERMINATE                                 */
/* ========================================================================== */

void	Window::close(void) const {
	if (not _isInit) { return; }

	if (not this->shouldClose()) {
		glfwSetWindowShouldClose(_id, true);
	}
} 

void	Window::destroy(void) {
	if (not _isInit) { return; }

	glfwDestroyWindow(_id);
	_id = nullptr;
}
