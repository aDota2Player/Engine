#include <ft2build.h>
#include <freetype/freetype.h>

#include <GL/glew.h>

#include "Graphics/Fonts/FontManager.h"

namespace lonely { namespace graphics {

	std::map<std::string, std::map<char, Character>> FontManager::Fonts;

	Shader*       FontManager::FontShader;
	VertexArray  FontManager::vertexArray;

	void FontManager::Initialize(Shader* shader, const maths::mat4& projection)
	{	
		FontShader = shader;
		FontShader->Bind();
		FontShader->SetUniformMat4("u_ProjectionMatrix", projection);

		VertexBuffer vertexBuffer;
		vertexBuffer.Compile(NULL, 6 * 4 * sizeof(float), GL_DYNAMIC_DRAW);

		vertexArray.Push<float>(2, GL_FLOAT, GL_FALSE);
		vertexArray.Push<float>(2, GL_FLOAT, GL_FALSE);
		vertexArray.Compile(vertexBuffer);
	}

	void FontManager::AddFont(std::string name, std::string path, unsigned int height, unsigned int width)
	{
		Fonts[name] = LoadFont(path, height, width);
	}

	void FontManager::RenderText(const std::string& text, const std::string& font, float x, float y, float scale, bool centered, const maths::vec3& color)
	{
		std::string::const_iterator c;
		float width = 0.0f;

		FontShader->Bind();
		vertexArray.BindArray();
		FontShader->SetUniform3f("u_TextColor", color);

		if (centered)
		{
			for (c = text.begin(); c != text.end(); c++)
			{
				Character ch = Fonts[font][*c];
				width += (ch.advance >> 6) * scale;
			}
			width /= 2.0f;
		}
		
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = Fonts[font][*c];

			float xpos = x + ch.bearing.x * scale;
			float ypos = y - (ch.size.y - ch.bearing.y) * scale;


			float w = ch.size.x * scale;
			float h = ch.size.y * scale;

			float vertices[]{
				xpos - width,     ypos - h,   0.0, 0.0,
				xpos - width,     ypos,       0.0, 1.0,
				xpos - width + w, ypos,       1.0, 1.0,

				xpos - width,     ypos - h,   0.0, 0.0,
				xpos - width + w, ypos,       1.0, 1.0,
				xpos - width + w, ypos - h,   1.0, 0.0
			};

			ch.texture->Bind();

			vertexArray.BindBuffer();
			vertexArray.BufferSubData(vertices, sizeof(vertices));
			vertexArray.UnBindBuffer();

			glDrawArrays(GL_TRIANGLES, 0, 6);

			x += (ch.advance >> 6) * scale;
		}
		vertexArray.UnBindArray();
		glBindTexture(GL_TEXTURE_2D, 0);
		FontShader->UnBind();
	}

	std::map<char, Character> FontManager::LoadFont(std::string path, unsigned int height, unsigned int width) // private
	{
		FT_Library freeType;
		FT_Face face;
		std::map<char, Character> Characters;

		if (FT_Init_FreeType(&freeType) || FT_New_Face(freeType, path.c_str(), 0, &face))
		{
			std::cout << "[ ERROR ]: Failed to load font in path: " << path << std::endl;
			return std::map<char, Character>();
		}
		
		FT_Set_Pixel_Sizes(face, width, height);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for (unsigned char c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				continue;

			Character character = {
				new lonely::graphics::Texture(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer),
				lonely::maths::vec2((float)face->glyph->bitmap.width,(float)face->glyph->bitmap.rows),
				lonely::maths::vec2((float)face->glyph->bitmap_left, (float)face->glyph->bitmap_top),
				face->glyph->advance.x
			};

			Characters.insert(std::pair<char, Character>(c, character));
		}

		FT_Done_Face(face);
		FT_Done_FreeType(freeType);
		return Characters;
	}

	void FontManager::SetProjectionMatrix(const maths::mat4& projection)
	{
		FontShader->Bind();
		FontShader->SetUniformMat4("u_ProjectionMatrix", projection);
		FontShader->UnBind();
	}

} }
