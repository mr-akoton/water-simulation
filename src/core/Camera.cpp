#include <core/Camera.hpp>

using namespace glm;

/* ========================================================================== */
/*                                 CONSTRUCTOR                                */
/* ========================================================================== */

Camera::Camera(unsigned int width, unsigned int height, vec3 position):
	width(width),
	height(height),
	ratio((float)width / height),
	up(0.0f, 1.0f, 0.0f),
	position(position),
	orientation(1.0f, 0.0f, 0.0f),
	matrix(1.0f) {

}

/* ========================================================================== */
/*                                   UPDATE                                   */
/* ========================================================================== */

void	Camera::updateMatrix(float fov, float near, float far) {
	mat4	view(1.0f);
	mat4	projection(1.0f);

	view = lookAt(position, position + orientation, up);
	projection = perspective(radians(fov), ratio, near, far);
	matrix = projection * view;
}

void	Camera::updateShaderMatrix(const Shader& shader,
																 const std::string uniform) {
	shader.setMat4(uniform, matrix);
}
