//
// Created by Giulio Fratini on 23/02/2022.
//

#include "Scene.hpp"

Scene::Scene(const std::string &scene_file) {
	objects = Parser().parse(scene_file);
	rot = 0;
}

Scene::Scene(const std::string &scene_file, const std::string &def_texture) {
	//objects
}

Scene::~Scene() {

}

void Scene::render(const ShaderProgram& s) {
	if (objects.size() > 1)
		for (auto & object : objects)
			object.draw(s);
	else if (objects.size() == 1) {
		auto object = objects[0];
		object.rotate({0.0f, 1.0f, 0.0f}, rot);
		object.draw(s);
		rot += 0.2f;
		if (rot >= 360)
			rot = 0;
	} else
		throw std::runtime_error("Error: invalid scene");
}

void Scene::rotate(Vec3 plane, float angle) {

}
