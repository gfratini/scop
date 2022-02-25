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
	for (auto & object : objects) {
		object.rotate({0.0f, 1.0f, 0.0f}, rot);
		object.draw(s);
		if (rot >= 360)
			rot = 0;
	}
	rot += 0.01f;
}

void Scene::rotate(Vec3 plane, float angle) {

}
