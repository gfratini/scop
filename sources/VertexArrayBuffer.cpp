//
// Created by Giulio Fratini on 2/10/22.
//

#include "VertexArrayBuffer.hpp"

VertexArrayBuffer::VertexArrayBuffer()
 : buffer_id(0)
{

	glGenVertexArrays(1, &buffer_id);
	glBindVertexArray(buffer_id);
}

VertexArrayBuffer::~VertexArrayBuffer() {
	glDeleteVertexArrays(1, &buffer_id);
}

void VertexArrayBuffer::bind() const {
	glBindVertexArray(buffer_id);
}