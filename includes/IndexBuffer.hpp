//
// Created by Giulio Fratini on 2/11/22.
//

#ifndef SCOP_CPP_INDEXBUFFER_HPP
#define SCOP_CPP_INDEXBUFFER_HPP


#include "GL/glew.h"

class IndexBuffer {
private:
	unsigned int	_buffer_id;
	unsigned int*	_idx;
	unsigned int	_num;

public:
	IndexBuffer();
	~IndexBuffer();
	IndexBuffer(const unsigned int * indices, unsigned int num, GLenum usage);

	void bind() const;
	void set_indices(const int *indices, unsigned int num, GLenum usage);
};


#endif //SCOP_CPP_INDEXBUFFER_HPP
