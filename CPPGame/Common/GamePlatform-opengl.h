#ifndef CPPGAME_COMMON_GAMEPLATFORM_OPENGL_H
#define CPPGAME_COMMON_GAMEPLATFORM_OPENGL_H

#include "GfxConfiguration.h"
#include "BaseApplication.h"
#include "GamePlatform-win32.h"

#include "GamePlatform-opengl.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>


class OpenGLApplication : public BaseApplication
{
public:
	OpenGLApplication(GfxConfiguration& config)
		: BaseApplication(config) {};

	virtual int Initialize();
	virtual void Finalize();
	// One cycle of the main loop
	virtual void Tick();

	static void mouseInput(GLFWwindow* window, int button, int action, int mods);
	static void keyInput(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
	void calculateDeltaTime();

	GLFWwindow* window;
	float _deltaTime;
	std::chrono::steady_clock::time_point _lastUpdate;
};

#endif //CPPGAME_COMMON_GAMEPLATFORM_OPENGL_H
