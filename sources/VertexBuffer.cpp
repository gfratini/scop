//
// Created by Giulio Fratini on 2/11/22.
//

#include "VertexBuffer.hpp"
#include <cstddef>
#include <iostream>
#include "GL/glew.h"

VertexBuffer::VertexBuffer()
 :  buffer_id(0),
 	v(NULL),
 	num(0) {
	glGenBuffers(1, &buffer_id);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &buffer_id);
	delete[] v;
}

VertexBuffer::VertexBuffer(const float *vertices, const unsigned int num, GLenum usage) : num(num) {
	buffer_id = 0;
	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(Vertex) * num), vertices, usage);

	v = std::allocator<Vertex>().allocate(num);
	for (unsigned int i = 0; i < num * (sizeof(Vertex) / sizeof(float)); ++i) {
		((float *)v)[i] = vertices[i];
	}
}

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
}

void VertexBuffer::set_vertices(const float *vertices, const unsigned int num, GLenum usage) {
	bind();

	glBufferData(GL_ARRAY_BUFFER, (sizeof(Vertex) * num), vertices, usage);

	v = std::allocator<Vertex>().allocate(num);
	for (unsigned int i = 0; i < num * (sizeof(Vertex) / sizeof(float)); ++i) {
		((float *)v)[i] = vertices[i];
	}
}