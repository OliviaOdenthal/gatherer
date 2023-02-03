#ifndef _AXESVISUALIZER_HPP_
#define _AXESVISUALIZER_HPP_

#define AXESVISUALIZER_W 64
#define AXESVISUALIZER_H 64

#include "utils.hpp"
#include "camera.hpp"

class AxesVisualizer
{
public:
	void init();
	void render(Camera& cam);
	GLuint fbotex_id;
private:
	GLuint shaprog_id;
	GLuint fbo_id;
	GLint  locid_camvpmat;
};

#endif