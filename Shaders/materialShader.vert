#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangentCoords;
layout (location = 4) in vec3 aBitangentCoords;

out vec3 FragPos;
out vec3 Normal;
out vec3 LightPos;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

void main()
{
  gl_Position = projection * view * model * vec4(aPos, 1.0f);
	FragPos = vec3(view * model * vec4(aPos, 1.0f));
	Normal = mat3(transpose(inverse(model))) * aNormal;

	LightPos = vec3(view * vec4(lightPos, 1.0f));
	
	TexCoords = aTexCoords;
} 