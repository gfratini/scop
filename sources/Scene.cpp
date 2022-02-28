//
// Created by Giulio Fratini on 23/02/2022.
//

#include "Scene.hpp"

Scene::Scene(const std::string &scene_file, std::string tex) {
	if (tex.empty()) tex = "assets/textures/wall.jpg";
	Texture t(tex, GL_TEXTURE0);
	objects = Parser().parse(scene_file, t);
	rot = 0;
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
