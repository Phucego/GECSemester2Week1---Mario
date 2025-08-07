#include "GameScreenMainMenu.h"
#include <iostream>
#include "Texture2D.h"

GameScreenMainMenu::GameScreenMainMenu(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();

}

GameScreenMainMenu::~GameScreenMainMenu()
{

	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

}

void GameScreenMainMenu::Render()
{
	//Draw the background.
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenMainMenu::Update(float deltaTime, SDL_Event e)
{


}

bool GameScreenMainMenu::SetUpLevel()
{
	//Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}

	return true;

}