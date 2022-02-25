//
// Created by Giulio Fratini on 2/10/22.
//

#ifndef SCOP_CPP_SHADERPROGRAM_HPP
#define SCOP_CPP_SHADERPROGRAM_HPP

#include <string>
#include "GL/glew.h"

class ShaderProgram {
private:
	unsigned int program_id;

	static unsigned int create_shader(const std::string& file, GLenum type);
public:
	ShaderProgram();
	ShaderProgram(const std::string& vs_file, const std::string& fs_file);
	~ShaderProgram();
	unsigned int id() const;

	void	create(const std::string& vs_file, const std::string& fs_file);
	void	use(unsigned int& id) const;
	void	send_texture(unsigned int uniform, unsigned int num) const;
};

#endif //SCOP_CPP_SHADERPROGRAM_HPP
