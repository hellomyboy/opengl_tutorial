#include "Camera2D.h"
#include <glm\glm.hpp>

#include <iostream>
#include <string>

namespace Engine {

	Camera2D::Camera2D() :	_shouldUpdate(true), 
		_position(0.0f, 0.0f), 
		_scale(1.0f),
		_orthoMatrix(1.0f),
		_cameraMatrix(1.0f),
		_screenWidth(500), 
		_screenHeight(500)
	{
	}


	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int width, int height)
	{
		_screenWidth = width;
		_screenHeight = height;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}

	void Camera2D::setPosition(glm::vec2& position)
	{
		_position = position;
		_shouldUpdate = true;
	}

	void Camera2D::setScale(float scale)
	{
		_scale = scale;
		_shouldUpdate = true;
	}

	void print(std::string key, glm::mat4 m)
	{
		std::cout << key << std::endl;
		for (int i = 0; i < 4; i++)
		{
			std::cout << m[i][0] << "," << m[i][1] << "," << m[i][2] << "," << m[i][3] << std::endl;
		}
		std::cout << std::endl;
	}

	void Camera2D::update()
	{
		if (_shouldUpdate) {
			_shouldUpdate = false;

			glm::vec3 translate(-_position.x, -_position.y, 0.0f);

			//print("ortho matrix", _orthoMatrix);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);
			//print("translate matrix", _cameraMatrix);

			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(_cameraMatrix, scale);
			//print("scale matrix", _cameraMatrix);

			//exit(100);
		}
	}

}
