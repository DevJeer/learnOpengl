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
	vec3 position;  //pointlight是需要一个位置的
	vec3 direction;
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	vec3 lightDir = normalize(light.position - FragPos);  
	float theta = dot(lightDir,normalize(-light.direction));
	if(theta > light.cutOff)
	{
		//ambient  将texture进行赋值
		vec3 ambient = light.ambient * texture(material.diffuse,TexCoords).rgb;
		
		//diffuse   
		vec3 norm = normalize(Normal);
		
		float diff = max(dot(norm,lightDir),0.0f);
		vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoords).rgb;
		
		//specular 
		vec3 viewDir = normalize(viewPos - FragPos);
		//取反射方向
		vec3 reflectDir = reflect(-lightDir,norm);
		float sepc = pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
		vec3 specular = light.specular * sepc * texture(material.specular,TexCoords).rgb;
		//spotlight(soft edges)
		float epsilon = (light.cutOff - light.outerCutOff);
		float intensity = clamp((theta - light.outerCutOff) / epsilon,0.0f,1.0f);
		diffuse *= intensity;
		specular *= intensity;
		//attenuation  衰减
		float distance = length(light.position - FragPos);
		float attenuation = 1.0 / ( light.constant + light.linear * distance + light.quadratic * (distance * distance));
		
		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;
	
		//vec3 result = ambient + diffuse + specular +emission;
		vec3 result = ambient + diffuse + specular ;
		FragColor = vec4(result,1.0f);
	}
	else
	{
		FragColor = vec4((light.ambient) * texture(material.diffuse,TexCoords).rgb,1.0f);
	}
	
}