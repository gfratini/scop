//
// Created by Giulio Fratini on 23/02/2022.
//

#include "Scene.hpp"

Scene::Scene(const std::string &scene_file) {
	objects = Parser().parse(scene_file);
}

Scene::Scene(const std::string &scene_file, const std::string &def_texture) {
	//objects
}

Scene::~Scene() {

}

void Scene::render(const ShaderProgram& s) {
	unsigned int tmp;
	for (auto it = objects.begin(); it != objects.end(); ++it) {
		s.use(tmp);
		it->draw(s);
	}
}

void Scene::rotate(Vec3 plane, float angle) {

}
