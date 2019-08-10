#ifndef SRC_RENDERER_BASE_RENDERER_H
#define SRC_RENDERER_BASE_RENDERER_H


#include "Component.h"
#include "ClassIDs.h"

class BaseRenderer:public Component
{
public:
	BaseRenderer():Component(ClassIDType::CLASS_BaseRenderer){}
};

#endif