//
// Created by Giulio Fratini on 2/10/22.
//

#ifndef SCOP_CPP_TEXTURE_HPP
#define SCOP_CPP_TEXTURE_HPP

#include "GL/glew.h"
#include <string>
#include "ShaderProgram.hpp"

#define TEX_UNIFORM_NAME "tex"

class Texture {
private:
	unsigned int texture_id;
	GLenum _pos;
	unsigned int location;
	std::string	file;

public:
	Texture(const std::string& file, GLenum unit);
	~Texture();
	Texture(const Texture& t);

	void	create(const std::string& file, GLenum unit);
	void	bind(const ShaderProgram& s);
	inline GLenum	pos() { return _pos; }
};

#endif //SCOP_CPP_TEXTURE_HPP
