//
// Created by Giulio Fratini on 2/10/22.
//

#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "STB/stb_image.h"

Texture::Texture(const std::string& file, GLenum usage, GLenum format)
	: texture_id(0),
	  usage(usage)
{
	int width, height, nrChannels;
	unsigned char *data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);

	if (!data)
		throw std::runtime_error("Texture " + file + " not found");
	glGenTextures(1, &texture_id);
	glBindTexture(usage, texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() {
	glDeleteTextures(1, &texture_id);
}

void	Texture::bind() {
	glActiveTexture(texture_id);
	glBindTexture(usage, texture_id);
}
