//
// Created by Giulio Fratini on 2/10/22.
//

#include "ShaderProgram.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

ShaderProgram::ShaderProgram(const std::string &vs_file, const std::string &fs_file) {
	unsigned int vertex_shader;
	unsigned int fragment_shader;

	program_id = glCreateProgram();

	vertex_shader = ShaderProgram::create_shader(vs_file, GL_VERTEX_SHADER);
	fragment_shader = ShaderProgram::create_shader(fs_file, GL_FRAGMENT_SHADER);

	glAttachShader(program_id, vertex_shader);
	glAttachShader(program_id, fragment_shader);
	glLinkProgram(program_id);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(program_id);
}

unsigned int ShaderProgram::create_shader(const std::string &file, GLenum type) {
	std::ifstream f(file);
	std::stringstream sstream;
	std::string source;

	if (!f.is_open())
		throw std::runtime_error("Shader file " + file + " not found");

	sstream << f.rdbuf();
	source = sstream.str();
	const char* source_ptr = source.c_str();
	unsigned int shader_id = glCreateShader(type);

	glShaderSource(shader_id, 1, &source_ptr, NULL);
	glCompileShader(shader_id);

	int success;
	char info[512];
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader_id, 512, NULL, info);
		std::cerr << "ERROR "<< file <<" COMPILATION_FAILED\n" << info;
		throw std::runtime_error("Shader Compilation Error");
	}
	return shader_id;
}

void ShaderProgram::use() const {
	glUseProgram(program_id);
}