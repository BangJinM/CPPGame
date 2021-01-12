#include <stdio.h>
#include <tchar.h>
#include "OpenGLApplication.hpp"
#include "MemoryManager.h"
#include "GfxConfiguration.h"
#include "InputManager.h"
#include "AssetLoader.h"
#include "glad/glad_wgl.h"
#include "GraphicsManager.h"
using namespace GameEngine;

namespace GameEngine
{
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540);
    IApplication *g_pApp = static_cast<IApplication *>(new OpenGLApplication(config));
    MemoryManager *g_pMemoryManager = static_cast<MemoryManager *>(new MemoryManager);
    InputManager *g_pInputManager = static_cast<InputManager *>(new InputManager);
    AssetLoader *g_pAssetLoader = static_cast<AssetLoader *>(new AssetLoader);
	GraphicsManager* g_pGraphicsManager = static_cast<GraphicsManager*>(new GraphicsManager);

} // namespace GameEngine

int GameEngine::OpenGLApplication::Initialize()
{
    int result;
    result = WindowsApplication::Initialize();
    if (result)
    {
        printf("Windows Application initialize failed!");
    }
    else
    {
        PIXELFORMATDESCRIPTOR pfd;
        memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = m_Config.redBits + m_Config.greenBits + m_Config.blueBits + m_Config.alphaBits;
        pfd.cDepthBits = m_Config.depthBits;
        pfd.iLayerType = PFD_MAIN_PLANE;

        HWND hWnd = reinterpret_cast<WindowsApplication *>(g_pApp)->GetMainWindow();
        HDC hDC = GetDC(hWnd);
        // Set a temporary default pixel format.
        int nPixelFormat = ChoosePixelFormat(hDC, &pfd);
        if (nPixelFormat == 0)
            return -1;

        result = SetPixelFormat(hDC, nPixelFormat, &pfd);
        if (result != 1)
        {
            return -1;
        }

        // Create a temporary rendering context.
        m_RenderContext = wglCreateContext(hDC);
        if (!m_RenderContext)
        {
            return -1;
        }

        // Set the temporary rendering context as the current rendering context for this window.
        result = wglMakeCurrent(hDC, m_RenderContext);
        if (result != 1)
        {
            return -1;
        }

        if (!gladLoadWGL(hDC))
        {
            printf("WGL initialize failed!\n");
            result = -1;
        }
        else
        {
            result = 0;
            printf("WGL initialize finished!\n");
        }
    }

    return result;
}

void GameEngine::OpenGLApplication::Finalize()
{
    if (m_RenderContext)
    {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(m_RenderContext);
        m_RenderContext = 0;
    }

    WindowsApplication::Finalize();
}

void GameEngine::OpenGLApplication::Tick()
{
    WindowsApplication::Tick();
}
