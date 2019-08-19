#version 440 core


uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_height1;
uniform float shininess;


struct Light{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform float ambientStrength = 0.5f;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform Light light;
uniform vec3 viewPos;


out vec4 FragColor;

void main()
{

	vec3 lightDir = normalize(light.position - FragPos);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);

	//ambient
	vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));

	vec3 height=texture(texture_height1,TexCoords).rgb;
	height=normalize(height * 2. - 1.);

	//diffuse
	vec3 norm = normalize(Normal);
	norm = texture(texture_height1,TexCoords).rgb;
	norm = normalize(norm * 2.0f - 1.0f);
	
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));

	//specular
	//vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, halfwayDir), 0.0f), shininess);
	vec3 specular =  light.specular * spec * vec3(texture(texture_specular1, TexCoords));


	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0f);
}