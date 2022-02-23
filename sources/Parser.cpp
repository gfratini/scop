//
// Created by Giulio Fratini on 2/18/22.
//

#include "Parser.hpp"
#include <fstream>
#include <sstream>
#include <cstdio>

Parser::Parser(const ShaderProgram &shader)
		:  shader(shader)
{ }

std::vector<std::string>	split(const std::string& s, char c) {
	std::string tmp(s);
	std::vector<std::string> v;

	while (tmp.find(c) != std::string::npos) {
		unsigned int pos = tmp.find(c);

		if (pos)
			v.push_back(tmp.substr(0, pos));
		tmp = tmp.substr(pos + 1);
	}

	v.push_back(tmp);

	return v;
}

coordinates	parse3f(const std::string& s) {
	coordinates coords;
	int read;
	read = sscanf(s.c_str(), "v %f %f %f", &coords.x, &coords.y, &coords.z);
	if (read != 3)
		throw std::runtime_error("Error: " + s + " Invalid object file");
	return coords;
}

tex_coordinates	parse2f(const std::string& s) {
	tex_coordinates coords;
	int read;
	read = sscanf(s.c_str(), "vt %f %f", &coords.x, &coords.y);
	if (read != 2)
		throw std::runtime_error("Error: " + s + " Invalid object file");
	return coords;
}

void triangulate(std::vector<unsigned int>& vec) {
	std::vector<unsigned int> tmp;

	for (unsigned int len = vec.size(); len >= 3; --len) {
		tmp.push_back(vec[0]);
		tmp.push_back(vec[vec.size() - len + 1]);
		tmp.push_back(vec[vec.size() - len + 2]);
	}
	vec = tmp;
}

std::vector<unsigned int>	parse_face(const std::string& s) {
	unsigned int	vc, tc;
	std::vector<unsigned int> v;
	auto a = split(s, ' ');

	for (auto it = a.begin(); it != a.end(); ++it) {
		auto tmp = split(*it, '/');
		if (tmp[0].length()) {
			vc = atoi(tmp[0].c_str());
			if (vc)
				v.push_back(vc - 1);
		}
	}

	triangulate(v);
	return v;
}

std::vector<coordinates> fix_tex(const std::vector<coordinates>& c, const std::vector<unsigned int> &i) {
	std::vector<coordinates>	vec_c;

	for (auto it = i.begin(); it != i.end(); ++it) {
		vec_c.push_back(c[*it]);
	}
	return vec_c;
}

VertexBuffer parse2(std::ifstream& file, std::vector<coordinates>& c) {
	std::string					line;
	std::vector<unsigned int>	i;
	bool						faces = false;
	std::vector<float>	vertices;

	while (std::getline(file, line)) {
		if (faces && line.find("f ") != 0) break;
		if (line.find("v ") == 0) {
			c.push_back(parse3f(line));
		} else if (line.find("f ") == 0) {
			faces = true;
			auto tmp = parse_face(line.substr(2));
			i.insert(i.end(), tmp.begin(), tmp.end());
		}
	}

	std::cout << i.size() << "  " << c.size() << std::endl;
	auto fixed = fix_tex(c, i);

	for (unsigned int i = 0; i < fixed.size(); ++i) {
		vertices.push_back(fixed[i].x);
		vertices.push_back(fixed[i].y);
		vertices.push_back(fixed[i].z);
		vertices.push_back(0);
		vertices.push_back(0);
	}

	return {vertices.data(), (unsigned int)vertices.size() / 5, GL_STATIC_DRAW};
}


std::vector<Object> Parser::parse(const std::string &file) {
	std::ifstream		f(file);
	std::vector<Object>	vec;

	if (!f.is_open())
		throw std::runtime_error(file + " not found");

	while (!f.eof())
		vec.emplace_back(shader, parse2(f, coords), "assets/textures/wall.jpg", GL_TEXTURE0);

	return vec;
}
