#include "axesvisualizer.hpp"

void AxesVisualizer::init()
{
	shaprog_id = disk_load_shader_program(
		"../src/client/shaders/axes.vert.glsl",
		"../src/client/shaders/axes.frag.glsl"
	);

	glGenFramebuffers(1, &fbo_id);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);

	glGenTextures(1, &fbotex_id);
	glBindTexture(GL_TEXTURE_2D, fbotex_id);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA, 
		250, 250, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(
		GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
		GL_TEXTURE_2D, fbotex_id, 0
	);  
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		BOOST_LOG_TRIVIAL(error) << "Framebuffer is not complete!";
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void AxesVisualizer::render(Camera& cam)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}