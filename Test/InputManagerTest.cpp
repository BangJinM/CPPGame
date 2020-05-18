

#include "InputManager.h"
using namespace std;
using namespace GameEngine;

namespace GameEngine {
    InputManager* g_pInputManager = new InputManager();
}

void * callback(){
	return nullptr;
}

int main(int , char** )
{
	g_pInputManager->Initialize();

	g_pInputManager->addClickEventListener('c',  callback);
	g_pInputManager->dispatchClickEvent('c');
	g_pInputManager->Finalize();

    delete g_pInputManager;

    return 0;
}

