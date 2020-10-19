

#pragma once
#include "InputManager.h"
#include "Material.h"
#include "MyMath.h"

using namespace GameEngine;
int main(int , char** )
{

	Material* material = new Material();
	float pInput = 1.0f;
	std::string str = "djfalfdjal";
	const char* c = str.c_str();
	material->AddProperty(&pInput, 1, str.c_str());
	const vecterFloat3 vec = vecterFloat3(3, 3, 3);
	str = "2233";
	material->AddProperty(&vec, 1, str.c_str());
	vecterFloat3 temp;
	material->Get(str.c_str(), 0, 0, temp);
    return 0;
}

