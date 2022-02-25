//
// Created by Giulio Fratini on 2/17/22.
//

#include "Object.hpp"
#include "utils.hpp"
Object::Object() {
	_use_ibo = false;
}

Object::Object(const VertexBuffer &obj, const Texture& tex)
 :  _vertex_buffer(obj),
	_texture(tex)
{
	_use_ibo = false;
}

Object::Object(const VertexBuffer &obj, const std::string &t_file, unsigned int pos)
:  _vertex_buffer(obj),
   _texture(t_file, pos)
{
	_use_ibo = false;
}

const ShaderProgram &Object::shader() const {
	return _shader;
}

ShaderProgram &Object::shader() {
	return _shader;
}

const VertexBuffer &Object::vbo() const {
	return _vertex_buffer;
}

VertexBuffer &Object::vbo() {
	return _vertex_buffer;
}


const Texture &Object::texture() const {
	return _texture;
}

Texture &Object::texture() {
	return _texture;
}

void Object::scale(const Vec3 &vec) {
	_transform.scale(vec);
}

void Object::translate(const Vec3 &vec) {
	_transform.translate(vec);
}

void Object::rotate(const Vec3 &plane, float angle) {
	_transform.rotate(plane, rad(angle));
}

void Object::draw(const ShaderProgram& s) {
	GL_CHECK(_vertex_buffer.bind(););
	Vertex::set_attrib_pointer();
	GL_CHECK(_texture.bind(s););

	int location = glGetUniformLocation(s.id(), TRANSFORM_UNIFORM);
	GL_CHECK(glUniformMatrix4fv(location, 1, GL_TRUE, _transform.ptr()););

	GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, _vertex_buffer.len()););
	_transform = Mat4();
}
