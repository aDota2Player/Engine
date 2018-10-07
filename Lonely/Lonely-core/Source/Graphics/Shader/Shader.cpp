#include "Shader.h"

#include "FileReader.h"

#include <GL/glew.h>

namespace lonely { namespace graphics {

	Shader::Shader(const std::string& name,
				   const std::string& vertexPath,
				   const std::string& fragmentPath)
		: m_ShaderID(0), m_Name(name)
	{
		std::string vertexSource =   FileToString(vertexPath);
		std::string fragmentSource = FileToString(fragmentPath);
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSource);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
	
		m_ShaderID = glCreateProgram();
		
		glAttachShader(m_ShaderID, vs);
		glAttachShader(m_ShaderID, fs);
		glLinkProgram(m_ShaderID);
		
#ifdef _DEBUG

		int result;
		glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetProgramiv(m_ShaderID, GL_INFO_LOG_LENGTH, &length);
			char* messege = (char*)alloca(sizeof(char) * length);
			glGetProgramInfoLog(m_ShaderID, length, &length, messege);

			std::cout << "[ PROGRAM ERROR ]: " << messege << std::endl;
		}

#endif

		glValidateProgram(m_ShaderID);
	}

	Shader::Shader(const std::string& name,
				   const std::string& vertexPath, 
		           const std::string& fragmentPath,
		           const std::string& geometryPath)
		: m_ShaderID(0), m_Name(name)
	{
		std::string vertexSource =   FileToString(vertexPath);
		std::string fragmentSource = FileToString(fragmentPath);	
		std::string geometrySource = FileToString(geometryPath);

		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSource);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
		unsigned int gs = CompileShader(GL_GEOMETRY_SHADER, geometrySource);

		m_ShaderID = glCreateProgram();

		glAttachShader(m_ShaderID, vs);
		glAttachShader(m_ShaderID, fs);
		glAttachShader(m_ShaderID, gs);
		glLinkProgram(m_ShaderID);

#ifdef _DEBUG

		int result;
		glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetProgramiv(m_ShaderID, GL_INFO_LOG_LENGTH, &length);
			char* messege = (char*)alloca(sizeof(char) * length);
			glGetProgramInfoLog(m_ShaderID, length, &length, messege);

			std::cout << "[ PROGRAM ERROR ]: " << messege << std::endl;
		}

#endif

		glValidateProgram(m_ShaderID);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderID);
	}

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source) // private
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
	
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

#ifdef _DEBUG

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* messege = (char*)alloca(sizeof(char) * length);
			glGetShaderInfoLog(id, length, &length, messege);

			std::cout << "[ SHADER ERROR ]: " << messege << std::endl;
			return 0;
		}

#endif

		return id;
	}
	
	void Shader::Bind() const
	{
		glUseProgram(m_ShaderID);
	}

	void Shader::UnBind() const
	{
		glUseProgram(0);
	}

	void Shader::SetUniform1i(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1f(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniform2f(const std::string& name, float v1, float v2)
	{
		glUniform2f(GetUniformLocation(name), v1, v2);
	}

	void Shader::SetUniform2f(const std::string& name, const maths::vec2& value)
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void Shader::SetUniform3f(const std::string& name, float v1, float v2, float v3)
	{
		glUniform3f(GetUniformLocation(name), v1, v2, v3);
	}

	void Shader::SetUniform3f(const std::string& name, const maths::vec3& value)
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void Shader::SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
	{
		glUniform4f(GetUniformLocation(name), v1, v2, v3, v4);
	}

	void Shader::SetUniform4f(const std::string& name, const maths::vec4& value)
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void Shader::SetUniformMat4(const std::string& name, const maths::mat4 & value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_TRUE, value.elements);
	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		int location = glGetUniformLocation(m_ShaderID, name.c_str());

		if (location == -1)
			std::cout << "[ WARNING ]: Failed to get location of uniform: " << name << std::endl;

		m_UniformLocationCache[name] = location;
		return location;
	}

} }