#pragma once

#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>

//Definition of general template class

template <size_t DIM, typename T> struct vec {
	vec() { for (size_t i = DIM; i--; data_[i] = T()); }

	      T& operator[] (const size_t i)       { assert(i < DIM); return data_[i]; }
	const T& operator[] (const size_t i) const { assert(i < DIM); return data_[i]; }

private:
	T data_[DIM];
};

typedef vec<2, float> Vec2f;
typedef vec<3, float> Vec3f;
typedef vec<3, int  > Vec3i;
typedef vec<4, float> Vec4f;

//Definition of specific cases with constructor
template <typename T> struct vec<2, T> {
	vec()           : x(T()), y(T())    {}
	vec(T X, T Y)   : x(X), y(Y)        {}

	      T& operator[] (const size_t i)       { assert(i < 2); return i <= 0 ? x : y; }
	const T& operator[] (const size_t i) const { assert(i < 2); return i <= 0 ? x : y; }

	float norm() { return std::sqrt(x * x + y * y); }
	float squared_distance() { return (x * x + y * y); }
	vec<2, T>& normalize(T l = 1) { *this = (*this) * (l / norm()); return *this; }

	T x, y;
};

template <typename T> struct vec<3, T> {
	vec()               : x(T()), y(T()), z(T())    {}
	vec(T X, T Y, T Z)  : x(X), y(Y), z(Z)          {}
	
	      T& operator[](const size_t i)       { assert(i < 3); return i <= 0 ? x : (1 == i ? y : z); }
	const T& operator[](const size_t i) const { assert(i < 3); return i <= 0 ? x : (1 == i ? y : z); }

	float norm() { return std::sqrt( x * x + y * y + z * z ); }
	float squared_distance() { return (x * x + y * y + z * z);  }
	vec<3, T>& normalize(T l = 1) { *this = (*this) * (l / norm()); return *this; }

	T x, y, z;
};

template <typename T> struct vec<4, T> {
	vec() : x(T()), y(T()), z(T()), w(T()) {}
	vec(T X, T Y, T Z, T W) : x(X), y(Y), z(Z), w(W) {}

	      T& operator[](const size_t i)       { assert(i < 4); return i <= 0 ? x : (1 == i ? y : (2 == i ? z : w)); }
	const T& operator[](const size_t i) const { assert(i < 4); return i <= 0 ? x : (1 == i ? y : (2 == i ? z : w)); }

	float norm() { return std::sqrt(x * x + y * y + z * z + w * w); }
	float squared_distance() { return (x * x + y * y + z * z + w * w); }
	vec<4, T>& normalize(T l = 1) const { *this = (*this) * (l / norm()); return *this; }

	T x, y, z, w;
};

//Basic operations for the template classes (between)

template<size_t DIM, typename T> T operator*(const vec<DIM, T>& lhs, const vec<DIM, T>& rhs) {
	T ret = T();
	for (size_t i = DIM; i--; ret += lhs[i] * rhs[i]);
	return ret;
}

template<size_t DIM, typename T> T operator+(const vec<DIM, T>& lhs, const vec<DIM, T>& rhs) {
    vec<DIM, T> ret;
	for (size_t i = DIM; i--; ret[i]= lhs[i] +rhs[i]);
	return ret;}

template<size_t DIM, typename T> T operator-(vec<DIM, T>& lhs, const vec<DIM, T>& rhs) {
	for (size_t i = DIM; i--; lhs[i] -= rhs[i]);
	return lhs;
}

//Basic operations for the template classes 

template <size_t DIM, typename T, typename U> vec<DIM, T> operator*(const vec<DIM, T>& lhs, const U& rhs) {
	vec<DIM, T> ret;
	for (size_t i = DIM; i--; ret[i] = lhs[i] * rhs);
	return ret;

}

template <size_t DIM, typename T, typename U> vec<DIM, T> operator+(const vec<DIM, T>& lhs, const U& rhs) {
	vec<DIM, T> ret;
	for (size_t i = DIM; i--; ret[i] = lhs[i] + rhs);
	return ret;
}

template <size_t DIM, typename T, typename U> vec<DIM, T> operator-(const vec<DIM, T>& lhs, const U& rhs) {
	vec<DIM, T> ret;
	for (size_t i = DIM; i--; ret[i] = lhs[i] - rhs);
	return ret;
}

//Define the opposite
template<size_t DIM, typename T> vec<DIM, T> operator-(const vec<DIM, T>& lhs) {
	return *lhs * T(-1); 
}

//Cross product for 3D
template <typename T> vec<3, T> cross_product(const vec<3, T>& v1, const vec<3, T> v2) {
	return vec<3, T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

template <size_t DIM, typename T> std::ostream& operator<<(std::ostream& out, const vec<DIM, T>& v) {
	for (size_t i = 0; i < DIM; i++) {
		out << v[i] << " ";
	}
	return out;
}

//Matrix class template definition 

template <size_t DIM_ROW,size_t DIM_COL, typename T> struct matrix{
	matrix() {
		for (int i = 0; i < DIM_ROW; ++i)
		{
			m_data[i]=vec<DIM_COL,T>();
		}
	}

	      vec<DIM_COL,T>& operator[] (const size_t i)       {return m_data[i];}
	const vec<DIM_COL,T>& operator[] (const size_t i) const {return m_data[i];}
	
private:
	vec<DIM_COL,T> m_data[DIM_ROW];

};

typedef matrix<3,3,float> Mat3f;
typedef matrix<4,4,float> Mat4f;

template <typename T> struct matrix<3,3,T>{
	matrix() {for(size_t i=3; i--; m_data[i]=vec<3,T>());}

	      vec<3,T>& operator[] (const size_t i)       {assert(i<3); return i<=0 ? m_data[0] : m_data[i];}
	const vec<3,T>& operator[] (const size_t i) const {assert(i<3); return i<=0 ? m_data[0] : m_data[i];}

private:
	vec<3,T> m_data[3];
};


template <typename T> struct matrix<4,4,T>{
	matrix() {for(size_t i=4; i--; m_data[i]=vec<4,T>());}

	      vec<4,T>& operator[] (const size_t i)       {assert(i<4); return i<=0 ? m_data[0] : m_data[i];}
	const vec<4,T>& operator[] (const size_t i) const {assert(i<4); return i<=0 ? m_data[0] : m_data[i];}		 

private:
	vec<4,T> m_data[4];
};



