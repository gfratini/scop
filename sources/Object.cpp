//
// Created by Giulio Fratini on 2/17/22.
//

#include "Object.hpp"
#include "utils.hpp"
Object::Object() {
	_use_ibo = false;
}

Object::Object(const ShaderProgram &shader, const VertexBuffer &obj, const Texture& tex)
 :  _shader(shader),
 	_vertex_buffer(obj),
	_texture(tex)
{
	_use_ibo = false;
}

Object::Object(const ShaderProgram &shader, const VertexBuffer &obj, const std::string &t_file, unsigned int pos)
:  _shader(shader),
   _vertex_buffer(obj),
   _texture(t_file, pos)
{
	_use_ibo = false;
}

Object::Object(const ShaderProgram &shader, const VertexBuffer &obj, const IndexBuffer &ibo, const Texture &tex)
:  _shader(shader),
   _vertex_buffer(obj),
   _index_buffer(ibo),
   _texture(tex)
{
	_use_ibo = true;
}

Object::Object(const ShaderProgram &shader, const VertexBuffer &obj, const IndexBuffer &ibo, const std::string &t_file,
			   unsigned int pos)
:  _shader(shader),
   _vertex_buffer(obj),
   _index_buffer(ibo),
   _texture(t_file, pos)
{
	_use_ibo = true;
}

Object::Object(const ShaderProgram &shader, const std::string &obj_file, const Texture &tex)
:  _shader(shader),
   _texture(tex)
{
	auto buffers = parse_file(obj_file);

	_vertex_buffer = buffers.first;
	_index_buffer = buffers.second;
	_use_ibo = true;
}

Object::Object(const ShaderProgram &shader, const std::string &obj_file, const std::string &t_file, unsigned int pos)
:  _shader(shader),
   _texture(t_file, pos)
{
	auto buffers = parse_file(obj_file);

	_vertex_buffer = buffers.first;
	_index_buffer = buffers.second;
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

const IndexBuffer &Object::ibo() const {
	return _index_buffer;
}

void Object::ibo(const IndexBuffer& ibo) {
	_index_buffer = ibo;
	_use_ibo = true;
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

void Object::draw() {
	GL_CHECK(_shader.use(););
	GL_CHECK(_vertex_buffer.bind(););
	Vertex::set_attrib_pointer();
	if (_use_ibo)
		_index_buffer.bind();
	GL_CHECK(_texture.bind(_shader););

	int location = glGetUniformLocation(_shader.id(), TRANSFORM_UNIFORM);
	GL_CHECK(glUniformMatrix4fv(location, 1, GL_TRUE, _transform.ptr()););

	if (_use_ibo)
		GL_CHECK(glDrawElements(GL_TRIANGLE_FAN, _index_buffer.len(), GL_UNSIGNED_INT, 0););
	else
		GL_CHECK(glDrawArrays(GL_TRIANGLES, 0, _vertex_buffer.len()););
	_transform = Mat4();
}

std::pair<VertexBuffer, IndexBuffer> Object::parse_file(const std::string &file) {
	return {VertexBuffer(), IndexBuffer()};
}
