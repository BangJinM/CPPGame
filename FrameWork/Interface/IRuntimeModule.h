#pragma once

namespace GameEngine
{
    class IRuntimeModule
    {
    public:
        virtual ~IRuntimeModule(){};
        /*
		* 这是用来初始化模块的
		*/
        virtual int Initialize() = 0;
        /*
		* 结束模块是调用
		*/
        virtual void Finalize() = 0;
        /*
		* ，这个是用来让驱动模块驱动该模块执行的。每调用一次，模块进行一个单位的处理
		*/
        virtual void Tick() = 0;
    };
}  // namespace GameEngine
