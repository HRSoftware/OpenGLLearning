#version 440 core
out vec4 FragColor;

in VS_OUT{
  vec3 FragPos;
  vec3 Normal;
  vec2 TexCoords;
  vec4 FragPosLightSpace;
}fs_in;


uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_height1;

uniform float shininess;

struct Light{
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float intensity;
  vec3 direction;
};

uniform sampler2D shadowMap;

uniform vec3 viewPos;

uniform Light light;

float ShadowCalculation(vec4 fragPosLightSpace)
{
  // perform perspective divide
  vec3 projCoords=fragPosLightSpace.xyz/fragPosLightSpace.w;
  // transform to [0,1] range
  projCoords=projCoords*.5+.5;
  // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
  float closestDepth=texture(shadowMap, projCoords.xy).r;
  // get depth of current fragment from light's perspective
  float currentDepth=projCoords.z;
  // check whether current frag pos is in shadow
  float shadow=currentDepth>closestDepth?1.:0.;
  
  return shadow;

}

void main()
{


  vec3 normal = normalize(fs_in.Normal);
  vec3 color=texture(texture_diffuse1,fs_in.TexCoords).rgb;
  // ambient
  vec3 ambient = (light.ambient * color) * light.intensity;


  // diffuse
  vec3 lightDir = normalize(light.direction - fs_in.FragPos);
  float diff = max(dot(lightDir , normal), 0.);
  vec3 diffuse = light.diffuse * diff * texture(texture_diffuse1, fs_in.TexCoords).rgb;

  // specular
  vec3 viewDir = normalize(viewPos - fs_in.FragPos);
  vec3 halfwayDir = normalize(lightDir + viewDir);

  float spec = pow( max( dot( normal, halfwayDir), 0.f), 64.0);
  vec3 specular = light.specular * spec * texture(texture_specular1, fs_in.TexCoords).rgb;

 
  // calculate shadow
  float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
  vec3 projCoords= fs_in.FragPosLightSpace.xyz / fs_in.FragPosLightSpace.w;
  vec3 lighting = (ambient + (1.0-shadow) * (diffuse + specular));
  
  FragColor = vec4(lighting, 1.);


}

