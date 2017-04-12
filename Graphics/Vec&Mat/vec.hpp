#ifndef KMUCS_GRAPHICS_VEC_HPP
#define KMUCS_GRAPHICS_VEC_HPP

#include <iostream>
#include <algorithm>

namespace kmuvcl {
namespace math {

template<unsigned int N, typename T>
class vec {
public:
	vec() {
		set_to_zero();
	}
	// v1
	vec(const T elem) {
		val[0] = elem;
	}
	// v2
	vec(const T s, const T t) :
			vec() {
		val[0] = s;
		val[1] = t;
	}
	// v3
	vec(const T s, const T t, const T u) :
			vec() {
		val[0] = s;
		val[1] = t;
		val[2] = u;
	}
	// v4
	vec(const T s, const T t, const T u, const T v) :
			vec() {
		val[0] = s;
		val[1] = t;
		val[2] = u;
		val[3] = v;
	}
	// Copy Constructor
	vec(const vec<N, T>& other) {

		for (int i = 0; i < N; i++) {
			val[i] = other(i);
		}
	}
	// 대입 연산자
	vec& operator=(const vec<N, T>& other) {
		for (int i = 0; i < N; i++) {
			val[i] = other(i);
		}
		return *this;
	}
	// 호출 연산자
	T& operator()(unsigned int i) {
		return val[i];
	}

	const T& operator()(unsigned int i) const {
		return val[i];
	}

	// type casting operators
	operator const T*() const {
		return val;
	}

	operator T*() {
		return val;
	}

	vec& operator+=(const vec<N, T>& other) {
		for (int i = 0; i < N; i++) {
			val[i] += other(i);
		}
		return *this;
	}

	vec& operator-=(const vec<N, T>& other) {
		for (int i = 0; i < N; i++) {
			val[i] -= other(i);
		}
		return *this;
	}

	void set_to_zero() {
		for (int i = 0; i < N; i++) {
			val[i] = 0;
		}
	}
	T length() {
		T sum = 0;
		for(int i = 0; i < N; i++) {
			sum += val[i] * val[i];
		}
		return sqrt(sum);
	}
	vec& normalize(void) {		
		T len = this->length();
		for(int i = 0; i < N; i++)
			val[i] /= len;
		return *this;
	}

protected:
	T val[N];
};

// typedef
typedef vec<2, float> vec2f;
typedef vec<2, double> vec2d;

typedef vec<3, float> vec3f;
typedef vec<3, double> vec3d;

typedef vec<4, float> vec4f;
typedef vec<4, double> vec4d;

} // namespace math
} // namespace kmuvcl

#include "operator.hpp"

#endif // KMUCS_GRAPHICS_VEC_HPP