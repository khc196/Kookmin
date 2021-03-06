
#include "mat.hpp"
#include "vec.hpp"
#include "operator.hpp"

namespace kmuvcl{
	namespace math{
		// 이동변환
		template<typename T>
		mat<4, 4, T> translate(T dx, T dy, T dz) {
			mat<4, 4, T> tr_mat;

			tr_mat.set_ith_column(0, vec<4, T>(1, 0, 0, 0));
			tr_mat.set_ith_column(1, vec<4, T>(0, 1, 0, 0));
			tr_mat.set_ith_column(2, vec<4, T>(0, 0, 1, 0));
			tr_mat.set_ith_column(3, vec<4, T>(dx, dy, dz, 1));

			return tr_mat;
		}
		// 회전변환
		template<typename T>
		mat<4, 4, T> rotate(T angle, T x, T y, T z) {
			T cos_v;
			T angle_t = angle * M_PI / 180;
			mat<4, 4, T> tr_mat;
			if(angle = 90)
				cos_v = 0;
			else
				cos_v = cos(angle_t);

			vec<3, T> u(x, y, z);
			u.normalize();

			tr_mat.set_ith_column(0,
					vec<4, T>((cos_v + (u(0) * u(0)) * (1 - cos_v)),
							(u(1) * u(0) * (1 - cos_v) + u(2) * sin(angle_t)),
							(u(2) * u(0) * (1 - cos_v) - u(1) * sin(angle_t)), 0));
			tr_mat.set_ith_column(1,
					vec<4, T>((u(0) * u(1) * (1 - cos_v) - u(2) * sin(angle_t)),
							(cos_v + u(1) * u(1) * (1 - cos_v)),
							(u(2) * u(1) * (1 - cos_v) + u(0) * sin(angle_t)), 0));
			tr_mat.set_ith_column(2,
					vec<4, T>((u(0) * u(2) * (1 - cos_v) + u(1) * sin(angle_t)),
							(u(1) * u(2) * (1 - cos_v) + u(0) * sin(angle_t)),
							(cos_v + u(2) * u(2) * (1 - cos_v)), 0));
			tr_mat.set_ith_column(3, vec<4, T>(0, 0, 0, 1));

			return tr_mat;
		}
		// 확대축소
		template<typename T>
		mat<4, 4, T> scale(T sx, T sy, T sz) {
			mat<4, 4, T> tr_mat;

			tr_mat.set_ith_column(0, vec<4, T>(sx, 0, 0, 0));
			tr_mat.set_ith_column(1, vec<4, T>(0, sy, 0, 0));
			tr_mat.set_ith_column(2, vec<4, T>(0, 0, sz, 0));
			tr_mat.set_ith_column(3, vec<4, T>(0, 0, 0, 1));

			return tr_mat;
		}
		// 시점변환
		template<typename T>
		mat<4, 4, T> lookAt(T eyeX, T eyeY, T eyeZ, T centerX, T centerY, T centerZ,
				T upX, T upY, T upZ) {
			mat<4, 4, T> tr_mat;
			mat<4, 4, T> A, B;
			vec<3, T> cam_axis_x, cam_axis_y, cam_axis_z;
			vec<3, T> temp1(centerX, centerY, centerZ);
			vec<3, T> temp2(eyeX, eyeY, eyeZ);
			temp2 -= temp1;
			cam_axis_z = temp2.normalize();
			cam_axis_x = cross(vec<3, T>(upX, upY, upZ), cam_axis_z).normalize();
			cam_axis_y = cross(cam_axis_z, cam_axis_x).normalize();

			A.set_ith_row(0, vec<4, T>(cam_axis_x(0), cam_axis_x(1), cam_axis_x(2), 0));
			A.set_ith_row(1, vec<4, T>(cam_axis_y(0), cam_axis_y(1), cam_axis_y(2), 0));
			A.set_ith_row(2, vec<4, T>(cam_axis_z(0), cam_axis_z(1), cam_axis_z(2), 0));
			A.set_ith_row(3, vec<4, T>(0, 0, 0, 1));

			B.set_ith_column(0, vec<4, T>(1, 0, 0, 0));
			B.set_ith_column(1, vec<4, T>(0, 1, 0, 0));
			B.set_ith_column(2, vec<4, T>(0, 0, 1, 0));
			B.set_ith_column(3, vec<4, T>(-eyeX, -eyeY, -eyeZ, 1));

			tr_mat = A * B;
			return tr_mat;
		}
		// 직교투영
		template<typename T>
		mat<4, 4, T> ortho(T left, T right, T bottom, T top, T nearVal, T farVal) {
			mat<4, 4, T> tr_mat;
			tr_mat.set_ith_column(0, vec<4, T>(2 / (right - left), 0, 0, 0));
			tr_mat.set_ith_column(1, vec<4, T>(0, 2 / (top - bottom), 0, 0));
			tr_mat.set_ith_column(2, vec<4, T>(0, 0, -2 / (farVal - nearVal), 0));
			tr_mat.set_ith_column(3,
					vec<4, T>(-(right + left) / (right - left),
							-(top + bottom) / (top - bottom),
							-(farVal + nearVal) / (farVal - nearVal), 1));
			return tr_mat;
		}
		// 원근투영
		template<typename T>
		mat<4, 4, T> frustum(T left, T right, T bottom, T top, T nearVal, T farVal) {
			mat<4, 4, T> tr_mat;
			tr_mat.set_ith_column(0, vec<4, T>(2 * nearVal / (right - left), 0, 0, 0));
			tr_mat.set_ith_column(1, vec<4, T>(0, 2 * nearVal / (top - bottom), 0, 0));
			tr_mat.set_ith_column(2,
					vec<4, T>((right + left) / (right - left),
							(top + bottom) / (top - bottom),
							-(farVal + nearVal) / (farVal - nearVal), -1));
			tr_mat.set_ith_column(3,
					vec<4, T>(0, 0, -2 * farVal * nearVal / (farVal - nearVal), 0));
			return tr_mat;
		}
		template<typename T>
		mat<4, 4, T> perspective(T fovy, T aspect, T zNear, T zFar) {
			T h, left, right, bottom, top;
			h = 2 * zNear * tanf(fovy / 2 * M_PI / 180);
			top = h / 2;
			bottom = -h / 2;
			left = aspect * bottom;
			right = aspect * top;
			return frustum(left, right, bottom, top, zNear, zFar);
		}

	}
}
