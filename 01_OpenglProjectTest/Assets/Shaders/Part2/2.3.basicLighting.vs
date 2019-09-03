#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;
out vec3 LightPos;

uniform vec3 lightPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	//将矩阵变换运用到物体生成的位置
	gl_Position = projection * view  * vec4(aPos, 1.0f);
	//得到片段位置
	FragPos = vec3(view * model * vec4(aPos,1.0f));
	//法线矩阵
	Normal = mat3(transpose(inverse(view * model))) * aNormal;
	//光线位置
	LightPos = vec3(view * vec4(lightPos,1.0f));

}