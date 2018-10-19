#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec4 aColor;

out DATA 
{
	vec2 texCoord;
	vec4 color;
} vs_out;


uniform mat4 u_ProjectionMatrix;

void main()
{
	gl_Position = u_ProjectionMatrix * vec4(aPos, 0.0f, 1.0f);
	vs_out.texCoord = aTexCoord;
	vs_out.color = aColor;
}