#version 330 core
in vec2 TexCoords;   //vertex����������
out vec4 color;         //�������ɫ

uniform sampler2D image;		//������
uniform vec3 spriteColor;       //������ɫ

void main()
{
	color = vec4(spriteColor,1.0f) * texture(image,TexCoords);   //�������յ���ɫ
}