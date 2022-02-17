//
// Created by Giulio Fratini on 2/11/22.
//

#include <memory>
#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer()
 : _buffer_id(0),
   _idx(NULL),
   _num(0) {
	glGenBuffers(1, &_buffer_id);

}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &_buffer_id);
	delete[] _idx;
}

IndexBuffer::IndexBuffer(const unsigned int *indices, const unsigned int num, GLenum usage) {
	_num = num;
	_buffer_id = 0;
	glGenBuffers(1, &_buffer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(float) * _num), indices, usage);

	_idx = std::allocator<unsigned int>().allocate(_num);
	for (unsigned int i = 0; i < num; ++i) {
		_idx[i] = indices[i];
	}
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer_id);
}

void IndexBuffer::set_indices(const int *indices, const unsigned int num, GLenum usage) {
	bind();

	_num = num;
	glGenBuffers(1, &_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * _num), indices, usage);

	_idx = std::allocator<unsigned int>().allocate(_num);
	for (unsigned int i = 0; i < _num; ++i) {
		_idx[i] = indices[i];
	}
}

int IndexBuffer::len() const {
	return (int)_num;
}

void *IndexBuffer::ptr() const {
	return (void*)_idx;
}
