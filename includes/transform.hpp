//
// Created by Giulio Fratini on 2/11/22.
//

#pragma once
#ifndef SCOP_CPP_TRANSFORM_HPP
#define SCOP_CPP_TRANSFORM_HPP

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

    class Vec4{
    private:
        float* vec;
    public:
        Vec4(float x, float y, float z, float w) {
            vec = new float[4];
            vec[0] = x;
            vec[1] = y;
            vec[2] = z;
            vec[3] = w;
        }
    };

	class Mat4 {
	private:
        static unsigned int mat_len = 4;
		float* mat;

        Mat4(float* mat): mat(mat) {}
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

		Mat4	operator*(const Mat4& m) {
            float* C = new float[mat_len*mat_len];
            int col = 0;
            for (int k = 0; k < mat_len; k++) {
                col = 0;
                for (int j = 0; j < mat_len; j++) {
                    C[j + (mat_len * k)] = 0;
                    for (int i = 0; i < mat_len; i++) {
                        C[j + (mat_len * k)] += A[i + (mat_len * k)] * B[(i * mat_len) + col];
                    };
                    col++;
                }
            }
            return (Mat4(C));
		}

        Mat4&    operator=(const Mat4& m) {
            memmove(mat, m.mat, 16);
            return *this;
        }

	};

} //namespace mat

#endif //SCOP_CPP_TRANSFORM_HPP
