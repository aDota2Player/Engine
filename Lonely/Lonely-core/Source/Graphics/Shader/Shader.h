#pragma once

#include <unordered_map>
#include <string>

namespace lonely { namespace maths { struct vec2; struct vec3; struct vec4; struct mat4; } }

namespace lonely { namespace graphics {

	class Shader
	{
	private:
		unsigned int m_ShaderID;
		std::string m_Name;
		std::unordered_map<std::string, int> m_UniformLocationCache;

	public:
		Shader(const std::string& name,
			   const std::string& vertex_shader_path,
               const std::string& fragment_shader_path);

		Shader(const std::string& name,
			   const std::string& vertex_shader_path,
			   const std::string& fragment_shader_path,
			   const std::string& geometry_shader_path);

		~Shader();

		void Bind() const;
		void UnBind() const;

		inline const std::string GetName() const { return m_Name; }

		// Setters (Uniforms)
		// -------------------------------------------------------------------------------
		void SetUniform1f(const std::string& name, float value);
		void SetUniform1i(const std::string& name, int value);

		void SetUniform2f(const std::string& name, float v1, float v2);
		void SetUniform2f(const std::string& name, const maths::vec2& value);
		
		void SetUniform3f(const std::string& name, float v1, float v2, float v3);
		void SetUniform3f(const std::string& name, const maths::vec3& value);

		void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
		void SetUniform4f(const std::string& name, const maths::vec4& value);

		void SetUniformMat4(const std::string& name, const maths::mat4& value);

	private:
		unsigned int CompileShader(unsigned int type, const std::string& source);
		int GetUniformLocation(const std::string& name);
	};

} }