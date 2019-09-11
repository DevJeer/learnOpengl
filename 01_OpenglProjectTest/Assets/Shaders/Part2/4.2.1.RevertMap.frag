#version 330 core
out vec4 FragColor;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
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
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	//ambient  将texture进行赋值
	vec3 ambient = light.ambient * texture(material.diffuse,TexCoords).rgb;
	//diffuse   漫反射需要与贴图的rgb混合
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm,lightDir),0.0f);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoords).rgb;
	
	//specular 
	vec3 viewDir = normalize(viewPos - FragPos);
	//取反射方向
	vec3 reflectDir = reflect(-lightDir,norm);
	float sepc = pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
	//将铁框与木箱材质的specualrMap取反
	//木箱材质高光显示  铁框不高光显示
	vec3 specular = light.specular * sepc * (vec3(1.0f) - texture(material.specular,TexCoords).rgb);
	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result,1.0f);
	
	
}