#pragma once
#include "pch.h"
#include <glm/glm.hpp>
#include "shapes/Shape2d.h"



template <typename T>
struct uniform
{
	std::string name;
	T value;

	uniform(std::string name, T value)
		: name(name), value(value)
	{
	};
	uniform(std::string name)
		: name(name)
	{
		value = default;
	};

	bool operator == (const uniform<T> &other)
	{
		return value == other.value;
	}
};

class UniformController
{
public:
	UniformController();
	~UniformController();

	void add_shape(Shape2d *shape);
	void remove_shape(Shape2d *shape);
	void use();

	void set(const std::string &name, bool value);
	void set(const std::string &name, int value);
	void set(const std::string &name, float value);
	void set(const std::string &name, const glm::vec2 &value);
	void set(const std::string &name, float x, float y);
	void set(const std::string &name, const glm::vec3 &value);
	void set(const std::string &name, float x, float y, float z);
	void set(const std::string &name, const glm::vec4 &value);
	void set(const std::string &name, float x, float y, float z, float w);
	void set(const std::string &name, const glm::mat2 &mat);
	void set(const std::string &name, const glm::mat3 &mat);
	void set(const std::string &name, const glm::mat4 &mat);



	void add(const std::string &name, bool value);
	void add(const std::string &name, int value);
	void add(const std::string &name, float value);
	void add(const std::string &name, const glm::vec2 &value);
	void add(const std::string &name, float x, float y);
	void add(const std::string &name, const glm::vec3 &value);
	void add(const std::string &name, float x, float y, float z);
	void add(const std::string &name, const glm::vec4 &value);
	void add(const std::string &name, float x, float y, float z, float w);
	void add(const std::string &name, const glm::mat2 &mat);
	void add(const std::string &name, const glm::mat3 &mat);
	void add(const std::string &name, const glm::mat4 &mat);

	void imgui_draw();
	void set_from_source(std::string &source);

private:
	std::vector<uniform<bool>> m_boolList;
	std::vector<uniform<int>> m_intList;
	std::vector<uniform<float>> m_floatList;
	std::vector<uniform<glm::vec2>> m_vec2List;
	std::vector<uniform<glm::vec3>> m_vec3List;
	std::vector<uniform<glm::vec4>> m_vec4List;
	std::vector<uniform<glm::mat2>> m_mat2List;
	std::vector<uniform<glm::mat3>> m_mat3List;
	std::vector<uniform<glm::mat4>> m_mat4List;

	std::vector<Shape2d*> m_shapeList;
};

