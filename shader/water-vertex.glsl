#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;

uniform mat4 u_projection;
uniform mat4 u_model;
uniform mat3 u_imodel;
uniform float u_time;

uniform float u_frequency;
uniform float u_speed;
uniform float u_amplitude;
uniform float u_iterationSeed;
uniform float u_speedScale;
uniform float u_frequencyScale;
uniform float u_amplitudeScale;

uniform int u_waveIteration;
uniform	float u_waveRool;
uniform	float u_waveSteepness;

out vec3 p_fragPosition;
out vec3 p_color;
out vec3 p_normal;

vec3	getWaveDisplacement(vec2 position, vec2 direction, float amplitude, float frequency, float speed, float steepness) {
	float	theta = dot(direction, position) * frequency + u_time * speed;
	
	float	y = amplitude * sin(theta);
	vec2	xz = steepness * amplitude * direction * cos(theta);

	return vec3(xz.x, y, xz.y);
}

void	main() {
	vec3	totalDisplacement = vec3(0.0f);
	vec3	normalData = vec3(0.0f);
	vec3	position = in_position;
	float	waveIteration = 1.0f;

	float	amplitude = u_amplitude;
	float	frequency = u_frequency;
	float	speed = u_speed;

	// Sum of waves
	for (int i = 0; i < u_waveIteration; i++) {
		vec2	direction = normalize(vec2(sin(waveIteration), cos(waveIteration)));

		float 	steepness = u_waveSteepness / (frequency * amplitude * u_waveIteration);
		vec3	displacement = getWaveDisplacement(position.xz, direction, amplitude, frequency, speed, steepness);
		
		totalDisplacement += displacement;

		float	theta = dot(direction, position.xz) * frequency + u_time * speed;
		normalData.x += direction.x * frequency * amplitude * cos(theta);
		normalData.z += direction.y * frequency * amplitude * cos(theta);
		normalData.y += steepness * frequency * amplitude * sin(theta);

		amplitude *= u_amplitudeScale;
		frequency *= u_frequencyScale;
		speed *= u_speedScale;
		waveIteration += u_iterationSeed;
	}

	// Extract final data
	vec3 normal = normalize(vec3(-normalData.x, 1 - normalData.y, -normalData.z));
	normal = normalize(u_imodel * normal);

	// Vertex position
	vec4 worldPosition = u_model * vec4(in_position + totalDisplacement, 1.0);
	gl_Position = u_projection * worldPosition;

	// Pass to vertex
	p_fragPosition = worldPosition.xyz;
	p_normal = normal;
	p_color = in_color;
}

