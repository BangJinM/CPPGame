#ifndef CPPGAME_COMMON_GAMEPLATFORM_OPENGL_H
#define CPPGAME_COMMON_GAMEPLATFORM_OPENGL_H

#include "GfxConfiguration.h"
#include "BaseApplication.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <vector>

namespace GameEngine
{

	class OpenGLApplication : public BaseApplication
	{
	public:
		OpenGLApplication(GfxConfiguration &config);

		virtual int Initialize();
		virtual void Finalize();
		// One cycle of the main loop
		virtual void Tick();

	private:
		void calculateDeltaTime();

		GLFWwindow *window;
		float _deltaTime;
		std::chrono::steady_clock::time_point _lastUpdate;
	};
} // namespace GameEngine
#endif //CPPGAME_COMMON_GAMEPLATFORM_OPENGL_H
