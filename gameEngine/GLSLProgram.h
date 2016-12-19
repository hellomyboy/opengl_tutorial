#pragma once

#include <string>
#include <GL\glew.h>

namespace Engine {

	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void compileShader(const std::string& shaderFilePath, const GLuint shaderID);

		void linkShaders();

		void addAttribue(const std::string& attributeName);
		GLint getUniformLocation(const std::string& uniformName);

		void use();
		void unuse();

	private:
		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;

		int _numAttribute;
	};

}

