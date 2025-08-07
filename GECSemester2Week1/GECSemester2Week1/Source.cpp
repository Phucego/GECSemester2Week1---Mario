#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreenManager.h"
#include "GameScreenLevel1.h"
#include "GameScreenMainMenu.h"

using namespace std;
	

	GameScreenManager* gameScreenManager;
	Uint32 gOldTime;

	//Texture2D* gTexture = NULL;
	SDL_Renderer* gRenderer = NULL;
	//SDL_Texture* gTexture = NULL;

	//Globals
	SDL_Window* gWindow = NULL;


	//Function prototypes
	bool InitSDL();
	void CloseSDL();

	void Render();
	//SDL_Texture* LoadTextureFromFile(string path);
	//void FreeTexture();
int main(int argc, char* args[])
{

	//Flag to check if we wish to quit.
	bool quit = false;

	InitSDL();
	//Check if SDL was set up correctly
	if (InitSDL())
	{
		gOldTime = SDL_GetTicks();
		//Set up the game screen manager - Start with Level1
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);
		
	}
	
	//Game loop.
	while (!quit)
	{
		Render();
		quit = Update();		
	}

	//Close Window and free resources.
	CloseSDL();

	return 0;
}

//Setup SDL.
bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialize. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//All good, so attempt to create the window.
		gWindow = SDL_CreateWindow("Games Engine Creation",
									SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									SCREEN_WIDTH,
									SCREEN_HEIGHT,
									SDL_WINDOW_SHOWN);
		//Did the window get created?
		if (gWindow == NULL)
		{
			//Nope
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer != NULL)
		{
		
			//Initialise PNG loading.
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}

			//Load the background texture
			//gTexture = new Texture2D(gRenderer);

			/*if (!gTexture->LoadFromFile("Images/test.bmp"))
			{
				return false;
			}*/
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}
	}
	return true;
}

void CloseSDL()
{

	//Destroy the game screen manager
	delete gameScreenManager;
	gameScreenManager = NULL;

	//Release the renderer.
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	//Release the memory
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

}


bool Update()
{

	//Get the new time
	Uint32 newTime = SDL_GetTicks();

	//Event Handler.
	SDL_Event e;

	//Get the events
	(SDL_PollEvent(&e));
	
		//Handle any events
	switch (e.type)
	{
		case SDL_QUIT:
			return true;
			break;
		default:
			break;

		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)	//using keysym because the 1 in the guide does not wor
			{		//press H to go to level 1
			case SDLK_h:
				gameScreenManager->ChangeScreen(SCREEN_LEVEL1);
				break;

			default:
				break;
			}

		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{		//press J to go to main menu 
			case SDLK_j:
				gameScreenManager->ChangeScreen(SCREEN_MENU);
				break;

			default:
				break;
			}
		
	}
	
		gameScreenManager->Update((float)(newTime-gOldTime) / 1000.0f, e);
		//Set the current time to be the old time
		gOldTime = newTime;

	return false;
}





void Render()
{
	//Clear the screen.
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	//Set where to render the texture
	SDL_Rect renderLocation = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	gameScreenManager->Render();

	//Update the screen
	SDL_RenderPresent(gRenderer);
	

}


