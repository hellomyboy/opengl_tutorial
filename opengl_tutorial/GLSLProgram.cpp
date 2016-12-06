#include "GLSLProgram.h"
#include "Error.h"
#include <fstream>


GLSLProgram::GLSLProgram()
{
}

GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	_programID = glCreateProgram();
	if (_programID == 0) {
		fatalError("create program shader error!");
	}

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0) {
		fatalError("create vertex shader error");
	}

	std::string shaderProgram = "";
	std::string line;

	std::ifstream shaderstream(vertexShaderPath);
	if (shaderstream.fail()) {
		fatalError("could not open " + vertexShaderPath);
	}
}

void GLSLProgram::linkShaders()
{

}
