#pragma once
#include "pch.h"

#include "dependencies/TextEditor.h"
#include <glm/vec2.hpp>

class EditorWindow
{
public:
	EditorWindow();
	~EditorWindow();

	void draw(bool fullscreen);
	void setShaderSource(std::string &source);
	std::string getShaderSource() { return m_editor.GetText(); };
	TextEditor *getEditor() { return &m_editor; };
	
private:
	char m_shaderSource[1024 * 16] = "";
	std::string sourceCode;
	TextEditor m_editor;
};

