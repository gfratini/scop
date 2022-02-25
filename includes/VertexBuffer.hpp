//
// Created by Giulio Fratini on 2/11/22.
//

#ifndef SCOP_CPP_VERTEXBUFFER_HPP
#define SCOP_CPP_VERTEXBUFFER_HPP

#include "GL/glew.h"

struct Vertex {

	float position[3];
	float tex_coords[2];

	static void set_attrib_pointer() {
		//position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
		glEnableVertexAttribArray(0);
		// tex_coord
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
		glEnableVertexAttribArray(1);
	}

};


class VertexBuffer {
private:
	static const unsigned int VERTEX_SIZE = 5;
	unsigned int	_buffer_id;
	unsigned int 	_num;
	float*			_vertices;
	GLenum			_usage;
public:
	VertexBuffer();
	VertexBuffer(const VertexBuffer& v);
	~VertexBuffer();
	VertexBuffer(const float * vertices, unsigned int num, GLenum usage);

	void	bind() const;
	void	set_vertices(const float *vertices, unsigned int num, GLenum usage);
	int		len() const;
	unsigned int	id() const;
	const float *	vertices() const;
};


#endif //SCOP_CPP_VERTEXBUFFER_HPP
