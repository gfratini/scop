//
// Created by Giulio Fratini on 2/11/22.
//

#ifndef SCOP_CPP_VERTEXBUFFER_HPP
#define SCOP_CPP_VERTEXBUFFER_HPP

#include "GL/glew.h"

struct Vertex {

	float position[3];
	float color[3];
	float tex_coords[2];

//	static unsigned int index;
//	static void set_attrib_pointer() {
//		// position
//		glVertexAttribPointer(index++, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
//		// color
//		glVertexAttribPointer(index++, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
//		// tex_coord
//		glVertexAttribPointer(index++, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
//	}

};


class VertexBuffer {
private:
	unsigned int	_buffer_id;
	Vertex*			_v;
	unsigned int 	_num;
public:
	VertexBuffer();
	~VertexBuffer();
	VertexBuffer(const float * vertices, unsigned int num, GLenum usage);

	void	bind() const;
	void	set_vertices(const float *vertices, unsigned int num, GLenum usage);
};


#endif //SCOP_CPP_VERTEXBUFFER_HPP
