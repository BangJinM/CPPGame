

#include "InputManager.h"
#include "Material.h"
using namespace GameEngine;
int main(int , char** )
{
	Material* material = new Material();
	float pInput = 1.0f;
	material->AddProperty(&pInput, 1, "1");
	material->AddProperty(&pInput, 1, "1");
	material->AddProperty(&pInput, 2, "2");
	material->AddProperty(&pInput, 3, "3");
	material->AddProperty(&pInput, 4, "4");
	material->AddProperty(&pInput, 5, "5");
	material->AddProperty(&pInput, 6, "6");
    return 0;
}

