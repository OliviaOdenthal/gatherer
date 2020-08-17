#ifndef _PATHSRENDERER_HPP_
#define _PATHSRENDERER_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>

#include "utils.hpp"
#include "camera.hpp"

#define PATHSRENDERER_DEFPATHSALPHA 0.2f

class SceneInfo
{
public:
	uintmax_t				paths_number;
	std::vector<GLint>		paths_firsts;
	std::vector<GLsizei>	paths_lenghts;
	AABB					bounding_box;
};

class PathsRenderer
{
public:
	void init();
	void render(Camera& cam);
	
	SceneInfo scene_info;
	float pathsalpha;
	bool enabledepth;
private:
	void disk_load_all_paths(
		const boost::filesystem::path dirpath
	);

	GLuint vaoidx;
	GLuint vboidx;
	GLuint shaprog_idx;
	GLint  locid_camvpmat;
	GLint  locid_pathsalpha;
};

#endif