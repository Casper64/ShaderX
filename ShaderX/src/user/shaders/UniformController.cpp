#include "pch.h"
#include "UniformController.h"

#include <imgui.h>

std::vector<bool> test;

UniformController::UniformController()
{
}

UniformController::~UniformController()
{
}

void UniformController::add_shape(Shape2d *shape)
{
	m_shapeList.push_back(shape);
}

void UniformController::remove_shape(Shape2d *shape)
{
	auto item = std::find(m_shapeList.begin(), m_shapeList.end(), shape);
	if (item != m_shapeList.end()) m_shapeList.erase(item);
}

void UniformController::use()
{
	for (Shape2d *shape : m_shapeList) {
		for (uniform<bool> b : m_boolList) shape->shader.setBool(b.name, b.value);
		for (uniform<int> i : m_intList) shape->shader.setInt(i.name, i.value);
		for (uniform<float> f : m_floatList) shape->shader.setFloat(f.name, f.value);
		for (uniform<glm::vec2> vec2 : m_vec2List) shape->shader.setVec2(vec2.name, vec2.value);
		for (uniform<glm::vec3> vec3 : m_vec3List) shape->shader.setVec3(vec3.name, vec3.value);
		for (uniform<glm::vec4> vec4 : m_vec4List) shape->shader.setVec4(vec4.name, vec4.value);
		for (uniform<glm::mat2> mat2 : m_mat2List) shape->shader.setMat2(mat2.name, mat2.value);
		for (uniform<glm::mat3> mat3 : m_mat3List) shape->shader.setMat3(mat3.name, mat3.value);
		for (uniform<glm::mat4> mat4 : m_mat4List) shape->shader.setMat4(mat4.name, mat4.value);
	}
	
}

void UniformController::set(const std::string &name, bool value)
{
	auto item = std::find_if(m_boolList.begin(), m_boolList.begin(), [name](const uniform<bool> obj) { return obj.name.compare(name) == 0; });
	if (item != m_boolList.end()) (*item).value = value;
}

void UniformController::set(const std::string &name, int value)
{
	auto item = std::find_if(m_intList.begin(), m_intList.end(), [name](const uniform<int> obj) { return obj.name.compare(name) == 0; });
	if (item != m_intList.end()) (*item).value = value;
}

void UniformController::set(const std::string &name, float value)
{
	auto item = std::find_if(m_floatList.begin(), m_floatList.end(), [name](const uniform<float> &obj) { return obj.name.compare(name) == 0; });
	if (item != m_floatList.end()) (*item).value = value;
}

void UniformController::set(const std::string &name, const glm::vec2 &value)
{
	auto item = std::find_if(m_vec2List.begin(), m_vec2List.end(), [name](const uniform<glm::vec2> obj) { return obj.name.compare(name) == 0; });
	if (item != m_vec2List.end()) (*item).value = value;
}

void UniformController::set(const std::string &name, float x, float y)
{
	auto item = std::find_if(m_vec2List.begin(), m_vec2List.end(), [name](const uniform<glm::vec2> obj) { return obj.name.compare(name) == 0; });
	if (item != m_vec2List.end()) (*item).value = glm::vec2(x, y);
}

void UniformController::set(const std::string &name, const glm::vec3 &value)
{
	auto item = std::find_if(m_vec3List.begin(), m_vec3List.end(), [name](const uniform<glm::vec3> obj) { return obj.name.compare(name) == 0; });
	if (item != m_vec3List.end()) (*item).value = value;
}

void UniformController::set(const std::string &name, float x, float y, float z)
{
	auto item = std::find_if(m_vec3List.begin(), m_vec3List.end(), [name](const uniform<glm::vec3> obj) { return obj.name.compare(name) == 0; });
	if (item != m_vec3List.end()) (*item).value = glm::vec3(x, y, z);
}

void UniformController::set(const std::string &name, const glm::vec4 &value)
{
	auto item = std::find_if(m_vec4List.begin(), m_vec4List.end(), [name](const uniform<glm::vec4> obj) { return obj.name.compare(name) == 0; });
	if (item != m_vec4List.end()) (*item).value = value;
}

void UniformController::set(const std::string &name, float x, float y, float z, float w)
{
	auto item = std::find_if(m_vec4List.begin(), m_vec4List.end(), [name](const uniform<glm::vec4> obj) { return obj.name.compare(name) == 0; });
	if (item != m_vec4List.end()) (*item).value = glm::vec4(x, y, z, w);
}

void UniformController::set(const std::string &name, const glm::mat2 &mat)
{
	auto item = std::find_if(m_mat2List.begin(), m_mat2List.end(), [name](const uniform<glm::mat2> obj) { return obj.name.compare(name) == 0; });
	if (item != m_mat2List.end()) (*item).value = mat;
}

void UniformController::set(const std::string &name, const glm::mat3 &mat)
{
	auto item = std::find_if(m_mat3List.begin(), m_mat3List.end(), [name](const uniform<glm::mat3> obj) { return obj.name.compare(name) == 0; });
	if (item != m_mat3List.end()) (*item).value = mat;
}

void UniformController::set(const std::string &name, const glm::mat4 &mat)
{
	auto item = std::find_if(m_mat4List.begin(), m_mat4List.end(), [name](const uniform<glm::mat4> obj) { return obj.name.compare(name) == 0; });
	if (item != m_mat4List.end()) (*item).value = mat;
}

