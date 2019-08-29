#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
//将矩阵变换运用到物体生成的位置
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	//TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	TexCoord = vec2(1 - aTexCoord.x,aTexCoord.y);
}