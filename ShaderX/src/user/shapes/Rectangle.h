#pragma once
#include "Shape2d.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <glad/glad.h>

class Rectangle : public Shape2d
{
public:
	glm::vec2 topLeft;
	glm::vec2 topRight;
	glm::vec2 bottomLeft;
	glm::vec2 bottomRight;

	Rectangle() {};
	Rectangle(float x, float y, float width, float height);
	~Rectangle() { remove(); };
	std::vector<glm::vec2> setVertices(float x, float y, float width, float height);

	void init(GLenum usage);
	void draw();
	void remove();
private:
	std::vector<glm::vec3> vertices3d;
	unsigned int VAO, VBO, EBO;
	unsigned int indices[6] = {
		0, 1, 3,
		1, 2, 3 
	};

};

