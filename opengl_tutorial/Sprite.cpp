#include "Sprite.h"
#include <GL\glew.h>
#include <string>
#include "Vertex.h"
//#include <cstddef>

extern void fatalError(std::string errorString);

Sprite::Sprite()
{
	_vboID = 0;
}

Sprite::~Sprite()
{
	if (_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	//float vertexData1[6 * 2] = {
	//	x, y,
	//	x + width, y + height,
	//	x, y+ height,

	//	x + width, y + height,
	//	x, y,
	//	x + width, y,
	//};

	Vertex vertexData[6];
	//first triangle
	vertexData[0].position.x = x;
	vertexData[0].position.y = y;

	vertexData[1].position.x = x + width;
	vertexData[1].position.y = y + height;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y + height;

	// second triangle
	vertexData[3].position.x = x + width;
	vertexData[3].position.y = y + height;

	vertexData[4].position.x = x;
	vertexData[4].position.y = y;

	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y;

	for (int i = 0; i < 6; i++) {
		vertexData[i].color.r = 255;
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 255;
		vertexData[i].color.a = 255;
	}

	vertexData[2].color.r = 0;
	vertexData[2].color.g = 0;
	vertexData[2].color.b = 255;
	vertexData[2].color.a = 255;

	vertexData[5].color.r = 0;
	vertexData[5].color.g = 255;
	vertexData[5].color.b = 0;
	vertexData[5].color.a = 255;

	if (_vboID == 0)
	{
		glGenBuffers(1, &_vboID);
		if (_vboID == 0) {
			fatalError("could not generate vbo!");
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
