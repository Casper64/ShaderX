#pragma once
#include "pch.h"
#include <glm/vec2.hpp>

#include "shaders/Shader.h"

class Shape2d
{
public:
	Shader shader;
	std::vector<glm::vec2> vertices;

	Shape2d() {};
	Shape2d(std::vector<glm::vec2> vertices) : vertices(vertices) {};
	double Area();
	void printVertices();

	virtual void init(GLenum usage) {};
	virtual void draw() {};
	virtual void remove() {};
};

