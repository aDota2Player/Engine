#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in float  aTextureID;
layout(location = 3) in vec4 aColor;

out DATA
{
	vec2 position;
	vec2 texCoord;
	float  texID;
	vec4 color;
} vs_out;

uniform mat4 u_ProjectionMatrix = mat4(1.0f);
uniform mat4 u_ViewMatrix = mat4(1.0f);

void main()
{
	gl_Position = u_ProjectionMatrix * u_ViewMatrix * vec4(aPos, 0.0f, 1.0f);

	vs_out.position = aPos;
	vs_out.texCoord = aTexCoord;
	vs_out.texID    = aTextureID;
	vs_out.color    = aColor;
}