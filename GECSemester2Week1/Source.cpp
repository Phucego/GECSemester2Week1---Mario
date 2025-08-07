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
#include <SDL_mixer.h>
using namespace std;
	
	void LoadMusic(string path);
	Mix_Music* gMusic = NULL;
	Mix_Chunk* jumpsfx = NULL;

	int jumpsfxChannel = -1;


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
	bool Update();

	void Render();
	//SDL_Texture* LoadTextureFromFile(string path);
	//void FreeTexture();
int main(int argc, char* args[])
{

	jumpsfx = Mix_LoadWAV("smb_jump.wav");

	//Flag to check if we wish to quit.
	bool quit = false;

	//InitSDL();
	//Check if SDL was set up correctly
	if (InitSDL())
	{
		gOldTime = SDL_GetTicks();
		//Set up the game screen manager - Start with Level1
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);

		LoadMusic("Music/Mario.ogg");
	}
	
	//Game loop.
	while (!quit)
	{
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(gMusic, -1);
		}
		Render();
		quit = Update();		
	}

	//Close Window and free resources.
	CloseSDL();

	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16;
	int audio_channels = 2;
	int audio_buffers = 4096;
	return 0;
}

//Setup SDL.
bool InitSDL()
{
	//Initialise the Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "Mixer could not initialise. Error. " << Mix_GetError();
		return false;
	}



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


	//Release music 
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

}


bool Update()
{

	//Get the new time
	Uint32 newTime = SDL_GetTicks();

	//Event Handler.
	SDL_Event e;

	//Get the events
	SDL_PollEvent(&e);
	
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
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	//Set where to render the texture
	SDL_Rect renderLocation = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	gameScreenManager->Render();

	//Update the screen
	SDL_RenderPresent(gRenderer);
	

}
void LoadMusic(string path)
{
	gMusic = Mix_LoadMUS(path.c_str());

	if (gMusic == NULL)
	{
		cout << "Failed to load background music! Error " << Mix_GetError() << endl;
	}
}
void handleKey(SDL_KeyboardEvent key)
{
	switch (key.keysym.sym)
	{
		case SDLK_p:
			//sound fx continually fire as long as the user is holding the button down
			if (key.type == SDL_KEYDOWN)
			{
				if (jumpsfxChannel < 0)
				{
					jumpsfxChannel = Mix_PlayChannel(-1, jumpsfx, -1);
				}
			}
			else
			{
				Mix_HaltChannel(jumpsfxChannel);
				jumpsfxChannel = -1;
			}
			break;
	}
}