void UniformController::add(const std::string &name, bool value)
{
	uniform<bool> uni(name, value);
	m_boolList.push_back(uni);
}

void UniformController::add(const std::string &name, int value)
{
	uniform<int> uni(name, value);
	m_intList.push_back(uni);
}

void UniformController::add(const std::string &name, float value)
{
	uniform<float> uni(name, value);
	m_floatList.push_back(uni);
}

void UniformController::add(const std::string &name, const glm::vec2 &value)
{
	uniform<glm::vec2> uni(name, value);
	m_vec2List.push_back(uni);
}

void UniformController::add(const std::string &name, float x, float y)
{
	uniform<glm::vec2> uni(name, glm::vec2(x, y));
	m_vec2List.push_back(uni);
}

void UniformController::add(const std::string &name, const glm::vec3 &value)
{
	uniform<glm::vec3> uni(name, value);
	m_vec3List.push_back(uni);
}

void UniformController::add(const std::string &name, float x, float y, float z)
{
	uniform<glm::vec3> uni(name, glm::vec3(x, y, z));
	m_vec3List.push_back(uni);
}

void UniformController::add(const std::string &name, const glm::vec4 &value)
{
	uniform<glm::vec4> uni(name, value);
	m_vec4List.push_back(uni);
}

void UniformController::add(const std::string &name, float x, float y, float z, float w)
{
	uniform<glm::vec4> uni(name, glm::vec4(x, y, z, w));
	m_vec4List.push_back(uni);
}

void UniformController::add(const std::string &name, const glm::mat2 &mat)
{
	uniform<glm::mat2> uni(name, mat);
	m_mat2List.push_back(uni);
}

void UniformController::add(const std::string &name, const glm::mat3 &mat)
{
	uniform<glm::mat3> uni(name, mat);
	m_mat3List.push_back(uni);
}

void UniformController::add(const std::string &name, const glm::mat4 &mat)
{
	uniform<glm::mat4> uni(name, mat);
	m_mat4List.push_back(uni);
}

void UniformController::imgui_draw()
{
	static bool test = false;

	for (uniform<bool> &b : m_boolList) {
		ImGui::Checkbox(b.name.c_str(), &b.value);
	}
	for (uniform<int> &i : m_intList) {
		ImGui::InputInt(i.name.c_str(), &i.value);
	}
	for (uniform<float> &f : m_floatList) {
		ImGui::InputFloat(f.name.c_str(), &f.value);
	}
	for (uniform<glm::vec2> &vec2 : m_vec2List) {
		float arr[2] = { vec2.value.x, vec2.value.y };
		if (ImGui::InputFloat2(vec2.name.c_str(), arr)) {
			vec2.value.x = arr[0];
			vec2.value.y = arr[1];
		}
	}
	for (uniform<glm::vec3> &vec3 : m_vec3List) {
		float arr[3] = { vec3.value.x, vec3.value.y, vec3.value.z };
		if (ImGui::ColorEdit3(vec3.name.c_str(), arr)) {
			vec3.value.x = arr[0];
			vec3.value.y = arr[1];
			vec3.value.z = arr[2];
		}
	}
	for (uniform<glm::vec4> &vec4 : m_vec4List) {
		float arr[4] = { vec4.value.x, vec4.value.y, vec4.value.z, vec4.value.w };
		if (ImGui::ColorEdit4(vec4.name.c_str(), arr)) {
			vec4.value.x = arr[0];
			vec4.value.y = arr[1];
			vec4.value.z = arr[2];
			vec4.value.w = arr[3];
		}
	}
	for (uniform<glm::mat2> &mat2 : m_mat2List) {

	}
	for (uniform<glm::mat3> &mat3 : m_mat3List) {

	}
	for (uniform<glm::mat4> &mat4 : m_mat4List) {

	}
}


void findWord(std::string &source, std::string sub, size_t &pos, std::function<void(std::string)> callback)
{
	pos = source.find(sub);
	static char delimiters[] = " \n\t;";
	while (pos != std::string::npos) {
		size_t start = source.find_first_not_of(delimiters, pos + sub.size());
		size_t end = source.find_first_of(delimiters, start);
		std::string word = source.substr(start, (end - start));
		callback(word);
		pos = source.find(sub, pos+word.size());
	}
}

void UniformController::set_from_source(std::string &source)
{
	m_boolList.clear();
	m_floatList.clear();
	m_intList.clear();
	m_vec2List.clear();
	m_vec3List.clear();
	m_vec4List.clear();
	//m_mat2List.clear();
	//m_mat3List.clear();
	//m_mat4List.clear();
	size_t pos;
	findWord(source, "uniform bool", pos, [this](std::string word) {
		add(word, false);
	});
	findWord(source, "uniform int", pos, [this](std::string word) {
		add(word, 0);
	});
	findWord(source, "uniform float", pos, [this](std::string word) {
		add(word, 0.0f);
	});
	findWord(source, "uniform vec2", pos, [this](std::string word) {
		add(word, glm::vec2(0, 0));
	});
	findWord(source, "uniform vec3", pos, [this](std::string word) {
		add(word, glm::vec3(0, 0, 0));
	});
	findWord(source, "uniform vec4", pos, [this](std::string word) {
		add(word, glm::vec4(0, 0, 0, 0));
	});
	// TODO: implement matrices defaul constructors
}
