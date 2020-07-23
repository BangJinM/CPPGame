#ifndef GameEngine_Common_AssetManager_H
#define GameEngine_Common_AssetManager_H

#include "IRuntimeModule.h"
#include <list>
#include <map>
#include <functional>
#include "Image.h"

namespace GameEngine{
    class AssetManager :IRuntimeModule
    {
        public:
            virtual int Initialize();
            virtual void Finalize();
            virtual void Tick();

            void addImage(std::string path, Image *image);
			Image* getImage(std::string path);
        private:
        std::map<std::string, Image*> m_Images;
    };
    
}
#endif