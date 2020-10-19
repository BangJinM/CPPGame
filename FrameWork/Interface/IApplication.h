//
// Created by 马邦进 on 2018/4/21.
//

#pragma once

#include "Config.h"
#include "IRuntimeModule.h"

GameEngineBegin 

class IApplication : public IRuntimeModule
{
public:
	virtual int Initialize() = 0;

	virtual void Finalize() = 0;

	// One cycle of the main loop
	virtual void Tick() = 0;
	/*
			* 用于查询应用程序是否需要退出。
			* 这是因为，在很多平台上用户关闭应用程序都是通过系统通知过来的。
			* 我们的程序自身并不会直接进行这方面的判断。所以当我们收到这样的关闭通知的时候，
		*/
	virtual bool IsQuit() = 0;
};

GameEngineEnd
