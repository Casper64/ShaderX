#pragma once
#include "shaders/Shader.h"
#include "shapes/Rectangle.h"
#include <glm/vec2.hpp>


class RenderWindow
{
public:
	RenderWindow();
	~RenderWindow();

	void render(glm::vec2 viewport, float time);
	glm::vec2 draw(uint32_t textureID, bool fullscreen);
	void setFragmentShader(std::string &fragment);
	std::string getFragmentCode() { return m_rectangle.shader.fragmentCode; };
	Rectangle *get_rectangle() { return &m_rectangle; };
public:
	glm::vec2 windowPos = glm::vec2(0, 0);
	glm::vec2 windowSize = glm::vec2(0, 0);


	std::string standardVertex =
		"#version 450\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	std::string standardFragment =
		"#version 450\n"
		"\n"
		"// global uniforms\n"
		"uniform float iTime;\n"
		"uniform vec2 iResolution;\n"
		"uniform vec2 iMouse;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	vec3 col = vec3(0.0);\n"
		"	// uv is from -1.0 to 1.0 with 0.0 being the center\n"
		"	vec2 uv = (gl_FragCoord.xy - 0.5 * iResolution.xy) / iResolution.y;\n"
		"	gl_FragColor = vec4(col, 1.0);\n"
		"}\n";

private:
	Rectangle m_rectangle;

};


