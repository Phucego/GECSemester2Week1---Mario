#pragma once
#ifndef _CONSTANTS_H
#define	_CONSTANTS_H
	#define SCREEN_WIDTH	512
	#define SCREEN_HEIGHT	416
	#include <iostream>
	using namespace std;



	//Functions Prototypes
	bool InitSDL();
	void CloseSDL();
	bool Update();

	void Render();
	SDL_Texture* LoadFromFile(string path);
	void Free();
#endif // !1

