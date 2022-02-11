//
// Created by Giulio Fratini on 2/11/22.
//

#pragma once
#ifndef SCOP_CPP_TRANSFORM_HPP
#define SCOP_CPP_TRANSFORM_HPP

/*
 *	1  2  3     1  2  3     (1*1 + 2*5 + 3*8)  (1*2 + 2*5 + 3*8)  (1*3 + 2*6 + 3*9)
 *	4  5  6  *  4  5  6  =   ...
 *	7  8  9     7  8  9
 *
 * */



/*
    pub fn rotate(a: [f32; 4], angle: f32) -> Mat4 {
		let [x,y,z,w] = a;
		let (sin, cos) = (angle.sin(), angle.cos());
		let data = [
			cos + x * x * (1.0 - cos),		x * y * (1.0 - cos) - z * sin,	x * z * (1.0 - cos) + y * sin,	0.0,
			y * x * (1.0 - cos) + z * sin,	cos + y * y * (1.0 - cos),		y * z * (1.0 - cos) - x * sin,	0.0,
			z * x * (1.0 - cos) - y * sin,	z * y * (1.0 - cos) + x * sin,	cos + z * z * (1.0 - cos),		0.0,
			0.0,							0.0,							0.0,							1.0
		];

        Mat4 {
			data
		}
    }
 * */
#include <memory>
namespace mat {

	class Mat4 {
	private:
		float * mat;
		Mat4	operator*(const Mat4& m) {

		}

	public:

		Mat4() {
			float tmp[] = {
				1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0
			};
			mat = new float[16];
			memmove(mat, tmp, 16);
		}

		~Mat4() {
			delete[] mat;
		}

	};

} //namespace mat

#endif //SCOP_CPP_TRANSFORM_HPP
