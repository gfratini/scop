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

VertexBuffer::VertexBuffer(const VertexBuffer &v)
{
	_num = v.len();
	_usage = v._usage;
	_vertices = new float [_num * VERTEX_SIZE];
	for (unsigned int i = 0; i < _num * VERTEX_SIZE; ++i)
		_vertices[i] = v.vertices()[i];
	glGenBuffers(1, &_buffer_id);

	glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
	glBufferData(GL_ARRAY_BUFFER, (VERTEX_SIZE * _num), _vertices, _usage);
}

VertexBuffer::~VertexBuffer() {
	delete[] _vertices;
	glDeleteBuffers(1, &_buffer_id);
}

VertexBuffer::VertexBuffer(const float *vertices, const unsigned int num, GLenum usage) {
	_num = num;
	_usage = usage;
	_vertices = new float[_num * VERTEX_SIZE];
	for (unsigned int i = 0; i < _num * VERTEX_SIZE; ++i)
		_vertices[i] = vertices[i];
	_buffer_id = 0;
	glGenBuffers(1, &_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
	glBufferData(GL_ARRAY_BUFFER, (VERTEX_SIZE * _num), _vertices, usage);
}

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
}

void VertexBuffer::set_vertices(const float *vertices, const unsigned int num, GLenum usage) {
	bind();

	_num = num;
	_usage = usage;
	_vertices = new float[_num * VERTEX_SIZE];
	for (unsigned int i = 0; i < _num * VERTEX_SIZE; ++i)
		_vertices[i] = vertices[i];
	glBufferData(GL_ARRAY_BUFFER, (VERTEX_SIZE * num), _vertices, usage);

}

int VertexBuffer::len() const {
	return (int)_num;
}

unsigned int VertexBuffer::id() const {
	return _buffer_id;
}

const float *VertexBuffer::vertices() const {
	return _vertices;
}
