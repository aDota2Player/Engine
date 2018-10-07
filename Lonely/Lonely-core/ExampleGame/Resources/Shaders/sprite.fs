#version 330 core

out vec4 FragColor;

in DATA
{
	vec2 position;
	vec2 texCoord;
	float texID;
	vec4 color;
} fs_in;

uniform sampler2D u_Textures[32];

void main()
{
	 int ID = int(fs_in.texID);
	 FragColor = texture(u_Textures[ID], fs_in.texCoord) * fs_in.color;
	// FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
}