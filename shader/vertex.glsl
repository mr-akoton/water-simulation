#version 330 core

layout (location = 0) in vec3	in_position;
layout (location = 1) in vec3	in_color;

uniform mat4	u_projection;
uniform mat4	u_model;

out vec3	p_color;

void	main() {
	gl_Position = u_projection * u_model * vec4(in_position, 1.0f);
	p_color = in_color;
}
