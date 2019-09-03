#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
//uniform vec3 lightPos;
//uniform vec3 viewPos;

void main()
{
	//环境光强度
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;
	
	//diffuse 漫反射
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm,lightDir),0.0f);
	vec3 diffuse = diff * lightColor;
	
	//specular 镜面高光
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(- FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f),32);
	vec3 specular = specularStrength * spec * lightColor;
	
	vec3 result = (ambient + diffuse + specular) * objectColor;
	//片段着色器
	FragColor = vec4(result,1.0f);
}