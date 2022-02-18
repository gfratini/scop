//
// Created by Giulio Fratini on 2/18/22.
//

#include "Parser.hpp"
#include <fstream>
#include <sstream>
#include <cstdio>

void	parse3f(const std::string& s, coordinates& c) {
	int read;
	read = sscanf(s.c_str(), "%f %f %f", &c.x, &c.y, &c.z);
	if (read != 3)
		throw std::runtime_error("Error: " + s + "Invalid object file");
}

void	parse2f(const std::string& s, tex_coordinates& t) {
	int read;
	read = sscanf(s.c_str(), "%f %f", &t.x, &t.y);
	if (read != 2)
		throw std::runtime_error("Error: " + s + "Invalid object file");
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

	coordinates		c;
	tex_coordinates	t;

	if (!f.is_open())
		throw std::runtime_error(file + " not found");

	while (std::getline(f, line)) {
		if (line.find('#') == 0) {
			std::cout << "Commented Line" << "\t" << line << std::endl;
		} else if (line.find("o ") == 0) {
			std::cout << "Object Name " << "\t" << line << std::endl;
		} else if (line.find("v ") == 0) {
			std::cout << "Vertex Coords" << "\t" << line << std::endl;
		} else if (line.find("vt ") == 0) {
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
