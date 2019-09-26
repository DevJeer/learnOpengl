#version 330 core
in vec2 TexCoords;   //vertex的纹理坐标
out vec4 color;         //输出的颜色

uniform sampler2D image;		//采样器
uniform vec3 spriteColor;       //精灵颜色

void main()
{
	color = vec4(spriteColor,1.0f) * texture(image,TexCoords);   //计算最终的颜色
}