//
// Created by Giulio Fratini on 2/17/22.
//

#ifndef SCOP_CPP_OBJECT_HPP
#define SCOP_CPP_OBJECT_HPP

#include "ShaderProgram.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Texture.hpp"
#include "transform.hpp"
#include "Parser.hpp"

#define TRANSFORM_UNIFORM "transform"

class Object {
private:
	ShaderProgram	_shader;
	VertexBuffer	_vertex_buffer;
	Texture			_texture;
	Mat4			_transform;
	bool			_use_ibo;
public:
	Object();
	Object(const VertexBuffer& obj, const Texture& tex);
	Object(const VertexBuffer& obj, const std::string& t_file, unsigned int pos);
	inline ~Object() = default;

	const ShaderProgram& shader() const;
	ShaderProgram& shader();

	const VertexBuffer& vbo() const;
	VertexBuffer& vbo();

	const Texture& texture() const;
	Texture& texture();

	void	scale(const Vec3& vec);
	void	translate(const Vec3& vec);
	void	rotate(const Vec3& plane, float angle);

	void	draw(const ShaderProgram& s);
};


#endif //SCOP_CPP_OBJECT_HPP
