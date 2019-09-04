#version 330 core
out vec4 FragColor;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;  //反光度
};
struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	//ambient
	vec3 ambient = light.ambient * material.ambient;
	
	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm,lightDir),0.0f);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);
	
	//specular
	vec3 viewDir = normalize(viewPos - FragPos);
	//取反射方向
	vec3 reflectDir = reflect(-lightDir,norm);
	float sepc = pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
	vec3 specular = light.specular * (sepc * material.specular);
	
	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result,1.0f);
	
	
}