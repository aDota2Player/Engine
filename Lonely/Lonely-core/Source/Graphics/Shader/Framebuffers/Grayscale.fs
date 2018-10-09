#version 330 core

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D u_Texture;

void main()
{
	FragColor = texture(u_Texture, texCoord);
	float average  = (FragColor.r + FragColor.g + FragColor.b) / 3.0;
	FragColor = vec4(average , average , average , 1.0);
}
