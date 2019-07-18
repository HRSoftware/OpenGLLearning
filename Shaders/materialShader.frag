#version 440 core


struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	float shininess;
};

struct Light{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos; //position of the light source


uniform float ambientStrength = 0.1f;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform Material material;
uniform Light light;


out vec4 FragColor;

void main()
{
	//ambient
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));

	//texture_diffuse1
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 texture_diffuse1 = light.diffuse * diff * vec3(texture(material.texture_diffuse1, TexCoords));

	//texture_specular1
	vec3 viewDir = normalize(-FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 texture_specular1 =  light.specular * spec * vec3(texture(material.texture_specular1, TexCoords));

	vec3 result = ambient + texture_diffuse1 + texture_specular1;
	FragColor = vec4(result, 1.0f);
}