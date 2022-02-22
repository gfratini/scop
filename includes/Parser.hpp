//
// Created by Giulio Fratini on 2/18/22.
//

#ifndef SCOP_CPP_PARSER_HPP
#define SCOP_CPP_PARSER_HPP

#include <vector>
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

struct coordinates {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 1.0f;
};

struct tex_coordinates {
	float x = 0.0;
	float y = 0.0;
};

struct vertex {
	float x;
	float y;
	float z;
	float t_x;
	float t_y;
};

class Parser {
private:
	std::vector<coordinates>		coords;
	std::vector<tex_coordinates>	tex_coords;
	std::vector<vertex>				vertices_vec;
	std::vector<unsigned int>		ibo;

public:
	std::pair<VertexBuffer, IndexBuffer>	parse(const std::string& file);

};


#endif //SCOP_CPP_PARSER_HPP
