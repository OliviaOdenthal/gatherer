#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "axesvisualizer.hpp"
#include "scenerenderer.hpp"
#include "selectionstroke.hpp"
#include "pathsrenderer.hpp"

#include "camera.hpp"

#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

class Application
{
public:
	Application();
	~Application();
	bool loop();

	void accountwindowresize();
private:
	RenderData renderdata;

	GLFWwindow* window;
	Vec2i framesize;

	AxesVisualizer	axesvisualizer;
	SceneRenderer	scenerenderer;
	SelectionStroke selectionstroke;
	PathsRenderer	pathsrenderer;

	Camera camera;
	ImGuiIO* imgui_io;

	Vec2f cursor_old_pos;
	bool lmb_pressed;
	bool rmb_pressed;
	bool mmb_pressed;
	bool camera_key_pressed;

	void render();
	void renderui();

	void initglfw();
	void createglfwwindow();
	void initglew();
	void configureogl();
	void initimgui();

	static void windowresize(GLFWwindow* window, int width, int height);
};

#endif