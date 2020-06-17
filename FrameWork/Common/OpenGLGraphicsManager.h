
#ifndef CPPGAME_Platform_Windows_OpenGlGraphicsManager_H
#define CPPGAME_Platform_Windows_OpenGlGraphicsManager_H

#include "IRuntimeModule.h"

namespace GameEngine
{
	class OpenGLGraphicsManager : public IRuntimeModule
	{
	public:
		~OpenGLGraphicsManager(){};
		virtual int Initialize();
		virtual void Finalize();
		virtual void Tick();
	};
} // namespace GameEngine
#endif //CPPGAME_INTERFACE_IRUNTIMEMODULE_H