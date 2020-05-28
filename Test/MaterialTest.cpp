

#pragma one
#include "InputManager.h"
#include "Material.h"
#include "MyMath.h"
using namespace myMath;
using namespace GameEngine;
int main(int , char** )
{

	Material* material = new Material();
	float pInput = 1.0f;
	material->AddProperty(&pInput, 1, "1");
	const vecterFloat3 vec = vecterFloat3(3, 3, 3);
	material->AddProperty(&vec, 1, "2323");
    return 0;
}

