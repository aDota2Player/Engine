#version 330 core

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D u_Texture;

void main()
{
	FragColor = vec4(vec3(1.0 - texture(u_Texture, texCoord)), 1.0);
}
