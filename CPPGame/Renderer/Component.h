#ifndef SRC_RENDERER_COMPEMENT_H
#define SRC_RENDERER_COMPEMENT_H

#include "ClassIDs.h"
class Component
{
public:
	ClassIDType getClassID() { 
		if (m_ClassID > 0)
			return m_ClassID;
		return ClassIDType::CLASS_Undefined;
	}
	ClassIDType m_ClassID = ClassIDType::CLASS_Undefined;

	Component(ClassIDType classID):m_ClassID(classID){}
public:
	//GameObject* m_Host; //¼ÄÖ÷
};

#endif