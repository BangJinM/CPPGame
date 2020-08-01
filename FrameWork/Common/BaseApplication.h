//
// Created by 马邦�? on 2018/4/21.
//

#ifndef MAENGINE_BASEAPPLICATION_H
#define MAENGINE_BASEAPPLICATION_H

#include "IApplication.h"
#include "GfxConfiguration.h"
namespace GameEngine
{
    class BaseApplication : public IApplication
    {
    public:
        BaseApplication(GfxConfiguration &cfg);

        virtual int Initialize();

        virtual void Finalize();

        // One cycle of the main loop
        virtual void Tick();

        virtual bool IsQuit();

    protected:
        virtual void OnDraw(){};

    protected:
        // 标记是否在住循环中退�?
        static bool m_bQuit;
        GfxConfiguration m_Config;

    private:
        // hide the default construct to enforce a configuration
        BaseApplication(){};
    };
} // namespace GameEngine
#endif //MAENGINE_BASEAPPLICATION_H
