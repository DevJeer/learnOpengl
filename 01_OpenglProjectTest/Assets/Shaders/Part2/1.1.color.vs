#version 330 core
layout (location = 0) in vec3 aPos;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
//将矩阵变换运用到物体生成的位置
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}