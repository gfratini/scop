//
// Created by Giulio Fratini on 2/11/22.
//

#include <memory>
#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer()
 : _buffer_id(0),
   _num(0) {
	glGenBuffers(1, &_buffer_id);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &_buffer_id);
}

IndexBuffer::IndexBuffer(const unsigned int *indices, const unsigned int num, GLenum usage) {
	_num = num;
	_buffer_id = 0;
	glGenBuffers(1, &_buffer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(unsigned int) * _num), indices, usage);
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer_id);
}

void IndexBuffer::set_indices(const int *indices, const unsigned int num, GLenum usage) {
	bind();

	_num = num;
	glGenBuffers(1, &_buffer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(unsigned int) * _num), indices, usage);
}

int IndexBuffer::len() const {
	return (int)_num;
}

