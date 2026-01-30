#include <core/Object.hpp>

/* ========================================================================== */
/*                          CONTRUCTOR AND DESTRUCTOR                         */
/* ========================================================================== */

VBO::VBO(const std::vector<Vertex>& vertices) {
	glGenBuffers(1, &_id);
	this->bind();
	glBufferData(GL_ARRAY_BUFFER,
							 vertices.size() * sizeof(Vertex),
							 vertices.data(),
							 GL_DYNAMIC_DRAW);
	this->unbind();
}

VBO::~VBO() {
	glDeleteBuffers(1, &_id);
}

/* ========================================================================== */
/*                                   BINDER                                   */
/* ========================================================================== */

void	VBO::bind(void) const {
	glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void	VBO::unbind(void) const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
