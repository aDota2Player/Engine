#include "Debugger.h"




namespace lonely { namespace debug {

	void GLClearLog()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	std::string GetErrorName(GLenum error)
	{
		switch (error)
		{
		case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
		case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
		case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
		case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
		case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
		case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
		case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
		case GL_CONTEXT_LOST: return "GL_CONTEXT_LOST";
		case GL_TABLE_TOO_LARGE: return "GL_TABLE_TOO_LARGE";
		default: return "unknown";
		}
	}

	bool GLLogCall(int line, const char* file, const char* function)
	{
		if (GLenum error = glGetError())
		{
			std::cout 
				<< "[ OpenGL ERROR ]: file: "	<< file 
				<< " | line: "					<< line 
				<< " | error: "					<< GetErrorName(error) 
				<< " | function: "				<< function  
				<< std::endl;
			return false;
		}
		return true;
	}

} }



