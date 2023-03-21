#include "main.h"

/**
 * WinMain function to get the thing started.
 */
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	D3DApp d3dApp(hInst);

	if (!d3dApp.Initialize())
		return 0;

	return d3dApp.Run();
}

	