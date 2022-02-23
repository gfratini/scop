//
// Created by Giulio Fratini on 2/11/22.
//

#include "VertexBuffer.hpp"
#include <cstddef>
#include <iostream>
#include "GL/glew.h"

VertexBuffer::VertexBuffer()
 : _buffer_id(0),
   _num(0) {
	glGenBuffers(1, &_buffer_id);
}

VertexBuffer::~VertexBuffer() {
//	glDeleteBuffers(1, &_buffer_id);
}

VertexBuffer::VertexBuffer(const float *vertices, const unsigned int num, GLenum usage) {
	_num = num;
	_buffer_id = 0;
	glGenBuffers(1, &_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(Vertex) * _num), vertices, usage);

}

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
}

void VertexBuffer::set_vertices(const float *vertices, const unsigned int num, GLenum usage) {
	bind();

	_num = num;
	glBufferData(GL_ARRAY_BUFFER, (sizeof(Vertex) * num), vertices, usage);

}

int VertexBuffer::len() const {
	return (int)_num;
}

unsigned int VertexBuffer::id() const {
	return _buffer_id;
}
