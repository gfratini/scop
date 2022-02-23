//
// Created by Giulio Fratini on 23/02/2022.
//

#include "Scene.hpp"

Scene::Scene(const std::string &scene_file, const ShaderProgram &shader) {
	objects = Parser(shader).parse(scene_file);
}

Scene::Scene(const std::string &scene_file, const ShaderProgram &shader, const std::string &def_texture) {
	//objects
}

Scene::~Scene() {

}

void Scene::render() {
	for (auto it = objects.begin(); it != objects.end(); ++it)
		it->draw();
}

void Scene::rotate(Vec3 plane, float angle) {

}
