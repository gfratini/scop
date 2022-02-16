//
// Created by Giulio Fratini on 2/16/22.
//

#ifndef SCOP_CPP_CAMERA_HPP
#define SCOP_CPP_CAMERA_HPP

#include "transform.hpp"

class Camera {
private:
	const Vec3	up = {0.0f, 1.0f, 0.0f};
	const float speed = 0.01;
	Vec3		position;
	Vec3		_front;
	Vec3		target;
	float		yaw;
	float		pitch;
	bool		first_input;
	float		last_pos[2];

public:
	Camera(Vec3 position);
	Camera();
	~Camera();

	void	look(double xpos, double ypos);
	void	move(int front, int back, int right, int left);
	Mat4	view() const;
};

#endif //SCOP_CPP_CAMERA_HPP
