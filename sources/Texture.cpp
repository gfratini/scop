//
// Created by Giulio Fratini on 2/10/22.
//

#include <iostream>
#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "STB/stb_image.h"
#include "GL/glew.h"

Texture::Texture(const std::string& file, GLenum unit)
	: texture_id(0),
	  _pos(unit),
	  location(0)
{
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char *data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);

	if (!data)
		throw std::runtime_error("Texture " + file + " not found");
	glGenTextures(1, &texture_id);
	glActiveTexture(_pos);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}

Texture::~Texture() {
	glDeleteTextures(1, &texture_id);
}

void	Texture::bind(const ShaderProgram& s) {
	if (location == 0)
		location = glGetUniformLocation(s.id(), TEX_UNIFORM_NAME);
	s.send_texture(location, _pos);
	glActiveTexture(_pos);
	glBindTexture(GL_TEXTURE_2D, texture_id);
}

Texture::Texture() = default;

void Texture::create(const std::string &file, GLenum unit) {
	_pos = unit;
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char *data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);

	if (!data)
		throw std::runtime_error("Texture " + file + " not found");
	glGenTextures(1, &texture_id);
	glActiveTexture(_pos);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}