#ifndef KMUVCL_GRAPHICS_OPERATOR_HPP
#define KMUVCL_GRAPHICS_OPERATOR_HPP

#include "vec.hpp"
#include "mat.hpp"
#include <math.h>

namespace kmuvcl {
  namespace math {

    /// y_n = s * x_n
    template <unsigned int N, typename T>
    vec<N, T> operator* (const T s, const vec<N, T>& x)
    {
      	vec<N, T>  y;
      	for(int i = 0; i < N; i++) {
		y(i) = s * x(i);
	}
      	return  y;
    }

    /// s = u_n * v_n (dot product)
    template <unsigned int N, typename T>
    T dot(const vec<N, T>& u, const vec<N, T>& v)
    {
      	T val = 0;
	for (int i = 0; i < N; i++) {
        	val += u(i)*v(i);
     	}
      	return  val;
    }

    /// w_3 = u_3 x v_3 (cross product, only for vec3)
    template <typename T>
    vec<3,T> cross(const vec<3, T>& u, const vec<3, T>& v)
    {
	vec<3, T>  w;
	w(0) = u(1) * v(2) - u(2) * v(1);
	w(1) = u(2) * v(0) - u(0) * v(2);
	w(2) = u(0) * v(1) - u(1) * v(0);
	return  w;
    }

    /// y_m = A_{mxn} * x_n
    template <unsigned int M, unsigned int N, typename T>
    vec<M, T> operator* (const mat<M, N, T>& A, const vec<N, T>& x)
    {
      	vec<M, T>   y;
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < N; j++) {
			y(i) += A(i, j) * x(j);
		}
	}
      	return  y;
    }

    /// y_n = x_m * A_{mxn}
    template <unsigned int M, unsigned int N, typename T>
    vec<N, T> operator* (const vec<M, T>& x, const mat<M, N, T>& A)
    {
      	vec<N, T>   y;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			y(i) += x(j) * A(j, i);
		}
	}
      	return  y;
    }

    /// C_{mxl} = A_{mxn} * B_{nxl}
    template <unsigned int M, unsigned int N, unsigned int L, typename T>
    mat<M, L, T> operator* (const mat<M, N, T>& A, const mat<N, L, T>& B)
    {
      	mat<M, L, T>   C;
      	for(int i = 0; i < M; i++) {
		for(int j = 0; j < L; j++) {
			for(int k = 0; k < N; k++) {
				C(i,j) += A(i, k) * B(k, j);
			}
		}
	}
      	return  C;
    }

    /// ostream for vec class
    template <unsigned int N, typename T>
    std::ostream& operator << (std::ostream& os, const vec<N, T>& v)
    {
	os << "(";
	for(int i = 0; i < N; i++) {
		os << v(i);
		if(i != N-1)
			os << ", ";
	}
	os << ")";
        return  os;
    }

    /// ostream for mat class
    template <unsigned int M, unsigned int N, typename T>
    std::ostream& operator << (std::ostream& os, const mat<M, N, T>& A)
    {
	os << std::endl;
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < N; j++) {
			os << A(i, j) << " ";
		}
		os << std::endl;
	}
	os << std::endl;
      	return  os;
    }

  } // math
} // kmuvcl

#endif // KMUVCL_GRAPHICS_OPERATOR_HPP
