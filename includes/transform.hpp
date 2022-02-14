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
#include <cmath>
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

		float x() const {return vec[0]; }
		float y() const {return vec[1]; }
		float z() const {return vec[2]; }
		float w() const {return vec[3]; }
    };

	class Mat4 {
	private:
        static const unsigned int mat_len = 4;
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
			memmove(mat, tmp, 16 * sizeof(float));
		}

		~Mat4() {
			delete[] mat;
		}

		float	operator[](unsigned int i) const {
			return mat[i];
		}

		float&	operator[](unsigned int i) {
			return mat[i];
		}

		const float * ptr() {
			return mat;
		}

		Mat4	operator*(const Mat4& m) {
            float* C = new float[mat_len*mat_len];
            int col;
            for (unsigned int k = 0; k < mat_len; k++) {
                col = 0;
                for (unsigned int j = 0; j < mat_len; j++) {
                    C[j + (mat_len * k)] = 0;
                    for (unsigned int i = 0; i < mat_len; i++) {
                        C[j + (mat_len * k)] += (*this)[i + (mat_len * k)] * m[(i * mat_len) + col];
                    };
                    col++;
                }
            }
            return (Mat4(C));
		}

        Mat4&    operator=(const Mat4& m) {
            memmove(mat, m.mat, 16 * sizeof(float));
            return *this;
        }

		void	scale(const Vec4 & v) {
			Mat4 m;

			m[0] = v.x();
			m[5] = v.y();
			m[10] = v.z();
			m[15] = v.w();

			*this = *this * m;
		}

		void	scale(const float * v) {
			Mat4 m;

			m[0] = v[0];
			m[5] = v[1];
			m[10] = v[2];
			m[15] = v[3];

			*this = *this * m;
		}
		void	translate(const Vec4 & v) {
			Mat4 m;

			m[3] = v.x();
			m[7] = v.y();
			m[11] = v.z();
			m[15] = v.w();

			*this = *this * m;
		}

		void	translate(const float * v) {
			Mat4 m;

			m[3] = v[0];
			m[7] = v[1];
			m[11] = v[2];
			m[15] = v[3];
			*this = *this * m;
		}

		void	rotate(const float * v, float angle) {
			float * f = std::allocator<float>().allocate(16);

			float x = v[0];
			float y = v[1];
			float z = v[2];
			float w = v[3];
			float c = cosf(angle);
			float s = sinf(angle);
			float tmp[] = {
					c + x * x * (1.0 - c), x * y * (1.0 - c) - z * s, x * z * (1.0 - c) + y * s, 0.0,
					y * x * (1.0 - c) + z * s, c + y * y * (1.0 - c), y * z * (1.0 - c) - x * s, 0.0,
					z * x * (1.0 - c) - y * s, z * y * (1.0 - c) + x * s, c + z * z * (1.0 - c), 0.0,
					0.0, 0.0, 0.0, w
			};
			memmove(f, tmp, 16 * sizeof(float));

			Mat4 m(f);
			*this = *this * m;
		}

		void	rotate(const Vec4 & v, float angle) {
			float * f = std::allocator<float>().allocate(16);

			float x = v.x();
			float y = v.y();
			float z = v.z();
			float w = v.w();
			float c = cosf(angle);
			float s = sinf(angle);
			float tmp[] = {
					c + x * x * (1.0 - c), x * y * (1.0 - c) - z * s, x * z * (1.0 - c) + y * s, 0.0,
					y * x * (1.0 - c) + z * s, c + y * y * (1.0 - c), y * z * (1.0 - c) - x * s, 0.0,
					z * x * (1.0 - c) - y * s, z * y * (1.0 - c) + x * s, c + z * z * (1.0 - c), 0.0,
					0.0, 0.0, 0.0, w
			};
			memmove(f, tmp, 16 * sizeof(float));

			Mat4 m(f);
			*this = *this * m;
		}
		friend std::ostream& operator<<(std::ostream& os, const Mat4& m);
	};

	std::ostream& operator<<(std::ostream& os, const Mat4& m) {
		for (unsigned int i = 0; i < Mat4::mat_len; ++i) {
			for (unsigned int j = 0; j < Mat4::mat_len; ++j) {
				os << m[(i * Mat4::mat_len) + j] << "(" << (i * Mat4::mat_len) + j << ")" << "  ";
			}
			os << "\n";
		}
		return os;
	}

} //namespace mat


#endif //SCOP_CPP_TRANSFORM_HPP
