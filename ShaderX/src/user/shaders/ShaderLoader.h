#pragma once
#include "pch.h"

class ShaderLoader
{
public:
public:
	static std::wstring open();
	static void save(std::string &source);
	static void save_as(std::string &source);
	static std::string load(std::string path);
	static std::wstring current_path;

};

