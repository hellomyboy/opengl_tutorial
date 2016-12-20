#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace Engine {

	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int width, int height);

		void update();

		void setPosition(glm::vec2& position);
		void setScale(float scale);

		glm::vec2 getPosition() { return _position; }
		glm::mat3 getCameraMatrix() { return _cameraMatrix; }
		float getScale() { return _scale; }

	private:
		int _screenWidth, _screenHeight;
		bool _shouldUpdate;
		glm::vec2 _position;
		float _scale;

		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
	};

}

