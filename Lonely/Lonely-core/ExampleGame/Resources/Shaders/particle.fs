#version 330 core

out vec4 FragColor;

in vec2 texCoord;
in vec4 color;

in DATA 
{
	vec2 texCoord;
	vec4 color;
} fs_in;

uniform sampler2D u_Texture;

void main()
{
	FragColor = texture(u_Texture, fs_in.texCoord) * fs_in.color; 
}