
#version 440 core
out vec4 FragColor;


uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_height1;
uniform float shininess;


struct Light{
	vec3 position;
	float strength;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Light light;

void main()
{
	// ambient
	vec3 ambient = light.ambient * texture(texture_diffuse1, TexCoords).rgb;
	
	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max( dot( norm, lightDir), 0.f);
	vec3 diffuse = light.diffuse * diff * texture(texture_diffuse1, TexCoords).rgb;
	
	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow( max( dot( viewDir, reflectDir), 0.f), shininess);
	vec3 specular = light.specular * spec * texture( texture_specular1, TexCoords).rgb;
	
	vec3 result = (ambient + diffuse + specular) * light.strength;
	FragColor=vec4(result,1.f);
}

