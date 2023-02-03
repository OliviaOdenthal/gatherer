#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <filesystem>
#include <iostream>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "math.hpp"

#define DEF_WINDOW_W 1024
#define DEF_WINDOW_H 1024

#define LOG(X) log_stdout(X);

void log_stdout(std::string const& msg);

namespace std {
	inline std::string to_string(const Vec2i& v) {
		return std::string{"["} + std::to_string(v[0]) + ", " + std::to_string(v[1]) + "]";
	}

	inline std::string to_string(const Vec2f& v) {
		return std::string{"["} + std::to_string(v[0]) + ", " + std::to_string(v[1]) + "]";
	}

	inline std::string to_string(const Vec2h& v) {
		return std::string{"["} + std::to_string(v[0]) + ", " + std::to_string(v[1]) + "]";
	}

	inline std::string to_string(const Vec3i& v) {
		return std::string{"["} + std::to_string(v[0]) + ", " + std::to_string(v[1]) + ", " + std::to_string(v[2]) + "]";
	}

	inline std::string to_string(const Vec3f& v) {
		return std::string{"["} + std::to_string(v[0]) + ", " + std::to_string(v[1]) + ", " + std::to_string(v[2]) + "]";
	}

	inline std::string to_string(const Vec3h& v) {
		return std::string{"["} + std::to_string(v[0]) + ", " + std::to_string(v[1]) + ", " + std::to_string(v[2]) + "]";
	}
}

class AABB {
public:
	AABB();
	AABB(std::vector<Vec3f>& points);
	AABB(Vec3f min, Vec3f max);

	Vec3f minpt, maxpt;

	void addpt(Vec3f pt);
	Vec3f center();
	float maxlength();
};

GLuint disk_load_shader(
	const std::filesystem::path&	path,
	const GLenum 					type
);

GLuint disk_load_shader_program(
	const std::filesystem::path& vtxsha_path,
	const std::filesystem::path& fragsha_path,
	const std::filesystem::path& tessha_path = "",
	const std::filesystem::path& geomsha_path = ""
);

bool glfwCheckErrors();

Vec2f get_cursor_pos(GLFWwindow* window);

// sph[0] = r, sph[1] = yaw, sph[2] = pitch
Vec3f spherical2cartesian(Vec3f sph);
Vec3f cartesian2spherical(Vec3f vec);


#endif