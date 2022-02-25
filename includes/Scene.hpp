//
// Created by Giulio Fratini on 23/02/2022.
//

#ifndef SCOP_CPP_SCENE_HPP
#define SCOP_CPP_SCENE_HPP

#include <vector>
#include "Object.hpp"
class Scene {
private:
	float rot;
	std::vector<Object>	objects;

public:
	Scene(const std::string& scene_file);
	Scene(const std::string& scene_file, const std::string& def_texture);
	~Scene();

	void	render(const ShaderProgram& s);
	void	rotate(Vec3 plane, float angle);
};


#endif //SCOP_CPP_SCENE_HPP
