//
// Created by Giulio Fratini on 23/02/2022.
//

#ifndef SCOP_CPP_SCENE_HPP
#define SCOP_CPP_SCENE_HPP

#include <vector>
#include "Object.hpp"
class Scene {
private:
	std::vector<Object>	objects;

public:
	Scene(const std::string& scene_file, const ShaderProgram& shader);
	Scene(const std::string& scene_file, const ShaderProgram& shader, const std::string& def_texture);
	~Scene();

	void	render();
	void	rotate(Vec3 plane, float angle);
};


#endif //SCOP_CPP_SCENE_HPP
