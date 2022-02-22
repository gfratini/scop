//
// Created by Giulio Fratini on 2/18/22.
//

#include "Parser.hpp"
#include <fstream>
#include <sstream>
#include <cstdio>

coordinates	parse3f(const std::string& s) {
	coordinates coords;
	int read;
	read = sscanf(s.c_str(), "v %f %f %f", &coords.x, &coords.y, &coords.z);
	std::cout << coords.x << coords.y << coords.z << std::endl;
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

std::vector<unsigned int>	parse_face(const std::string& s) {
	const char *ptr = s.c_str();
	unsigned int	x, y, z;

	while (sscanf(ptr, "%u/%u/%u", &x, &y, &z)) {

	}
}

Object Parser::parse(const std::string &file) {
	std::ifstream		f(file);
	std::string			line;
	std::vector<coordinates>		c;
	std::vector<tex_coordinates>	t;

	if (!f.is_open())
		throw std::runtime_error(file + " not found");

	while (std::getline(f, line)) {
		if (line.find('#') == 0) {
			std::cout << "Commented Line" << "\t" << line << std::endl;
		} else if (line.find("o ") == 0) {
			std::cout << "Object Name " << "\t" << line << std::endl;
		} else if (line.find("v ") == 0) {
			c.push_back(parse3f(line));
			std::cout << "Vertex Coords" << "\t" << line << std::endl;
		} else if (line.find("vt ") == 0) {
			t.push_back(parse2f(line));
			std::cout << "Texture Coords" << "\t" << line << std::endl;
		} else if (line.find("vn ") == 0) {
			std::cout << "Vertex Normals" << "\t" << line << std::endl;
		} else if (line.find("f ") == 0) {
			std::cout << "Face element" << "\t" << line << std::endl;
		} else {
//			std::cout << "Something Else" << "\t" << line << std::endl;
		}
	}

	return {};
}
