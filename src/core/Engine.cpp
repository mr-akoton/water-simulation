#include <core/Engine.hpp>
#include <fstream>
#include <iostream>

using namespace glm;

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

constexpr int					WINDOW_WIDTH = 900;
constexpr int 				WINDOW_HEIGHT = 600;
constexpr const char*	WINDOW_TITLE = "OpenGL - Water";
constexpr const char*	VERTEX_SHADER = "shader/vertex.glsl";
constexpr const char*	FRAGMENT_SHADER = "shader/fragment.glsl";

static bool	isFileValid(const std::string path) {
	std::ifstream	file(path);
	return file.is_open();
}

Engine::Engine(void):
	camera(WINDOW_WIDTH, WINDOW_HEIGHT, vec3(-10.0f, 0.0f, 0.0f)),
	_lastFrame(0),
	_deltaTime(0) {

	if (not isFileValid(VERTEX_SHADER)) {
		std::string error = "Error: failed to open " + std::string(VERTEX_SHADER);
		throw std::runtime_error(error);
	} else if (not isFileValid(FRAGMENT_SHADER)) {
		std::string error = "Error: failed to open " + std::string(FRAGMENT_SHADER);
		throw std::runtime_error(error);
	}

	_initGLFW();
	if (window.init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE) == -1) {
		glfwTerminate();
		throw Engine::WindowInitFailedException();
	}
	_initGLAD();

	glEnable(GL_DEPTH_TEST);
}

Engine::~Engine() {
	window.destroy();
	glfwTerminate();
}

/* ========================================================================== */
/*                                    INIT                                    */
/* ========================================================================== */

void	Engine::_initGLFW(void) const {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);
}

void	Engine::_initGLAD(void) const {
	if (not gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		window.close();
		glfwTerminate();
		throw Engine::GladLoadFailedException();
	}
}

/* ========================================================================== */
/*                                     RUN                                    */
/* ========================================================================== */

void Engine::run(void) {
	Shader	shader(VERTEX_SHADER, FRAGMENT_SHADER);
	std::vector<Vertex>	vertices = {
		Vertex{ vec3( -1.0f, -1.0f,  1.0f), vec3(0.0f, 0.0f, 0.0f)},
		Vertex{ vec3(  1.0f, -1.0f,  1.0f), vec3(0.0f, 0.0f, 1.0f)},
		Vertex{ vec3(  1.0f,  1.0f,  1.0f), vec3(0.0f, 1.0f, 0.0f)},
		Vertex{ vec3( -1.0f,  1.0f,  1.0f), vec3(0.0f, 1.0f, 1.0f)},
		Vertex{ vec3( -1.0f, -1.0f, -1.0f), vec3(1.0f, 0.0f, 0.0f)},
		Vertex{ vec3(  1.0f, -1.0f, -1.0f), vec3(1.0f, 0.0f, 1.0f)},
		Vertex{ vec3(  1.0f,  1.0f, -1.0f), vec3(1.0f, 1.0f, 0.0f)},
		Vertex{ vec3( -1.0f,  1.0f, -1.0f), vec3(1.0f, 1.0f, 1.0f)},
	};
	std::vector<GLuint> indices = {
		0, 1, 2,  0, 2, 3,
		1, 5, 6,  1, 6, 2,
		5, 4, 7,  5, 7, 6,
		4, 0, 3,  4, 3, 7,
		3, 2, 6,  3, 6, 7,
		4, 5, 1,  4, 1, 0,
	};

	VAO	vao;
	vao.bind();
	VBO	vbo(vertices);
	vbo.bind();
	EBO ebo(indices);
	ebo.bind();

	vao.linkAttribute(vbo, 0, 3, GL_FLOAT, sizeof(Vertex),
										(void*)(0));
	vao.linkAttribute(vbo, 1, 3, GL_FLOAT, sizeof(Vertex),
										(void*)(3 * sizeof(float)));
	
	vao.unbind();
	vbo.unbind();
	ebo.unbind();

	vec3 position(0.0f);
	vec3 rotation(1.0f, -1.0f, 0.5f);
	mat4 model(1.0f);
	model = translate(model, position);
	model = rotate(model, (float)radians(1.0f), rotation);

	while (not window.shouldClose()) {
		glfwPollEvents();
		_handleInput();
		_updateDeltaTime();

		glClearColor(0.3f, 0.04f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.updateMatrix(45, 0.1f, 1000.0f);
		model = rotate(model, _deltaTime, rotation);

		vao.bind();
	
		shader.enable();
		camera.updateShaderMatrix(shader, "u_projection");
		shader.setMat4("u_model", model);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		window.update();
	}
}

/* ========================================================================== */
/*                                    INPUT                                   */
/* ========================================================================== */

void	Engine::_handleInput(void) const {
	if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
		window.close();
	}
}

/* ========================================================================== */
/*                                    FRAME                                   */
/* ========================================================================== */

void	Engine::_updateDeltaTime(void) {
	float currentFrame = glfwGetTime();

	_deltaTime = currentFrame - _lastFrame;
	_lastFrame = currentFrame;
}

/* ========================================================================== */
/*                                  EXCEPTION                                 */
/* ========================================================================== */

const char*	Engine::WindowInitFailedException::what(void) const noexcept {
	return "Exception: failed while initiating the window";
}

const char*	Engine::GladLoadFailedException::what(void) const noexcept {
	return "Exception: failed while loading GLAD";
}
