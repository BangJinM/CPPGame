

#include "InputManager.h"
using namespace std;
using namespace GameEngine;

namespace GameEngine {
    InputManager* g_pInputManager = new InputManager();
}

void callback(){
	printf("daaaaaaaaaaaaaaa\n");
}

void callback3() {
	printf("nnnnnnnnnnnnnnnnnnnn\n");
}

void callback4() {
	printf("tttttttttttttttt\n");
}

int main(int , char** )
{
	g_pInputManager->Initialize();

	g_pInputManager->addClickEventListener('c',  callback);
	g_pInputManager->addClickEventListener('c', callback3);
	g_pInputManager->addClickEventListener('b', callback4);
	g_pInputManager->dispatchClickEvent('c');

	g_pInputManager->removeClickEventListener('c', callback3);
	g_pInputManager->dispatchClickEvent('c');

	g_pInputManager->Finalize();

    delete g_pInputManager;

    return 0;
}

