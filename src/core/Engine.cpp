#include <core/Engine.hpp>
#include <fstream>
#include <iostream>

using namespace glm;

/* ========================================================================== */
/*                         CONSTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

constexpr int					WINDOW_WIDTH = 1280;
constexpr int 				WINDOW_HEIGHT = 720;
constexpr const char*	WINDOW_TITLE = "OpenGL - Water";

Engine::Engine(void):
	camera(WINDOW_WIDTH, WINDOW_HEIGHT, vec3(250.0f, 150.0f, -100.0f)),
	_lastFrame(0.0f),
	_deltaTime(0.0f),
	_frameCount(0) {

	_initGLFW();
	if (window.init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE) == -1) {
		glfwTerminate();
		throw Engine::WindowInitFailedException();
	}
	_initGLAD();
	interface.init(window);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

Engine::~Engine() {
	window.destroy();
	interface.shutdown();
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
	Water	water(500, 500);
	water.init(vec3(0.172f, 0.3412f, 0.4667f));

	vec3	lightDirection(0.2f, 0.8f, 1.0f);
	vec3	lightColor(1.0f, 1.0f, 1.0f);

	float	lastTime = glfwGetTime();
	char	fpsText[100] = "Debug: 0 ms/frame";

	float	waveRool = 2.0f;
	float waveSteepness = 0.0f;

	while (not window.shouldClose()) {
		glfwPollEvents();
		_handleInput();
		_updateDeltaTime();

		_frameCount++;
		if (glfwGetTime() - lastTime >= 1.0f) {
			sprintf(fpsText, "Debug: %f ms/frame", 1000.0/double(_frameCount));
			_frameCount = 0;
			lastTime += 1.0f;
		}

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.updateMatrix(45.0f, 0.1f, 1000.0f);

		if (not interface.wantCaptureMouse()) {
			camera.handleInput(window, _deltaTime);
		}

		water.shader.setFloat("u_waveRool", waveRool);
		water.shader.setFloat("u_waveSteepness", waveSteepness);
		water.render(camera, lightDirection, lightColor);

		interface.createFrame();
		
		ImGui::Begin("Setting");
		ImGui::Text(fpsText);
		ImGui::Text("Water");
		ImGui::SliderInt("Iteration", &water.iteration, 1, 100, "%d");
		ImGui::InputFloat("Amplitude", &water.amplitude);
		ImGui::InputFloat("Frequency", &water.frequency);
		ImGui::InputFloat("Speed", &water.speed);
		ImGui::Text("Wave Tuning");
		ImGui::InputFloat("Iteration Seed", &water.iterationSeed);
		ImGui::InputFloat("Amplitude Scale", &water.amplitudeScale);
		ImGui::InputFloat("Frequency Scale", &water.frequencyScale);
		ImGui::InputFloat("Speed Scale", &water.speedScale);
		ImGui::InputFloat("Roll", &waveRool);
		ImGui::SliderFloat("Steepness", &waveSteepness, 0.0f, 1.0f, "%.3f");
		ImGui::Text("Light");
		ImGui::SliderFloat3("Direction", value_ptr(lightDirection), -1, 1, "%.3f");
		ImGui::ColorEdit3("Color", value_ptr(lightColor));
		ImGui::End();
		interface.render();

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
