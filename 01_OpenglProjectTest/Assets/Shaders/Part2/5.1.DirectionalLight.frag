#version 330 core
out vec4 FragColor;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	//sampler2D emission; //放射贴图采样器
	float shininess;  //反光度
};
struct Light
{
	//vec3 position;
	vec3 direction;
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
	
	//diffuse   漫反射需要与贴图的rgb混合  directional light是漫反射  而且它只受场景中光源的方向的影响
	vec3 norm = normalize(Normal);
	//directional light 是影响所有物体的shader
	vec3 lightDir = normalize(-light.direction);  //0 - > position  取反就可以照射到物体啦
	float diff = max(dot(norm,lightDir),0.0f);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoords).rgb;
	
	//specular 
	vec3 viewDir = normalize(viewPos - FragPos);
	//取反射方向
	vec3 reflectDir = reflect(-lightDir,norm);
	float sepc = pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
	vec3 specular = light.specular * sepc * texture(material.specular,TexCoords).rgb;
	
	//emission
	//vec3 emission = texture(material.emission,TexCoords).rgb;

	//vec3 result = ambient + diffuse + specular +emission;
	vec3 result = ambient + diffuse + specular ;
	FragColor = vec4(result,1.0f);
	
	
}