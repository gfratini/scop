//
// Created by Giulio Fratini on 2/11/22.
//

#include <memory>
#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer()
 : buffer_id(0),
   idx(NULL),
   num(0) {
	glGenBuffers(1, &buffer_id);

}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &buffer_id);
	delete[] idx;
}

IndexBuffer::IndexBuffer(const int *indices, const unsigned int num, GLenum usage) : num(num) {
	buffer_id = 0;
	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(float) * num), indices, usage);

	idx = std::allocator<unsigned int>().allocate(num);
	for (unsigned int i = 0; i < num; ++i) {
		idx[i] = indices[i];
	}
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id)
}

void IndexBuffer::set_indices(const int *indices, const unsigned int num, GLenum usage) {
	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * num), indices, usage);

	idx = std::allocator<unsigned int>().allocate(num);
	for (unsigned int i = 0; i < num; ++i) {
		idx[i] = indices[i];
	}
}