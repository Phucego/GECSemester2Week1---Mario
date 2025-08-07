#pragma once
#ifndef _GAMESCREENMAINMENU_H
#define _GAMESCREENMAINMENU_H

#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"

class Texture2D;


class GameScreenMainMenu : GameScreen
{
public:
	GameScreenMainMenu(SDL_Renderer* renderer);
	~GameScreenMainMenu();

	void Render();
	void Update(float deltaTime, SDL_Event e);


private:
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();
};



#endif