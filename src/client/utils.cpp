#include "utils.hpp"

#include <fstream>

void log_stdout(std::string const& msg) {
	std::cout << msg << std::endl;
}

AABB::AABB()
: minpt{ INFINITY,  INFINITY,  INFINITY}, 
  maxpt{-INFINITY, -INFINITY, -INFINITY} {}

AABB::AABB(Vec3f min, Vec3f max)
: minpt{min}, maxpt{max} {}

AABB::AABB(std::vector<Vec3f>& points)
{
	for(Vec3f p : points)
		addpt(p);
}

void AABB::addpt(Vec3f pt)
{
	minpt[0] = min(minpt[0], pt[0]);
	minpt[1] = min(minpt[1], pt[1]);
	minpt[2] = min(minpt[2], pt[2]);
	maxpt[0] = max(maxpt[0], pt[0]);
	maxpt[1] = max(maxpt[1], pt[1]);
	maxpt[2] = max(maxpt[2], pt[2]);
}

Vec3f AABB::center()
{
	return 0.5f * (minpt + maxpt);
}

float AABB::maxlength()
{
	const Vec3f diff = maxpt - minpt;
	return max(max(diff[0], diff[1]), diff[2]);
}

GLuint disk_load_shader(
	const std::filesystem::path&	path,
	const GLenum 					type
)
{
	std::ifstream ifs{path};
	std::string str(
		(std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>())
	);
	ifs.close();
	const char* src = str.c_str();
	GLuint idx = glCreateShader(type);
	glShaderSource(idx, 1, &src, nullptr);
	glCompileShader(idx);

	GLint compile_status;
	glGetShaderiv(idx, GL_COMPILE_STATUS, &compile_status);
	if(compile_status == GL_FALSE)
	{
		LOG(error) << "Shader has errors!";
		char info[512];
		glGetShaderInfoLog(idx, 512, NULL, info);
    	LOG(error) << info;
		return -1;
	}
	LOG(info) << "Compiled shader " << idx;

	return idx;
}

GLuint disk_load_shader_program(
	const std::filesystem::path& vtxsha_path,
	const std::filesystem::path& fragsha_path,
	const std::filesystem::path& tessha_path,
	const std::filesystem::path& geomsha_path
)
{
	bool tessha  = !tessha_path.empty();
	bool geomsha = !geomsha_path.empty();

	GLuint vtxsha_idx  = disk_load_shader(vtxsha_path,  GL_VERTEX_SHADER);
	GLuint fragsha_idx = disk_load_shader(fragsha_path, GL_FRAGMENT_SHADER);
	GLuint tessha_idx = -1;
	if(tessha)
		tessha_idx = disk_load_shader(tessha_path, GL_TESS_EVALUATION_SHADER);
	GLuint geomsha_idx = -1;
	if(geomsha)
		geomsha_idx = disk_load_shader(geomsha_path, GL_GEOMETRY_SHADER);

	GLuint shaprog_idx;
	shaprog_idx = glCreateProgram();
	glAttachShader(shaprog_idx, vtxsha_idx);
	glAttachShader(shaprog_idx, fragsha_idx);
	if(tessha) glAttachShader(shaprog_idx, tessha_idx);
	if(geomsha) glAttachShader(shaprog_idx, geomsha_idx);
	glLinkProgram(shaprog_idx);

	GLint link_status;
	glGetProgramiv(shaprog_idx, GL_LINK_STATUS, &link_status);
	if(link_status == GL_FALSE)
	{
		LOG(error) << "Shader program has errors!";
		char info[512];
		glGetProgramInfoLog(shaprog_idx, 512, NULL, info);
    	LOG(error) << info;
		return -1;
	}
	LOG(info) << "Created shader program " << shaprog_idx;

	glDeleteShader(vtxsha_idx);
	glDeleteShader(fragsha_idx);

	return shaprog_idx;
}

bool glfwCheckErrors()
{
	const char* err_msg;
	int err_code = glfwGetError(&err_msg);
	if(err_code != GLFW_NO_ERROR)
	{
		LOG(error) << "GLFW: " << err_msg;
		return false;
	}
	return true;
}

Vec2f get_cursor_pos(GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	return {(float)x, (float)y};
}

Vec3f spherical2cartesian(Vec3f sph)
{
	float yaw = PI_OVER_180*sph[1];
	float pitch = PI_OVER_180*sph[2];
	float proj = sph[0]*cosf(pitch);
	return {
		proj*cosf(yaw),
		sph[0]*sinf(pitch),
		proj*sinf(yaw)
	};
}

Vec3f cartesian2spherical(Vec3f vec)
{
	float proj = length({vec[0], 0, vec[2]});
	return{
		//r
		length(vec),
		//yaw
		RAD_TO_DEG*atan2f(vec[2], vec[0]),
		//pitch
		RAD_TO_DEG*atan2f(vec[1], proj)
	};
}
