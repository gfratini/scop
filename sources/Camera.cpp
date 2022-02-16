//
// Created by Giulio Fratini on 2/16/22.
//

#include "Camera.hpp"

Camera::Camera() {
	yaw = -90.0f;
	pitch = 0.0f;
	first_input = true;
	last_pos[0] = 0;
	last_pos[1] = 0;
}

Camera::Camera(Vec3 position) :Camera() {this->position = position; }

Camera::~Camera() = default;

void Camera::look(double xpos, double ypos) {
	if (first_input)
	{
		last_pos[0] = (float)xpos;
		last_pos[1] = (float)ypos;
		first_input = false;
	}

	auto x_offset = (float)(last_pos[0] - xpos);
	auto y_offset = (float)(ypos - last_pos[1]);
	last_pos[0] = xpos;
	last_pos[1] = ypos;

	float sensitivity = 0.1f;
	x_offset *= sensitivity;
	y_offset *= sensitivity;

	yaw   += x_offset;
	pitch += y_offset;

	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;

	Vec3 direction;
	direction.x() = cos(rad(yaw)) * cos(rad(pitch));
	direction.y() = sin(rad(pitch));
	direction.z() = sin(rad(yaw)) * cos(rad(pitch));
	_front = normalize(direction);
}

void Camera::move(int front, int back, int right, int left) {
	if (left && !right) {
		Vec3 v = normalize(cross(up, _front)) * speed;
		position -= v;
	} else if (right && !left) {
		Vec3 v = normalize(cross(up, _front)) * speed;
		position += v;
	}
	if (front && !back) {
		Vec3 v = _front * speed;
		position += v;
	} else if (back && !front) {
		Vec3 v = _front * speed;
		position -= v;
	}
}

Mat4 Camera::view() const {
	return look_at(position, position + _front, up);
}