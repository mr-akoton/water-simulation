#version 330 core

in vec3	p_color;
out vec4 FragColor;

void	main() {
	FragColor = vec4(p_color, 1.0f);
}
