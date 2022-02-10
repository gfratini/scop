//
// Created by Giulio Fratini on 2/10/22.
//

#ifndef SCOP_CPP_VERTEXARRAYBUFFER_HPP
#define SCOP_CPP_VERTEXARRAYBUFFER_HPP

#include "GL/glew.h"

class VertexArrayBuffer {
private:
	unsigned int buffer_id;
public:
	VertexArrayBuffer();
	~VertexArrayBuffer();

	void bind() const;
};


#endif //SCOP_CPP_VERTEXARRAYBUFFER_HPP
