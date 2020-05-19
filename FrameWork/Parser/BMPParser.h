#ifndef GameEngine_Image_H
#define GameEngine_Image_H

#include <cstdint>
#include "ImageParser.h"

namespace GameEngine{
    class BMPParser :public ImageParser
    {
    private:
        /* data */
    public:
        BMPParser(/* args */){

        }
        ~BMPParser(){
            
        }

        virtual Image Parse(const Buffer& buf){

        }
    };

}

#endif