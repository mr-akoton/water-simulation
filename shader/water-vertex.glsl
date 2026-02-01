#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;

uniform int u_iteration;
uniform mat4 u_projection;
uniform mat4 u_model;
uniform mat3 u_imodel;
uniform float u_time;

uniform float u_frequency;
uniform float u_speed;
uniform float u_amplitude;
uniform float u_iterationSeed;
uniform float u_maxPeak;
uniform float u_peakOffset;
uniform float u_speedScale;
uniform float u_frequencyScale;
uniform float u_amplitudeScale;
uniform float u_drag;

out vec3 p_fragPosition;
out vec3 p_color;
out vec3 p_normal;

// x: derivative of x, y: wave height, z: derivative of z
vec3	getWaveData(vec2 position, vec2 direction, float amplitude, float frequency, float speed) {
	float	phase = speed * frequency;

	float	x = dot(direction, position) * frequency + u_time * speed;
	float	wave = amplitude * exp(sin(x) - 1.0f);
	vec2	derivative = amplitude * direction * frequency * exp(sin(x) - 1.0f) * cos(x);

	return vec3(derivative.x, wave, derivative.y);
}

void	main() {
	vec3	waveData = vec3(0.0f);
	vec3	position = in_position;
	float	waveIteration = 1.0f;

	float	amplitude = u_amplitude;
	float	frequency = u_frequency;
	float	speed = u_speed;

	// Sum of waves
	for (int i = 0; i < u_iteration; i++) {
		vec2	direction = normalize(vec2(sin(waveIteration), cos(waveIteration)));

		vec3	wave = getWaveData(position.xz, direction, amplitude, frequency, speed);
		position.xz += wave.xz * direction * amplitude * u_drag;
		waveData += wave;

		amplitude *= u_amplitudeScale;
		frequency *= u_frequencyScale;
		speed *= u_speedScale;
		waveIteration += u_iterationSeed;
	}

	// Extract final data
	float wave = waveData.y;
	vec3 normal = normalize(vec3(-waveData.x, 1.0f, -waveData.z));
	normal = normalize(u_imodel * normal);

	// Vertex position
	vec4 worldPosition = u_model * vec4(in_position.x, in_position.y + wave, in_position.z, 1.0);
	gl_Position = u_projection * worldPosition;

	// Pass to vertex
	p_fragPosition = worldPosition.xyz;
	p_normal = normal;
	p_color = in_color;
}
