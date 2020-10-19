#pragma once

#include "IRuntimeModule.h"
#include <list>
#include <map>
#include <functional>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace GameEngine
{
	class InputManager;
	extern InputManager *g_pInputManager;
	class InputManager : IRuntimeModule
	{

		typedef std::function<void()> CallBack;
		struct GameEngineCallBack
		{
			std::list<CallBack> *callbacks;

			GameEngineCallBack()
			{
				callbacks = new std::list<CallBack>();
			}

			void push(CallBack callback)
			{
				callbacks->push_back(callback);
			}

			void remove(CallBack callback)
			{
				auto iter = callbacks->begin();
				//while (iter != callbacks->end())
				//{

				//}
			}

			void dispatch()
			{
				auto iter = callbacks->begin();
				while (iter != callbacks->end())
				{
					CallBack callback = *iter;
					(callback)();
					++iter;
				}
			}
		};

	public:
		virtual int Initialize();
		virtual void Finalize();
		virtual void Tick();

		static void addClickEventListener(const char key, CallBack callBack);

		static void removeClickEventListener(const char key, CallBack callBack);

		static void dispatchClickEvent(const char key);

		static void mouseInput(GLFWwindow *window, int button, int action, int mods);
		static void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods);

	private:
		GLFWwindow *window;
		/* data */
		std::map<char, GameEngineCallBack *> _listeners;
	};

} // namespace GameEngine
