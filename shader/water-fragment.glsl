#version 330 core

uniform vec3	u_lightDirection;
uniform vec3	u_lightColor;
uniform vec3    u_viewPosition;

in vec3	p_color;
in vec3	p_normal;
in vec3 p_fragPosition;

out vec4 fragColor;

vec3	getLight() {
	float	ambient = 0.2f;
	float	specularStrength = 1.0f;

	// Diffuse lighting
	vec3	normal = normalize(p_normal);
	vec3	lightDirection = normalize(u_lightDirection);
	float	diffuse = max(dot(lightDirection, normal), 0.0f);

	// Specular reflection
	vec3	viewDirection = normalize(u_viewPosition - p_fragPosition);
	vec3	reflection = normalize(reflect(-lightDirection, normal));
	float	specular = pow(max(dot(reflection, viewDirection), 0.0f), 32.0f) * specularStrength;

	return p_color * (ambient + (diffuse + specular) * u_lightColor);
}

void	main() {
	fragColor = vec4(getLight(), 1.0f);
}
