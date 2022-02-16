//
// Created by Giulio Fratini on 2/11/22.
//

#ifndef SCOP_CPP_TRANSFORM_HPP
#define SCOP_CPP_TRANSFORM_HPP

#include <memory>
#include <cmath>
#include <iostream>

inline float rad(float deg) { return deg * (float)(3.141592/180.0); }

template <class T>
T	normalize(T vec) {
	T new_vec;
	float len = sqrtf((vec.x() * vec.x()) + (vec.y() * vec.y()) + (vec.z() * vec.z()));
	new_vec.x() = vec.x() / len;
	new_vec.y() = vec.y() / len;
	new_vec.z() = vec.z() / len;
	return new_vec;
}

template <class T>
T	cross(T vec1, T vec2) {
	T new_vec;

	new_vec.x() = vec1.y() * vec2.z() - vec1.z() * vec2.y();
	new_vec.y() = vec1.z() * vec2.x() - vec1.x() * vec2.z();
	new_vec.z() = vec1.x() * vec2.y() - vec1.y() * vec2.x();
	return new_vec;
}

class Vec3 {
	float* vec;
public:
	Vec3(float x, float y, float z) {
		vec = new float[3];
		vec[0] = x;
		vec[1] = y;
		vec[2] = z;
	}
	Vec3() {
		vec = new float[3];
		vec[0] = 0;
		vec[1] = 0;
		vec[2] = 0;
	}

	float x() const {return vec[0]; }
	float y() const {return vec[1]; }
	float z() const {return vec[2]; }

	float& x() {return vec[0]; }
	float& y() {return vec[1]; }
	float& z() {return vec[2]; }

	Vec3(const Vec3& v) : Vec3() { *this = v; }

	Vec3&	operator=(const Vec3& v) {
		if (this != &v)
			memmove(vec, v.vec, 4 * sizeof(float));
		return *this;
	}

	Vec3	operator*(float f) {
		return {x() * f, y() * f, z() * f};
	}

	Vec3	operator+(const Vec3& v) const {
		return {x() + v.x(), y() + v.y(), z() + v.z()};
	}
	Vec3	operator-(const Vec3& v) const {
		return {x() - v.x(), y() - v.y(), z() - v.z()};
	}
	Vec3	operator+=(const Vec3& v) {
		*this = *this + v;
		return *this;
	}
	Vec3	operator-=(const Vec3& v) {
		*this = *this - v;
		return *this;
	}

};

class Mat4 {
private:
	static const unsigned int mat_len = 4;
	float* mat;

public:
	explicit Mat4(float* mat): mat(mat) {}

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
		auto C = new float[mat_len*mat_len];
		int col;
		for (unsigned int k = 0; k < mat_len; k++) {
			col = 0;
			for (unsigned int j = 0; j < mat_len; j++) {
				C[j + (mat_len * k)] = 0;
				for (unsigned int i = 0; i < mat_len; i++) {
					C[j + (mat_len * k)] += (*this)[i + (mat_len * k)] * m[(i * mat_len) + col];
				}
				col++;
			}
		}
		return (Mat4(C));
	}

	Mat4&    operator=(const Mat4& m) {
		if (this != &m)
			memmove(mat, m.mat, 16 * sizeof(float));
		return *this;
	}

	Mat4&    operator=(const float * f) {
		memmove(mat, f, 16 * sizeof(float));
		return *this;
	}

	void	scale(const Vec3 & v) {
		Mat4 m;

		m[0] = v.x();
		m[5] = v.y();
		m[10] = v.z();

		*this = *this * m;
	}

	void	scale(const float * v) {
		Mat4 m;

		m[0] = v[0];
		m[5] = v[1];
		m[10] = v[2];

		*this = *this * m;
	}
	void	translate(const Vec3 & v) {
		Mat4 m;

		m[3] = v.x();
		m[7] = v.y();
		m[11] = v.z();

		*this = *this * m;
	}

	void	translate(const float * v) {
		Mat4 m;

		m[3] = v[0];
		m[7] = v[1];
		m[11] = v[2];
		*this = *this * m;
	}

	void	rotate(const float * v, float angle) {
		float * f = std::allocator<float>().allocate(16);

		float x = v[0];
		float y = v[1];
		float z = v[2];
		float c = cosf(angle);
		float s = sinf(angle);
		const float tmp[] = {
				c + x * x * (1.0f - c), x * y * (1.0f - c) - z * s, x * z * (1.0f - c) + y * s, 0.0f,
				y * x * (1.0f - c) + z * s, c + y * y * (1.0f - c), y * z * (1.0f - c) - x * s, 0.0f,
				z * x * (1.0f - c) - y * s, z * y * (1.0f - c) + x * s, c + z * z * (1.0f - c), 0.0f,
				0.0, 0.0, 0.0, 1.0f
		};
		memmove(f, tmp, 16 * sizeof(float));

		Mat4 m(f);
		*this = *this * m;
	}

	void	rotate(const Vec3 & v, float angle) {
		auto f = new float[16];

		float x = v.x();
		float y = v.y();
		float z = v.z();
		float c = cosf(angle);
		float s = sinf(angle);
		float tmp[] = {
				c + x * x * (1.0f - c), x * y * (1.0f - c) - z * s, x * z * (1.0f - c) + y * s, 0.0f,
				y * x * (1.0f - c) + z * s, c + y * y * (1.0f - c), y * z * (1.0f - c) - x * s, 0.0f,
				z * x * (1.0f - c) - y * s, z * y * (1.0f - c) + x * s, c + z * z * (1.0f - c), 0.0f,
				0.0, 0.0, 0.0, 1.0f
		};
		memmove(f, tmp, 16 * sizeof(float));

		Mat4 m(f);
		*this = *this * m;
	}
	friend std::ostream& operator<<(std::ostream& os, const Mat4& m);
};
inline Mat4 perspective(float w, float h, float z_near, float  z_far, float fov) {
	const float ar = w / h;
	const float z_range = z_near - z_far;
	const float tan_fov = tanf(rad(fov / 2.0f));

	auto f = new float[16];

	float tmp[] = {
			1.0f / (tan_fov * ar), 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f / tan_fov, 0.0f, 0.0f,
			0.0f, 0.0f, (-z_near - z_far) / z_range, 2.0f * z_far * z_near / z_range,
			0.0f, 0.0f, 1.0f, 1.0f
	};
	memmove(f, tmp, 16 * sizeof(float));
	return Mat4(f);
}

inline Mat4 look_at(const Vec3& from, const Vec3& to, const Vec3& up) {
	Vec3	d(normalize(from - to));
	Vec3	r(normalize(cross(up, d)));
	Vec3	u(cross(d, r));
	float f[] = {
		r.x(), r.y(), r.z(), 0.0f,
		u.x(), u.y(), u.z(), 0.0f,
		d.x(), d.y(), d.z(), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	Mat4	m1;
	m1 = f;
	Mat4	m2;
	m2[3] = from.x();
	m2[7] = from.y();
	m2[11] = from.z();
	return m1 * m2;
}

inline std::ostream& operator<<(std::ostream& os, const Mat4& m) {
	for (unsigned int i = 0; i < Mat4::mat_len; ++i) {
		for (unsigned int j = 0; j < Mat4::mat_len; ++j) {
			os << m[(i * Mat4::mat_len) + j] << "(" << (i * Mat4::mat_len) + j << ")" << "  ";
		}
		os << "\n";
	}
	return os;
}



#endif //SCOP_CPP_TRANSFORM_HPP
