#include "pch.h"
#include "Rectangle.h"



Rectangle::Rectangle(float x, float y, float width, float height)
{
	vertices = setVertices(x, y, width, height);
}

std::vector<glm::vec2> Rectangle::setVertices(float x, float y, float width, float height)
{
	std::vector<glm::vec2> v;
	topLeft = { x, y };
	topRight = { x + width, y };
	bottomLeft = { x, y - height };
	bottomRight = { x + width, y - height };
	v = { topRight, bottomRight, bottomLeft, topLeft };
	for (int i = 0; i < 4; i++) {
		vertices3d.push_back(glm::vec3(v[i].x, v[i].y, 0.0f));
	}
	return v;
}

void Rectangle::init(GLenum usage)
{
	float verticesRect[] = {
	 1.0f,  1.0f, 0.0f,  // top right
	 1.0f, -1.0f, 0.0f,  // bottom right
	-1.0f, -1.0f, 0.0f,  // bottom left
	-1.0f,  1.0f, 0.0f   // top left 
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesRect), verticesRect, usage);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, usage);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Rectangle::draw()
{
	shader.use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Rectangle::remove()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
