#include "GLSLProgram.h"
#include "Error.h"
#include <fstream>
#include <iostream>
#include <vector>

namespace Engine {

	GLSLProgram::GLSLProgram() :_programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAttribute(0)
	{
	}

	GLSLProgram::~GLSLProgram()
	{
		if (_programID != 0) {
			glDeleteProgram(_programID);
		}
		if (_vertexShaderID != 0) {
			glDeleteShader(_vertexShaderID);
		}
		if (_fragmentShaderID != 0) {
			glDeleteShader(_fragmentShaderID);
		}
	}

	void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		_programID = glCreateProgram();
		if (_programID == 0) {
			fatalError("create program shader error!");
		}

		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertexShaderID == 0) {
			fatalError("create vertex shader error");
		}

		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentShaderID == 0) {
			fatalError("create fragment shader error");
		}

		compileShader(vertexShaderFilePath, _vertexShaderID);
		compileShader(fragmentShaderFilePath, _fragmentShaderID);
	}

	void GLSLProgram::compileShader(const std::string& shaderFilePath, const GLuint shaderID)
	{
		std::ifstream shaderFile(shaderFilePath);
		if (shaderFile.fail()) {
			perror(shaderFilePath.c_str());
			fatalError("could not open " + shaderFilePath);
		}

		std::string fileContents = "";
		std::string line;
		while (std::getline(shaderFile, line)) {
			fileContents += line + "\n";
		}
		shaderFile.close();
		//std::cout << fileContents << std::endl;


		const GLchar* contentPtr = fileContents.c_str();
		glShaderSource(shaderID, 1, &contentPtr, nullptr);

		glCompileShader(shaderID);

		GLint success = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLint length = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);

			//std::cout << "info log length:" << length << std::endl;

			std::vector<char> errorLog(length + 1);
			glGetShaderInfoLog(shaderID, length, &length, &errorLog[0]);

			std::cout << "compile shader error:" << &(errorLog[0]) << std::endl;
			fatalError("compile shader error! " + shaderFilePath);
			glDeleteShader(shaderID);
		}
	}

	void GLSLProgram::linkShaders()
	{
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);
		glLinkProgram(_programID);

		GLint success = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, &success);
		if (success == GL_FALSE) {
			GLint maxLength;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

			glDeleteProgram(_programID);
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			std::printf("link program error:%s\n", &errorLog[0]);
			fatalError("link program error!");
		}

		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}

	void GLSLProgram::addAttribue(const std::string& attributeName)
	{
		glBindAttribLocation(_programID, _numAttribute++, attributeName.c_str());
	}

	GLint GLSLProgram::getUniformLocation(const std::string& uniformName)
	{
		GLint location = glGetUniformLocation(_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX) {
			fatalError("uniform " + uniformName + " not found in shader!");
		}
		return location;
	}

	void GLSLProgram::use()
	{
		glUseProgram(_programID);
		for (int i = 0; i < _numAttribute; i++) {
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuse()
	{
		glUseProgram(0);
		for (int i = 0; i < _numAttribute; i++) {
			glDisableVertexAttribArray(i);
		}
	}

}
