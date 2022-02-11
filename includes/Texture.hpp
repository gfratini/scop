//
// Created by Giulio Fratini on 2/10/22.
//

#ifndef SCOP_CPP_TEXTURE_HPP
#define SCOP_CPP_TEXTURE_HPP

#include "GL/glew.h"
#include <string>
class Texture {
private:
	unsigned int texture_id;
	GLenum _pos;

public:
	Texture(const std::string& file, GLenum unit);
	~Texture();

	void	bind();
};

#endif //SCOP_CPP_TEXTURE_HPP
