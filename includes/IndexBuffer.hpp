//
// Created by Giulio Fratini on 2/11/22.
//

#ifndef SCOP_CPP_INDEXBUFFER_HPP
#define SCOP_CPP_INDEXBUFFER_HPP


#include "GL/glew.h"
#include <iostream>
#include "VertexBuffer.hpp"
class IndexBuffer {
private:
	unsigned int	_buffer_id;
	unsigned int	_num;

public:
	IndexBuffer();
	~IndexBuffer();
	IndexBuffer(const unsigned int * indices, unsigned int num, GLenum usage);

	void	bind() const;
	void	set_indices(const int *indices, unsigned int num, GLenum usage);
	int		len() const;
	inline void info() {
		std::cout << "id: " << _buffer_id << "  len: " << _num << std::endl;
	}
};


#endif //SCOP_CPP_INDEXBUFFER_HPP
