//
// Created by Giulio Fratini on 2/10/22.
//

#ifndef SCOP_CPP_BUFFER_HPP
#define SCOP_CPP_BUFFER_HPP

#include "GL/glew.h"

template<class T>
class Buffer {
protected:
	unsigned int buffer_id;
	T data;
	GLenum type;
	GLenum usage;

public:
	IBuffer(T data, GLenum type, GLenum usage)
		: data(data), type(type), usage(usage)
	{
	}
	~IBuffer();

	void bind();
};

#endif //SCOP_CPP_BUFFER_HPP
