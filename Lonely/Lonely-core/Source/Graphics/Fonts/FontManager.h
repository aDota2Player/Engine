#pragma once

#include "../Shader/Shader.h"
#include "../Texture/Texture.h"
	
#include "../Buffers/VertexArray.h"
#include "../Buffers/VertexBuffer.h"

#include "Maths.h"

#include <map>


namespace lonely { namespace graphics {

	struct Character
	{
		lonely::graphics::Texture* texture;
		lonely::maths::vec2 size;
		lonely::maths::vec2 bearing;
		unsigned int advance;
	};

	class FontManager
	{
	private: 
		static std::map<std::string, std::map<char, Character>> Fonts;
		static Shader* FontShader;
		static VertexArray vertexArray;

	public:
		static void Initialize(Shader* shader, const maths::mat4& projection);

		static void AddFont(std::string name, std::string path, unsigned int height, unsigned int width = 48);

		static void RenderText(const std::string& text, const std::string& font, float x, float y, float scale, bool centered, const maths::vec3& color = maths::vec3(1.0f));

		static inline void SetShader(Shader* shader) { FontShader = shader; }
		
		static void SetProjectionMatrix(const maths::mat4& projection);
		
		static inline Shader* GetShader() { return FontShader; }

	private:
		static std::map<char, Character> LoadFont(std::string path, unsigned int height, unsigned int width = 48);
		FontManager();

	};

} }