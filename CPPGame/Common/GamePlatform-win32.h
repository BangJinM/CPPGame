#ifndef CPPGAME_COMMON_GAMEPLATFORM_WIN32_H
#define CPPGAME_COMMON_GAMEPLATFORM_WIN32_H

#include <windows.h>
#include <windowsx.h>

#include "GfxConfiguration.h"
#include "BaseApplication.h"

class WindowsApplication : public BaseApplication
{
public:
	WindowsApplication(GfxConfiguration& config)
		: BaseApplication(config) {};

	virtual int Initialize();
	virtual void Finalize();
	// One cycle of the main loop
	virtual void Tick();

	// the WindowProc function prototype
	static LRESULT CALLBACK WindowProc(HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam);
};

#endif //MAENGINE_GFXCONFIGURATION_H
