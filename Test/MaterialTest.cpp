

#include "InputManager.h"
#include "Material.h"
using namespace GameEngine;
int main(int , char** )
{
	Material* material = new Material();
	const float pInput = 1.0f;
	material->AddProperty(&pInput, 1, "1");

    return 0;
}

