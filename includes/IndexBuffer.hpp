//
// Created by Giulio Fratini on 2/11/22.
//

#ifndef SCOP_CPP_INDEXBUFFER_HPP
#define SCOP_CPP_INDEXBUFFER_HPP


#include "GL/glew.h"

class IndexBuffer {
private:
	unsigned int	buffer_id;
	unsigned int*	idx;
	unsigned int	num;

public:
	IndexBuffer();
	~IndexBuffer();
	IndexBuffer(const int * indices, const unsigned int num, GLenum usage);

	void bind() const;
	void set_indices(const int *indices, const unsigned int num, GLenum usage);
};


#endif //SCOP_CPP_INDEXBUFFER_HPP
