#include "hitbox.h"
#include<iostream>
namespace game {
	Hitbox::Hitbox(std::vector<glm::vec3> p) {
		base_points = p;
		trans = glm::mat4(0.0);
	}

	Hitbox::Hitbox()
	{
		base_points = std::vector<glm::vec3>();
		base_points.push_back(glm::vec3(-1.0, -1.0, -1.0));
		base_points.push_back(glm::vec3(-1.0, -1.0, 1.0));
		base_points.push_back(glm::vec3(-1.0, 1.0, -1.0));
		base_points.push_back(glm::vec3(-1.0, 1.0, 1.0));
		base_points.push_back(glm::vec3(1.0, -1.0, -1.0));
		base_points.push_back(glm::vec3(1.0, -1.0, 1.0));
		base_points.push_back(glm::vec3(1.0, 1.0, -1.0));
		base_points.push_back(glm::vec3(1.0, 1.0, 1.0));
		trans = glm::mat4(0.0);
	}

	Hitbox::~Hitbox() {}

	std::vector<glm::vec3> Hitbox::getPoints() {
		std::vector<glm::vec3> points;
		glm::vec3 trans_point = glm::vec3(0, 0, 0);

		glm::vec4 w_point;
		glm::mat4 local_trans = trans * glm::scale(glm::mat4(1.0), scale);

		for (glm::vec3 p : base_points) {
			w_point = glm::vec4(p.x, p.y, p.z, 1.0);
			w_point = local_trans * w_point;
			trans_point = glm::vec3(w_point.x, w_point.y, w_point.z);

			points.push_back(trans_point);
		}
		return points;
	}

	glm::vec3 Hitbox::getPos() {
		// need to generate position and scale from points

		std::vector<glm::vec3> points = getPoints();
		// right/left = +/- x
		// up/down = +/- y 
		// close/far = +/- z
		float right = NAN, left = NAN, up = NAN, down = NAN, close = NAN, far = NAN;
		for (glm::vec3 point : points)
		{
			//std::cout << "[" << p.x << ", " << p.y << ", " << p.z << "]" << std::endl;
			right = fmax(right, point.x);
			left = fmin(left, point.x);

			up = fmax(up, point.y);
			down = fmin(down, point.y);

			close = fmax(close, point.z);
			far = fmin(far, point.z);
		}

		pos = glm::vec3((right + left) / 2.0, (up + down) / 2.0, (close + far) / 2.0);
		return pos;
	}

	glm::vec3 Hitbox::getScale() {
		return scale;
	}

	glm::mat4 Hitbox::getTrans() {
		return trans;
	}

	void Hitbox::setScale(glm::vec3 s) {
		scale = s;
	}

	void Hitbox::setTransform(glm::mat4 t)
	{
		trans = t;

		
	}
}