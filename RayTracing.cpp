#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "geometry.h"
#include "matrix.h"


struct Sphere {
	Vec3f center_position;
	float radius;

	Sphere(Vec3f& center,float radius_sphere): center_position(center),radius(radius_sphere){}

	//Check if there is an intersection with the sphere
	/*
	bool intersect_ray(const Vec3f& origin_ray, const Vec3f& direction_ray, float& t0) const {
		Vec3f distance_center_origin = center_position - origin_ray;
		float distance_ray = origin_ray * direction_ray;
		float d2 = distance_center_origin * distance_center_origin - distance_ray * distance_ray;
		if (d2 > radius* radius) { return false; }

	}
	*/
};

void render() {
	//Define the dimension of the frame
	const int width = 1920, height = 1080;
	//Create One dimensional vector (it s a matrix)-> Frame and fill it with a (R,G,B) vector
	std::vector<Vec3f> framebuffer(width * height);

	for (size_t j = 0; j < height; j++) {
		for (size_t i = 0; i < width; i++) {
			framebuffer[i + j * width] = Vec3f(j / float(height), i / float(width), 0);
		}
	}

	std::ofstream file; // save the framebuffer to file
	file.open("./out.ppm", std::ofstream::out | std::ofstream::binary); //open the file in the directory as out .ppm...we open the file in binary to avoid problems (on linux is not necessary)
	file << "P6\n" << width << " " << height << "\n255\n"; //we use a ppm P6
	for (size_t i = 0; i < height * width; ++i) {
		for (size_t j = 0; j < 3; j++) {
			file << (unsigned char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j]))); //The color value is in the framebuffer, 255 is the lightning
		}
	}
	file.close();
}

int main() {
	Mat3f l;
	std::cout<<l[1];
	return 0;
}

