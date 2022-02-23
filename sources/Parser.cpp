//
// Created by Giulio Fratini on 2/18/22.
//

#include "Parser.hpp"
#include <fstream>
#include <sstream>
#include <cstdio>

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
	const char *ptr = s.c_str();
	unsigned int	vc, tc;
	std::vector<unsigned int> v;
	auto a = split(s, ' ');

	for (auto it = a.begin(); it != a.end(); ++it) {
		auto tmp = split(*it, '/');
		vc = atoi(tmp[0].c_str()) - 1;
		v.push_back(vc);
	}

	triangulate(v);
	return v;
}

void fix_tex(std::vector<coordinates>& c, std::vector<tex_coordinates> &t, const std::vector<unsigned int> &i) {
	std::vector<tex_coordinates> vec_t;
	std::vector<coordinates>	vec_c;

	for (auto it = i.begin(); it != i.end(); ++it) {
		vec_c.push_back(c[*it]);
	}
	c = vec_c;
}


std::pair<VertexBuffer, IndexBuffer> Parser::parse(const std::string &file) {
	std::ifstream		f(file);
	std::string			line;
	std::vector<coordinates>		c;
	std::vector<tex_coordinates>	t;
	std::vector<unsigned int> i;

	std::vector<float>	vertices;

	if (!f.is_open())
		throw std::runtime_error(file + " not found");

	while (std::getline(f, line)) {
		if (line.find('#') == 0) {
//			std::cout << "Commented Line" << "\t" << line << std::endl;
		} else if (line.find("o ") == 0) {
//			std::cout << "Object Name " << "\t" << line << std::endl;
		} else if (line.find("v ") == 0) {
			c.push_back(parse3f(line));
//			std::cout << "Vertex Coords" << "\t" << line << std::endl;
		} else if (line.find("vt ") == 0) {
			t.push_back(parse2f(line));
//			std::cout << "Texture Coords" << "\t" << line << std::endl;
		} else if (line.find("vn ") == 0) {
//			std::cout << "Vertex Normals" << "\t" << line << std::endl;
		} else if (line.find("f ") == 0) {
			auto tmp = parse_face(line.substr(2));
			i.insert(i.end(), tmp.begin(), tmp.end());
//			std::cout << "Face element" << "\t" << line << std::endl;
		} else {
//			std::cout << "Something Else" << "\t" << line << std::endl;
		}
	}

	fix_tex(c, t, i);

	for (unsigned int i = 0; i < c.size(); ++i) {
		vertices.push_back(c[i].x);
		vertices.push_back(c[i].y);
		vertices.push_back(c[i].z);
		vertices.push_back(0);
		vertices.push_back(0);
	}

	std::cout << vertices.size();

	return {VertexBuffer(vertices.data(), vertices.size() / 5, GL_STATIC_DRAW), IndexBuffer()};
}
