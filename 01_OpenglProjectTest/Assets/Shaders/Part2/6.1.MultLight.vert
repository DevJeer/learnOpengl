#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

//输出片段位置和法线向量
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	//输出片段位置的计算
	FragPos = vec3(model * vec4(aPos,1.0f));
	//法线矩阵  创建法线向量
	Normal = mat3(transpose(inverse(model))) * aNormal;
	//设置贴图的位置
	TexCoords = aTexCoords;
	gl_Position = projection * view * vec4(FragPos,1.0f);
	
	
}